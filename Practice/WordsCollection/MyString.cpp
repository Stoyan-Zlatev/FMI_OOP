#include "MyString.h"
#include <cstring>
#include <iostream>

void MyString::copyFrom(const MyString& other)
{
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
	size = other.size;
}
void MyString::free()
{
	delete[] str;
}

MyString::MyString()
{
	str = new char[1];
	str[0] = '\0';
	size = 0;
}

MyString::MyString(const char* data)
{
	if(data == nullptr)
	{
		str = new char[1];
		str[0] = '\0';
		size = 0;
	}
	else
	{
		size = strlen(data);
		str = new char[size + 1];
		strcpy(str, data);
	}
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}
MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
MyString::~MyString()
{
	free();
}


size_t MyString::getSize() const
{
	return size;
}
void MyString::concat(const MyString& other)
{
	char* temp = new char[getSize() + other.getSize() + 1];
	strcpy(temp, str);
	strcat(temp, other.str);

	delete[] str;
	str = temp;
	size = size + other.getSize();
}

const char* MyString::c_str() const
{
	return str;
}

MyString& MyString::operator+=(const MyString& other)
{
	concat(other);
	return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString copyOfLeft(lhs);
	copyOfLeft += rhs;
	return copyOfLeft;
}

std::ostream& operator<<(std::ostream& stream, const MyString& str)
{
	stream << str.str;
	return stream;
}

std::istream& operator>>(std::istream& stream, MyString& str)
{
	delete[] str.str;
	char buff[1024];
	stream >> buff;

	str.size = strlen(buff);
	str.str = new char[str.size + 1];
	strcpy(str.str, buff);

	return stream;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;

}
bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;

}

MyString::MyString(MyString&& otherString)
{
	str = otherString.str;
	size = otherString.size;
	otherString.str = nullptr;
	std::cout << "move constr" << std::endl;
}

MyString& MyString::operator=(MyString&& otherString)
{
	if (this != &otherString)
	{
		free();
		str = otherString.str;
		otherString.str = nullptr;
		size = otherString.size;
	}
	return *this;
}
