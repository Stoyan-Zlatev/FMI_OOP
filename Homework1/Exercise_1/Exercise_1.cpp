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

void convertArrayToHex(int* arr, size_t length, char* array)
{
	char hexNumber[2];
	for (size_t i = 0; i < length; i++)
	{
		convertDecToHex(arr[i], hexNumber);
		array[i * 2] = hexNumber[0];
		array[i * 2 + 1] = hexNumber[1];
	}
}

void printHex(char* hexInput, size_t fileSize)
{
	for (size_t i = 0; i < fileSize * 2; i += 2)
	{
		std::cout << hexInput[i] << hexInput[i + 1] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	const int BUFF = 1024;
	/*int x = 25409;
	std::ofstream file("source.dat");
	file.write((const char*)&x, sizeof(x));
	file.close();*/

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

	int fileSize = getFileSize(sourceFile);
	std::cout << "File loaded successfully! Size: " << fileSize << " bytes" << std::endl;
	//delete
	int* input = new int[fileSize];
	for (size_t i = 0; i < fileSize; i++)
	{
		input[i] = sourceFile.get();
		std::cout << input[i] << std::endl;
	}
	//delete
	char* hexInput = new char[fileSize * 2]; //new array with decimal to hexadecimal bytes
	
	convertArrayToHex(input, fileSize, hexInput);
	printHex(hexInput, fileSize);
	
	for (size_t i = 0; i < fileSize; i++)
	{
		if ((input[i] <= 90 && input[i] >= 65) || (input[i] >= 97 && input[i] <= 122))
			std::cout << (char)input[i] << " ";
		else
			std::cout << ". ";
	}
}