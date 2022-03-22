#include <iostream>
#include <fstream>

bool Duplicate(const char* filePath, const char* newFile, int n)
{
	std::ifstream inputFile(filePath);
	std::ofstream destFile(newFile);

	if (!inputFile.is_open() || !destFile.is_open())
	{
		return false;
	}

	const int BUFF = 1024;
	for (size_t i = 0; i < n; i++)
	{
		while (!inputFile.eof())
		{
			char line[BUFF];
			inputFile.getline(line, BUFF);
			destFile << line;
		}
		inputFile.seekg(0, std::ios::beg);
	}
}

int main()
{
	if (Duplicate("myFile.txt", "result.txt", 3))
	{
		std::cout << "Success";
	}
	else
	{
		std::cout << "Error";
	}
}