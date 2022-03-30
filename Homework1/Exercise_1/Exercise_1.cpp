#include <iostream>
#include <fstream>
#include <cstring>

const int hexByteLegth = 2;

size_t getFileSize(std::fstream& file)
{
	size_t currentPosition = file.tellg();

	file.seekg(0, std::ios::end);
	size_t result = file.tellg();
	file.seekg(currentPosition);
	return result;
}

size_t getNumberLength(size_t number)
{
	if (number == 0)
	{
		return 1;
	}
	size_t counter = 0;
	while (number != 0)
	{
		number /= 10;
		counter++;
	}
	return counter;
}

bool isCapitalLetter(char element)
{
	return element <= 'Z' && element >= 'A';
}

bool isSmallLetter(char element)
{
	return element >= 'a' && element <= 'z';
}

bool isDigit(char element)
{
	return element >= '0' && element <= '9';
}

size_t parseCharToInt(char element)
{
	if (isDigit(element))
		return element - '0';
	else
		return (element - 'A') + 10;
}

char parseIntToChar(size_t digit)
{
	if (digit < 10)
		return digit + '0';
	else
		return (digit % 10) + 'A';
}

size_t convertHexToDec(const char* hexNumber)
{
	return parseCharToInt(hexNumber[1]) + 16 * parseCharToInt(hexNumber[0]);
}

void convertDecToHex(size_t number, char* hexNumber)
{
	size_t numberLength = getNumberLength(number);

	if (numberLength == 0)
	{
		hexNumber[0] = 48;
		hexNumber[1] = 48;
	}
	else if (number < 16)
	{
		hexNumber[0] = 0;
		hexNumber[1] = number % 16;
	}
	else
	{
		for (size_t i = hexByteLegth; i > 0; i--)
		{
			size_t lastDigit = number % 16;
			if (lastDigit < 10)
				hexNumber[i - 1] = lastDigit + '0';
			else
				hexNumber[i - 1] = (lastDigit - 10) + 'A';
			number /= 16;
		}
	}
}

void convertArrayToHex(const int* input, size_t length, char* hexInput)
{
	char hexNumber[hexByteLegth];
	for (size_t i = 0; i < length; i++)
	{
		convertDecToHex(input[i], hexNumber);
		hexInput[i * hexByteLegth] = hexNumber[0];
		hexInput[i * hexByteLegth + 1] = hexNumber[1];
	}
}

void printHex(const char* buffer, size_t fileSize)
{
	char hexNumber[hexByteLegth];
	for (size_t i = 0; i < fileSize; i++)
	{
		convertDecToHex(buffer[i], hexNumber);
		if (hexNumber[0] == '\0')
			std::cout << parseIntToChar(hexNumber[0]) << parseIntToChar(hexNumber[1]) << " ";
		else
			std::cout << hexNumber[0] << hexNumber[1] << " ";
	}
	std::cout << std::endl;
}

bool isPrefix(const char* text, const char* prefix)
{
	int i = 0;
	while (prefix[i] != '\0')
	{
		if (text[i] == '\0' || text[i] != prefix[i])
			return false;
		i++;
	}
	return true;
}

bool isValidHexNumber(const char* command, const size_t currentCommandIndex)
{
	const size_t hexCapacity = 15;
	if (parseCharToInt(command[currentCommandIndex]) > hexCapacity || parseCharToInt(command[currentCommandIndex + 1]) > hexCapacity)
		return false;
	return true;

}

void getHexNumber(const char* command, char* hexNumber, size_t numberLength)
{
	size_t currentIndex = numberLength;
	hexNumber[0] = command[currentIndex];
	hexNumber[1] = command[currentIndex + 1];
}

size_t getNumber(const char* command, size_t numberLength)
{
	size_t currentIndex = numberLength;
	size_t number = 0;
	while (isDigit(command[currentIndex]))
	{
		number *= 10;
		number += parseCharToInt(command[currentIndex]);
		currentIndex++;
	}
	return number;
}

void view(const char* buffer, size_t fileSize)
{
	printHex(buffer, fileSize);

	for (size_t i = 0; i < fileSize; i++)
	{
		size_t currentByte = buffer[i];
		if (isCapitalLetter(currentByte) || isSmallLetter(currentByte))
			std::cout << (char)currentByte << "  ";
		else
			std::cout << ".  ";
	}
	std::cout << std::endl;
}

bool change(const char* command, char* buffer, size_t fileSize)
{
	const size_t currentCommandLength = 7;
	const size_t byteCapacity = 255;
	size_t index = getNumber(command, currentCommandLength);
	if (index >= fileSize)
	{
		return false;
	}
	size_t number = getNumber(command, currentCommandLength + getNumberLength(index) + 1);
	char hexNumber[hexByteLegth];
	hexNumber[0] = parseIntToChar(number / 10);
	hexNumber[1] = parseIntToChar(number % 10);
	size_t decNumber = convertHexToDec(hexNumber);
	if (decNumber > byteCapacity)
	{
		return false;
	}
	buffer[index] = char(decNumber);

	return true;
}

