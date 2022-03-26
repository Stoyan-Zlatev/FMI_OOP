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

void getData(int*& input, std::fstream& sourceFile, size_t fileSize)
{
	for (size_t i = 0; i < fileSize; i++)
	{
		input[i] = sourceFile.get();
	}
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

size_t convertHexToDec(const char* hexNumber, size_t currentIndex)
{
	return parseCharToInt(hexNumber[currentIndex * 2 + 1]) + 16 * parseCharToInt(hexNumber[currentIndex * 2]);
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
		for (size_t i = numberLength; i > 0; i--)
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

void printHex(const char* hexInput, size_t fileSize)
{
	for (size_t i = 0; i < fileSize * 2; i += 2)
	{
		std::cout << hexInput[i] << hexInput[i + 1] << " ";
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

bool isCapitalLetter(char element)
{
	return element <= 90 && element >= 65;
}

bool isSmallLetter(char element)
{
	return element >= 97 && element <= 122;
}

size_t getNumber(const char* command, size_t numberLength)
{
	//command x
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

//ref?
void view(const char* hexInput, const int* input, size_t fileSize)
{
	printHex(hexInput, fileSize);

	for (size_t i = 0; i < fileSize; i++)
	{
		if (isCapitalLetter(input[i]) || isSmallLetter(input[i]))
			std::cout << (char)input[i] << "  ";
		else
			std::cout << ".  ";
	}
	std::cout << std::endl;
}

bool change(const char* command, char* hexInput, int* input, std::fstream& file, size_t fileSize)
{
	const size_t currentCommandLength = 7;
	size_t index = getNumber(command, 7);
	if (index >= fileSize)
	{
		return false;
	}
	size_t number = getNumber(command, currentCommandLength + getNumberLength(index) + 1);
	hexInput[index * 2] = parseIntToChar(number / 10);
	hexInput[index * 2 + 1] = parseIntToChar(number % 10);
	size_t decNumber = convertHexToDec(hexInput, index);
	if (decNumber > 255)
	{
		return false;
	}
	input[index] = decNumber;
	file.seekp(index);
	file << char(decNumber);
	file.seekp(0, std::ios::beg);

	return true;
}

void removeLastByte(const char* filePath, int* input, char* hexInput, std::fstream& file, size_t& fileSize)
{
	fileSize--;
	file.close();
	file.open(filePath, std::ios::binary | std::ios::trunc);
	for (size_t i = 0; i < fileSize; i++)
	{
		file.seekg(i);
		file << (char)input[i];
	}
	file.seekg(std::ios::beg);
	/*input = new int[fileSize];
	hexInput = new char[fileSize * 2];
	getData(input, file, fileSize);
	convertArrayToHex(input, fileSize, hexInput);*/
}

void add(const char* command, int* input, char* hexInput, std::fstream& file, size_t& fileSize)
{
	const size_t currentCommandLength = 4;
	file.seekg(fileSize);
	size_t value = getNumber(command, currentCommandLength);
	file.putback(char(value));
	fileSize++;
	/*input = new int[fileSize];
	hexInput = new char[fileSize * 2];
	getData(input, file, fileSize);
	convertArrayToHex(input, fileSize, hexInput);*/
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
	//delete
	int* input = new int[fileSize];
	getData(input, sourceFile, fileSize);
	//delete
	char* hexInput = new char[fileSize * 2]; //new array with decimal to hexadecimal bytes

	convertArrayToHex(input, fileSize, hexInput);

	char command[BUFF] = "";
	while (!isPrefix(command, "save"))
	{
		std::cout << ">";
		std::cin.getline(command, BUFF);
		if (isPrefix(command, "view"))
		{
			view(hexInput, input, fileSize);
		}
		else if (isPrefix(command, "change"))
		{
			if (change(command, hexInput, input, sourceFile, fileSize) && file.good())
				std::cout << "Operation successfully executed!" << std::endl;
			else
				std::cout << "Error, incorrect input!" << std::endl;
		}
		else if (isPrefix(command, "remove"))
		{
			removeLastByte(filePath, input, hexInput, sourceFile, fileSize);
		}
		else if (isPrefix(command, "add"))
		{
			add(command, input, hexInput, sourceFile, fileSize);
		}
		else if (isPrefix(command, "save as"))
		{

		}
		else if (isPrefix(command, "save"))
		{

		}
	}

}
