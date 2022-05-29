#include "Utils.h"
#include "GlobalConstants.h"
#include <iostream>

bool isPrefix(const MyString& text, const MyString& prefix)
{
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

	throw std::invalid_argument("Incorrect line in file!\n");
}

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, ' ', ' ');
}

void getTranslateArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, '=', ' ');
}

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, '\"', '\"');
}

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument, char startSeparator, char endSeparator)
{
	for (currentIndex; currentIndex < lineSize; currentIndex++)
	{
		if (line[currentIndex] == startSeparator)
		{
			break;
		}
	}

	currentIndex++;
	char* buffer = new char[lineSize];
	size_t i = 0;
	for (i = currentIndex; i < lineSize; i++)
	{
		if (line[i] == endSeparator)
		{
			break;
		}

		buffer[i - currentIndex] = line[i];
	}

	buffer[i - currentIndex] = '\0';

	if (strlen(buffer) > 0)
	{
		argument = std::atof(buffer);
		endSeparator == ' ' ? currentIndex = i : currentIndex = i + 1;
	}

	delete[] buffer;
}

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument, char startSeparator, char endSeparator)
{
	for (currentIndex; currentIndex < lineSize; currentIndex++)
	{
		if (line[currentIndex] == startSeparator)
		{
			break;
		}
	}

	currentIndex++;
	char* buffer = new char[lineSize];
	size_t i = 0;
	for (i = currentIndex; i < lineSize; i++)
	{
		if (line[i] == endSeparator)
		{
			break;
		}

		buffer[i - currentIndex] = line[i];
	}

	buffer[i - currentIndex] = '\0';
	argument = buffer;
	endSeparator == ' ' ? currentIndex = i : currentIndex = i + 1;

	delete[] buffer;
}

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, '\"', '\"');
}

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, ' ', ' ');
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
