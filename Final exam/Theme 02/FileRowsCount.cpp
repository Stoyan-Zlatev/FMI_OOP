#include <iostream>
#include <fstream>

const size_t BUFF_SIZE = 1024;

size_t getFileRowsCount(std::ifstream& file)
{
	size_t currentPosition = file.tellg();
	file.seekg(0, std::ios::beg);

	size_t rows = 0;
	char buff[BUFF_SIZE];
	
	while (!file.eof())
	{
		file.getline(buff, BUFF_SIZE);
		rows++;
	}

	file.seekg(currentPosition);
	
	return rows;
}
