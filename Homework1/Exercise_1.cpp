#include <iostream>
#include <fstream>
#include <cstring>

size_t getFileSize(std::ifstream& file)
{
	size_t currentPosition = file.tellg();

	file.seekg(0, std::ios::end);
	size_t result = file.tellg();
	file.seekg(currentPosition);
	return result;
}

int main()
{
	int x = 25409;
	std::ofstream file("source.txt");
	file.write((const char*)&x, sizeof(x));
	std::cout << "Enter a file path:" << std::endl;
	char filePath[1024];
	std::cout << ">";
	std::cin.getline(filePath, 1024);

	std::ifstream sourceFile(filePath, std::ios::binary);

	if (!sourceFile.is_open())
	{
		std::cout << "Error" << std::endl;
		return -1;
	}
	std::cout << "File loaded successfully! Size: " << getFileSize(sourceFile) << " bytes";

}
