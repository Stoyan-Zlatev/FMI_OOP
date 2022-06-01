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

size_t getNumSize(int number)
{
	size_t counter = 0;
	while (number != 0)
	{
		counter++;
		number /= 10;
	}

	return counter;
}

void swap(char& el1, char& el2)
{
	char temp = el1;
	el1 = el2;
	el2 = temp;
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

	if (buffer[0] != '\0')
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

MyString parseDoubleToString(double value)
{
	//To get the part before decimal point and two digits after the decimal point
	int temp = abs(value * 100);
	size_t tempLength = getNumSize(temp);
	size_t index = 0;

	char* buffer;
	value < 0 ? buffer = new char[tempLength + 3] : buffer = new char[tempLength + 2];

	for (size_t i = 0; i < 2; i++)
	{
		buffer[index++] = parseIntToChar(temp % 10);
		temp /= 10;
	}

	buffer[index++] = '.';

	while (temp != 0)
	{
		buffer[index++] = parseIntToChar(temp % 10);
		temp /= 10;
	}

	if (value < 0)
	{
		buffer[tempLength + 1] = '-';
		buffer[tempLength + 2] = '\0';
	}
	else
	{
		buffer[tempLength + 1] = '\0';
	}

	MyString doubleValue = buffer;
	delete[] buffer;

	return doubleValue.reverse();
}

char parseIntToChar(size_t value)
{
	if (value > 9)
	{
		throw std::invalid_argument("Invalid argument to parse digit\n");
	}

	return value + '0';
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
