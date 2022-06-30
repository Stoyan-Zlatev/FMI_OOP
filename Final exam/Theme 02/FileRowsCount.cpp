#include <iostream>
#include <fstream>

const size_t BUFF = 1024;

size_t getFileRowsCount(std::ifstream& file)
{
	size_t currentPosition = file.tellg();
	file.seekg(0, std::ios::beg);
	
	size_t counter = 0;
	char buff[BUFF];
	while (!file.eof())
	{
		file.getline(buff,BUFF);
		counter++;
	}

	file.seekg(0, currentPosition);
	return counter;
}
int main()
{
	std::ifstream file("name.txt");

	if (!file.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
		return -1;
	}

	std::cout << getFileRowsCount(file) << " rows" << std::endl;

	return 0;
}
