#include <iostream>
#include <fstream>

const size_t BUFF_SIZE = 1024;

int main()
{
	std::ifstream sourceFile("Source.cpp");
	std::ofstream destFile("Dest.cpp");

	if (!sourceFile.is_open())
	{
		std::cout << "Error, opening source file." << std::endl;
	}
	if (!destFile.is_open())
	{
		std::cout << "Error, opening source file." << std::endl;
	}

	char buff[BUFF_SIZE];

	while (!sourceFile.eof())
	{
		sourceFile.getline(buff, BUFF_SIZE);
		destFile << buff<<"\n";
	}

	sourceFile.close();
	destFile.close();
}
