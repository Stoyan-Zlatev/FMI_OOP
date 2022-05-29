#include "Utils.h"
#include "GlobalConstants.h"
#include <iostream>

bool isPrefix(const MyString& text, const MyString& prefix)
{
	int i = 0;
	for (size_t i = 0; i < prefix.getSize(); i++)
	{
		if (i >= text.getSize() || text[i] != prefix[i])
			return false;
	}

	return true;
}

void loadFigures(const MyString& path, ShapeCollection& shapes)
{
	std::ifstream sourceFile(path.c_str());

	shapes;
	if (!sourceFile.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
	}
	else
	{
		shapes.load(sourceFile);
		std::cout << "File loaded successfully" << std::endl;
	}

	sourceFile.close();
}

int getStartindex(const MyString& line, size_t& lineSize)
{
	for (size_t i = 0; i < lineSize; i++)
	{
		if (line[i] == '<')
		{
			return i + 1;
		}
	}

	throw std::invalid_argument("Incorrect line in file!");
}

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, ' ');
}

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, '\"');
}

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument, char el)
{
	for (currentIndex; currentIndex < lineSize; currentIndex++)
	{
		if (line[currentIndex] == el)
		{
			break;
		}
	}

	currentIndex++;
	char* buffer = new char[lineSize];
	size_t i = 0;
	for (i = currentIndex; i < lineSize; i++)
	{
		if (line[i] == el)
		{
			break;
		}

		buffer[i - currentIndex] = line[i];
	}

	buffer[i - currentIndex] = '\0';
	argument = std::atof(buffer);
	el == ' ' ? currentIndex = i : currentIndex = i + 1;

	delete[] buffer;
}

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument, char el)
{
	for (currentIndex; currentIndex < lineSize; currentIndex++)
	{
		if (line[currentIndex] == el)
		{
			break;
		}
	}

	currentIndex++;
	char* buffer = new char[lineSize];
	size_t i = 0;
	for (i = currentIndex; i < lineSize; i++)
	{
		if (line[i] == el)
		{
			break;
		}

		buffer[i - currentIndex] = line[i];
	}

	buffer[i - currentIndex] = '\0';
	argument = buffer;
	el == ' ' ? currentIndex = i : currentIndex = i + 1;

	delete[] buffer;
}

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, '\"');
}

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, ' ');
}

void readUnnecessaryLines(std::ifstream& sourceFile, MyString& line)
{
	while (!(line == SvgOpenTag))
	{
		line.readLine(sourceFile);
	}
}

void getShapeType(const MyString& line, MyString& type, size_t& lineSize, size_t& currentIndex)
{
	char* shapeType = new char[lineSize];
	size_t startIndex = getStartindex(line, lineSize);

	for (currentIndex = startIndex; currentIndex < lineSize; currentIndex++)
	{
		if (line[currentIndex] == ' ' || line[currentIndex] == '\t')
		{
			break;
		}

		shapeType[currentIndex - startIndex] = line[currentIndex];
	}

	shapeType[currentIndex - startIndex] = '\0';
	type = shapeType;

	delete[] shapeType;
}
