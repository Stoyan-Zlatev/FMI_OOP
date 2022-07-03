#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& file)
{
	size_t currentPosition = file.tellg();

	file.seekg(0, std::ios::cur);
	size_t size = file.tellg();

	file.seekg(currentPosition);
	
	return size;
}
