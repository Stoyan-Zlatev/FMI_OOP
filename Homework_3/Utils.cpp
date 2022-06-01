#include "Utils.h"
#include "Parser.h"
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

void loadFigures(const MyString& path, ShapeCollection& shapes, Collection<MyString>& headers)
{
	std::ifstream sourceFile(path.c_str());

	shapes;
	if (!sourceFile.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
	}
	else
	{
		readUnnecessaryLines(sourceFile, headers);
		shapes.load(sourceFile);
		std::cout << "File loaded successfully" << std::endl;
	}

	sourceFile.close();
}


void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, '\"', '\"');
}



void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, '\"', '\"');
}

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, ' ', ' ');
}

void readUnnecessaryLines(std::ifstream& sourceFile, Collection<MyString>& headers)
{
	MyString line;
	line.getline(sourceFile);
	while (!(line == SvgOpenTag))
	{
		headers.add(line);
		line.getline(sourceFile);
	}
}

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, ' ', ' ');
}

void getTranslateArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument)
{
	parseArgument(line, lineSize, currentIndex, argument, '=', ' ');
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
