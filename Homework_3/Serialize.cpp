#include "Serialize.h"
#include "Utils.h"
#include "Shape.h"

void writeString(std::ofstream& sourceFile, const MyString& str) {
	int len = str.getSize();
	sourceFile.write((const char*)&len, sizeof(int));

	sourceFile.write(str.c_str(), sizeof(char) * len);
}

void readString(std::ifstream& sourceFile, MyString& field) {
	int len = 0;
	sourceFile.read((char*)&len, sizeof(len));

	char* buff = new char[len + 1];
	sourceFile.read(buff, sizeof(char) * len);

	buff[len] = '\0';

	field = buff;

	delete[] buff;
}

void saveCircle(std::ofstream& file, double& cx, double& cy, double& radius, const MyString& color)
{
	file << " <circle cx=\"";
	file << cx;
	file << "\" cy=\"";
	file << cy;
	file << "\" r=\"";
	file << radius;
	file << "\" fill=\"" + color + "\" />\n";
}

void readCircle(const MyString& line, size_t& lineSize, size_t& currentIndex, double& cx, double& cy, double& radius, MyString& color)
{
	loadArgument(line, lineSize, currentIndex, cx);
	loadArgument(line, lineSize, currentIndex, cy);
	loadArgument(line, lineSize, currentIndex, radius);
	loadArgument(line, lineSize, currentIndex, color);
}

void saveRectangle(std::ofstream& file, double& x, double& y, double& width, double& height, const MyString& color)
{
	file << " <rect x=\"";
	file << x;
	file << "\" cy=\"";
	file << y;
	file << "\" width=\"";
	file << width;
	file << "\" height=\"";
	file << height;
	file << "\" fill=\"" + color + "\" />\n";
}

void readRectangle(const MyString& line, size_t& lineSize, size_t& currentIndex, double& x, double& y, double& width, double& height, MyString& color)
{
	loadArgument(line, lineSize, currentIndex, x);
	loadArgument(line, lineSize, currentIndex, y);
	loadArgument(line, lineSize, currentIndex, width);
	loadArgument(line, lineSize, currentIndex, height);
	loadArgument(line, lineSize, currentIndex, color);
}

void saveLine(std::ofstream& file, double& x1, double& y1, double& x2, double& y2, const MyString& color)
{
	file << " <line x1=\"";
	file << x1;
	file << "\" y1=\"";
	file << y1;
	file << "\" x2=\"";
	file << x2;
	file << "\" y2=\"";
	file << y2;
	file << "\" fill=\"" + color + "\" />\n";
}

void readLine(const MyString& line,size_t& lineSize, size_t& currentIndex, double& x1, double& y1, double& x2, double& y2, MyString& color)
{
	loadArgument(line, lineSize, currentIndex, x1);
	loadArgument(line, lineSize, currentIndex, y1);
	loadArgument(line, lineSize, currentIndex, x2);
	loadArgument(line, lineSize, currentIndex, y2);
	loadArgument(line, lineSize, currentIndex, color);
}

void saveHeaders(std::ofstream& file, const Collection<MyString>& headers)
{
	for (size_t i = 0; i < headers.getCount(); i++)
	{
		file << headers.getElementAt(i)<<"\n";
	}
}
