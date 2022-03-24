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

void convertDecToHex(size_t number, char* hexNumber)
{
	while (number!=0)
	{
		size_t lastDigit = number % 10;
		hexNumber[0] = lastDigit;
		number /= 16;
	}
}

void convertArrayToHex(int*& arr, size_t length)
{
	char hexNumber[2];
	for (size_t i = 0; i < length; i++)
	{
		convertDecToHex(arr[i], hexNumber);
	}
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

	int fileSize = getFileSize(sourceFile);
	std::cout << "File loaded successfully! Size: " << fileSize << " bytes" << std::endl;

	int* input = new int[fileSize];
	for (size_t i = 0; !sourceFile.eof(); i++)
	{
		input[i] = sourceFile.get();
	}
	for (size_t i = 0; i < fileSize; i++)
	{
		if ((input[i] <= 90 && input[i] >= 65) || (input[i] >= 97 && input[i] <= 122))
			std::cout << (char)input[i] << " ";
		else
			std::cout << ". ";
	}
}