void copyArray(const char* buffer, char*& tempBuffer, size_t newSize)
{
	for (size_t i = 0; i < newSize; i++)
	{
		tempBuffer[i] = buffer[i];
	}
}

void removeLastByte(char*& buffer, size_t& fileSize)
{
	fileSize--;
	char* tempBuffer = new char[fileSize];
	copyArray(buffer, tempBuffer, fileSize);
	delete[] buffer;
	buffer = tempBuffer;
}

void substr(size_t startIndex, const char* text, char*& subStr, size_t textLength, size_t currentCommandLength)
{
	for (size_t i = startIndex; i < textLength; i++)
	{
		subStr[i - currentCommandLength] = text[i];
	}
}

void rewriteFile(std::fstream& file, const char* buffer, size_t& fileSize) {
	file.seekp(0, std::ios::beg);
	file.write(buffer, fileSize);
	file.seekp(0, std::ios::beg);
}

bool add(const char* command, char*& buffer, size_t& fileSize)
{
	const size_t currentCommandLength = 4;
	if (!isValidHexNumber(command, currentCommandLength))
		return false;
	char hexNumber[hexByteLegth];
	getHexNumber(command, hexNumber, currentCommandLength);
	size_t value = convertHexToDec(hexNumber);
	char* tempArray = new char[fileSize + 1];
	copyArray(buffer, tempArray, fileSize);
	tempArray[fileSize] = char(value);
	fileSize++;
	delete[] buffer;
	buffer = tempArray;
	return true;
}

void loadBuffer(char*& buffer, std::fstream& sourceFile, size_t fileSize)
{
	sourceFile.seekg(0, std::ios::beg);
	for (size_t i = 0; i < fileSize; i++)
	{
		buffer[i] = (char)sourceFile.get();
	}
}

void saveAs(std::fstream& sourceFile, const char* command, const char* buffer, const char* filePath, size_t fileSize)
{
	const size_t currentCommandLength = 8;
	sourceFile.close();
	size_t textLength = strlen(command);
	char* newFileName = new char[(textLength - currentCommandLength) + 1];
	substr(currentCommandLength, command, newFileName, textLength, currentCommandLength);
	newFileName[textLength - currentCommandLength] = '\0';
	std::fstream newFile(newFileName, std::ios::binary | std::ios::out | std::ios::ate);
	rewriteFile(newFile, buffer, fileSize);
	newFile.close();
	delete[] newFileName;
}

void save(std::fstream& sourceFile, const char* buffer, const char* filePath, size_t fileSize)
{
	sourceFile.close();
	std::fstream newFile(filePath,std::ios::trunc | std::ios::binary |std::ios::in | std::ios::out | std::ios::ate);
	rewriteFile(newFile, buffer, fileSize);
	newFile.close();
}

int main()
{
	int x = 25409;
	std::ofstream file("source.dat");
	file.write((const char*)&x, sizeof(x));
	file.close();

	const int BUFF = 1024;
	const int minFileSize = 1;

	std::cout << "Enter a file path:" << std::endl;
	std::cout << ">";
	char filePath[BUFF];
	std::cin.getline(filePath, BUFF);

	std::fstream sourceFile(filePath, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);

	if (!sourceFile.is_open())
	{
		std::cout << "Error" << std::endl;
		return -1;
	}

	size_t fileSize = getFileSize(sourceFile);

	std::cout << "File loaded successfully! Size: " << fileSize << " bytes" << std::endl;

	char* buffer = new char[fileSize];
	loadBuffer(buffer, sourceFile, fileSize);

	char command[BUFF] = "";
	while (!isPrefix(command, "save"))
	{
		std::cout << ">";
		std::cin.getline(command, BUFF);

		if (isPrefix(command, "view"))
		{
			view(buffer, fileSize);
		}
		else if (isPrefix(command, "change"))
		{
			if (change(command, buffer, fileSize))
				std::cout << "Operation successfully executed!" << std::endl;
			else
				std::cout << "Error, incorrect input!" << std::endl;
		}
		else if (isPrefix(command, "remove"))
		{
			if (fileSize >= minFileSize)
			{
				removeLastByte(buffer, fileSize);
			}
			else
			{
				std::cout << "File is already empty" << std::endl;
			}
		}
		else if (isPrefix(command, "add"))
		{
			if (add(command, buffer, fileSize))
			{
				std::cout << "Byte added successfuly!" << std::endl;
			}
			else
			{
				std::cout << "Operation failed!" << std::endl;
			}
		}
		else if (isPrefix(command, "save as"))
		{
			saveAs(sourceFile, command, buffer, filePath, fileSize);
			//Should not be sourceFile
			if (sourceFile.good())
				std::cout << "File successfully saved!" << std::endl;
		}
		else if (isPrefix(command, "save"))
		{
			save(sourceFile, buffer, filePath, fileSize);
			if (sourceFile.good())
				std::cout << "File successfully saved!" << std::endl;
		}
		else
		{
			std::cout << "Incorrect command" << std::endl;
		}
	}
}
