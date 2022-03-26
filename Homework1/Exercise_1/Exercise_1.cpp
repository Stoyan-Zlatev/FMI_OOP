#include <iostream>
#include <fstream>
#include <cstring>

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
	return element <= 90 && element >= 65;
}

bool isSmallLetter(char element)
{
	return element >= 97 && element <= 122;
}

bool isDigit(char element)
{
	return element >= 48 && element <= 57;
}

size_t parseCharToInt(char element)
{
	if (isDigit(element))
		return element - 48;
	else
		return element - 55;
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
		for (size_t i = 2; i > 0; i--)
		{
			size_t lastDigit = number % 16;
			if (lastDigit < 10)
				hexNumber[i - 1] = lastDigit + 48;
			else
				hexNumber[i - 1] = lastDigit + 55;
			number /= 16;
		}
	}
}

void convertArrayToHex(const int* input, size_t length, char* hexInput)
{
	char hexNumber[2];
	for (size_t i = 0; i < length; i++)
	{
		convertDecToHex(input[i], hexNumber);
		hexInput[i * 2] = hexNumber[0];
		hexInput[i * 2 + 1] = hexNumber[1];
	}
}

void printHex(std::fstream& file, size_t fileSize)
{
	char hexNumber[2];
	file.seekg(0, std::ios::beg);
	for (size_t i = 0; i < fileSize; i++)
	{
		convertDecToHex(file.get(), hexNumber);
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

void view(std::fstream& file, size_t fileSize)
{
	printHex(file, fileSize);

	file.seekg(0, std::ios::beg);
	for (size_t i = 0; i < fileSize; i++)
	{
		size_t currentByte = file.get();
		if (isCapitalLetter(currentByte) || isSmallLetter(currentByte))
			std::cout << (char)currentByte << "  ";
		else
			std::cout << ".  ";
	}
	std::cout << std::endl;
	file.seekg(0, std::ios::beg);
}

bool change(const char* command, std::fstream& file, size_t fileSize)
{
	const size_t currentCommandLength = 7;
	size_t index = getNumber(command, 7);
	if (index >= fileSize)
	{
		return false;
	}
	size_t number = getNumber(command, currentCommandLength + getNumberLength(index) + 1);
	char hexNumber[2];
	hexNumber[0] = parseIntToChar(number / 10);
	hexNumber[1] = parseIntToChar(number % 10);
	size_t decNumber = convertHexToDec(hexNumber);
	if (decNumber > 255)
	{
		return false;
	}
	file.seekp(index);
	file << char(decNumber);
	file.seekg(0, std::ios::beg);

	return true;
}

void substr(size_t startIndex, const char* text, char*& subStr, size_t textLength)
{
	for (size_t i = startIndex; i < textLength; i++)
	{
		subStr[i - 8] = text[i];
	}
}

void removeLastByte(const char* input, std::fstream& file, size_t& fileSize)
{
	fileSize--;
	file.seekp(0, std::ios::beg);
	file.write(input, fileSize);
}

void removeFileData(std::fstream& file, const char* buffer, size_t& fileSize) {
	file.seekp(0, std::ios::beg);
	file.write(buffer, --fileSize);
	file.seekp(0, std::ios::beg);
}

void rewriteFile(std::fstream& file, const char* buffer, size_t& fileSize) {
	file.seekp(0, std::ios::beg);
	file.write(buffer, fileSize);
}

void add(const char* command, std::fstream& file, size_t& fileSize)
{
	const size_t currentCommandLength = 4;
	size_t value = convertHexToDec(getNumber(command, currentCommandLength));
	file<<(char(value));
	fileSize++;
}

int main()
{
	const int BUFF = 1024;
	int x = 25409;
	std::ofstream file("source.dat");
	file.write((const char*)&x, sizeof(x));
	file.close();

	std::cout << "Enter a file path:" << std::endl;
	std::cout << ">";
	char filePath[BUFF];
	std::cin.getline(filePath, BUFF);

	std::fstream sourceFile(filePath, std::ios::in | std::ios::out | std::ios::binary);

	if (!sourceFile.is_open())
	{
		std::cout << "Error" << std::endl;
		return -1;
	}

	size_t fileSize = getFileSize(sourceFile);

	std::cout << "File loaded successfully! Size: " << fileSize << " bytes" << std::endl;

	char command[BUFF] = "";
	while (!isPrefix(command, "save"))
	{
		std::cout << ">";
		std::cin.getline(command, BUFF);
		if (isPrefix(command, "view"))
		{
			view(sourceFile, fileSize);
		}
		else if (isPrefix(command, "change"))
		{
			if (change(command, sourceFile, fileSize) && sourceFile.good())
				std::cout << "Operation successfully executed!" << std::endl;
			else
				std::cout << "Error, incorrect input!" << std::endl;
		}
		else if (isPrefix(command, "remove"))
		{
			char* buffer = new char[fileSize];
			for (size_t i = 0; i < fileSize; i++)
			{
				buffer[i] = (char)sourceFile.get();
			}
			sourceFile.close();
			std::fstream removeFile(filePath, std::ios::binary | std::ios::out | std::ios::trunc);
			removeFileData(removeFile, buffer, fileSize);
			removeFile.close();
			delete[] buffer;
			sourceFile.open(filePath, std::ios::binary | std::ios::out | std::ios::in);
		}
		else if (isPrefix(command, "add"))
		{
			sourceFile.close();
			std::fstream addFile(filePath, std::ios::binary | std::ios::app);
			add(command, addFile, fileSize);
			addFile.close();
			sourceFile.open(filePath, std::ios::binary | std::ios::out | std::ios::in);
		}
		else if (isPrefix(command, "save as"))
		{
			char* buffer = new char[fileSize];
			for (size_t i = 0; i < fileSize; i++)
			{
				buffer[i] = (char)sourceFile.get();
			}
			sourceFile.close();
			size_t textLength = strlen(command);
			char* newFileName = new char[textLength -7];
			substr(8, command, newFileName, textLength);
			newFileName[textLength - 8] = '\0';
			std::fstream newFile(newFileName, std::ios::binary | std::ios::out | std::ios::app);
			rewriteFile(newFile, buffer, fileSize);
			newFile.close();
			delete[] buffer;
			sourceFile.open(filePath, std::ios::binary | std::ios::out | std::ios::in);
		}
		else if (isPrefix(command, "save"))
		{
			sourceFile.close();
		}
	}
	sourceFile.close();

}

//TODO getNumber must be char[2] because hex
