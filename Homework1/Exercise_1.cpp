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
	const int BUFF = 1024;
	/*int x = 25409;
	std::ofstream file("source.dat");
	file.write((const char*)&x, sizeof(x));
	file.close();*/

	std::cout << "Enter a file path:" << std::endl;
	std::cout << ">";
	char filePath[BUFF];
	std::cin.getline(filePath, BUFF);

	std::ifstream sourceFile(filePath, std::ios::binary);

	if (!sourceFile.is_open())
	{
		std::cout << "Error" << std::endl;
		return -1;
	}
	std::cout << "File loaded successfully! Size: " << getFileSize(sourceFile) << " bytes";

}
