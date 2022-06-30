#include <iostream>
#include <fstream>

const size_t BUFF_SIZE = 1024;

int main()
{
	std::ifstream sourceFile("Source.cpp");

	if (!sourceFile.is_open())
	{
		std::cout << "Error, opening source file." << std::endl;
	}

	char buff[BUFF_SIZE];

	while (!sourceFile.eof())
	{
		sourceFile.getline(buff, BUFF_SIZE);
		std::cout << buff << std::endl;
	}

	sourceFile.close();
}
