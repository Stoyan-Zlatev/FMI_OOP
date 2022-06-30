#include <iostream>
#include <fstream>

void replaceInFile(std::fstream& file, char ch1, char ch2)
{
	while (!file.eof())
	{
		char currentSymbol = file.get();

		if (currentSymbol != ch1)
			continue;

		file.seekp(-1, std::ios::cur);
		file.put(ch2);
		file.flush();
	}
}

int main()
{
	std::fstream file("file.txt", std::ios::in | std::ios::out);

	if (!file.is_open())
	{
		std::cout << "Error";
		return -1;
	}

	replaceInFile(file, 'c', 'x');
}
