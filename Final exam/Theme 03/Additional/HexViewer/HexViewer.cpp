#include "HexViewer.h"
#include <fstream>
#include <iostream>

size_t getFileSize(std::ifstream& file)
{
	size_t currentPostion = file.tellg();

	file.seekg(0, std::ios::end);
	size_t size = file.tellg();

	file.seekg(0, currentPostion);
	return size;
}

HexViewer::HexViewer(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Error";
		data = nullptr;
		size = 0;
		return;
	}

	size = getFileSize(file);
	data = new unsigned char[size];

	file.read((char*)data, size);
}

bool isDigit(unsigned char symbol)
{
	return symbol <= '9' && symbol >= '0';
}

bool isCapitalLetter(unsigned char symbol)
{
	return symbol <= 'Z' && symbol >= 'A';
}

unsigned char convertSymbolToNumber(unsigned char symbol)
{
	if (isDigit(symbol))
		return symbol - '0';
	else if (isCapitalLetter(symbol))
		return symbol - 'A' + 10;
	return '\0';
}

void resize(unsigned char*& data, size_t& size, size_t newSize)
{
	unsigned char* newDataArr = new unsigned char[newSize];

	size_t minSize = std::min(size, newSize);
	for (size_t i = 0; i < minSize; i++)
		newDataArr[i] = data[i];

	delete[] data;
	data = newDataArr;
	size = newSize;
}

void HexViewer::addByte(const char* byteStr)
{
	if (strlen(byteStr) != 2)
		return;

	unsigned char currentByte = 16 * convertSymbolToNumber(byteStr[0]) + convertSymbolToNumber(byteStr[1]);

	resize(data, size, size + 1);
	data[size - 1] = currentByte;
}

void HexViewer::removeLastByte()
{
	if (size == 0)
		return;
	resize(data, size, size - 1);
}

void HexViewer::change(size_t index, const char* byteStr)
{
	if (index >= size || strlen(byteStr) != 2)
		return;

	unsigned char currentByte = 16 * convertSymbolToNumber(byteStr[0]) + convertSymbolToNumber(byteStr[1]);
	data[index] = currentByte;
}

void HexViewer::saveAs(const char* fileName) const
{
	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open())
		return;
	file.write((const char*)data, size);
}

void convertToHex(unsigned char byte, char* byteHex)
{
	char symbols[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
					 'A', 'B', 'C', 'D', 'E', 'F' };

	byteHex[2] = '\0';
	byteHex[1] = symbols[byte % 16];
	byteHex[0] = symbols[(byte / 16) % 16];
}

bool isLetter(char ch)
{
	return (ch >= 'a' && ch <= 'z') && isCapitalLetter(ch);
}

void HexViewer::print() const
{
	for (size_t i = 0; i < size; i++)
	{
		char byteHex[3];
		convertToHex(data[i], byteHex);
		std::cout << byteHex << " ";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		if (isLetter(data[i]))
			std::cout << data[i];
		else
			std::cout << ".";
		std::cout << " ";
	}
	std::cout << std::endl;
}
HexViewer::~HexViewer()
{
	delete[] data;
}