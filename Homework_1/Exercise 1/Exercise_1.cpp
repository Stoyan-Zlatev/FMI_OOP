#include <iostream>
#include <fstream>
#include <cstring>
#include "Exercise 1.h"

int main()
{
	/*int x = 25409;
	std::ofstream file("source.dat");
	file.write((const char*)&x, sizeof(x));
	file.close();*/
	
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

	std::cout << "File loaded successfully! Size: "; 
	
	size_t fileSize = getFileSize(sourceFile);

	std::cout << fileSize << " bytes" << std::endl;

	char* buffer = new char[fileSize];
	loadBuffer(buffer, sourceFile, fileSize);

	operate(sourceFile, filePath, buffer, fileSize);

	delete[] buffer;
}
