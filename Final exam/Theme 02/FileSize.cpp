#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& file)
{
	size_t currentPosition = file.tellg();

	file.seekg(0, std::ios::end);
	size_t result = file.tellg();
	file.seekg(0, currentPosition);
	return result;
}
int main()
{
	std::ifstream file("name.txt");

	if (!file.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
		return -1;
	}

	std::cout << getFileSize(file) << " bytes" << std::endl;

	return 0;
}
