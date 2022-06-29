#include <iostream>
#pragma warning(disable:4996)
using namespace std;

const size_t MinAge = 5;
const size_t MaxAge = 90;
const size_t MaxNameLength = 20;

bool isSmallLetter(char ch)
{
	return ch >= 'a' && ch <= 'z';
}
bool isCapitalLetter(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}
bool containsOnlySmallChars(const char* str)
{
	size_t len = strlen(str);

	for (size_t i = 0; i < len; i++)
	{
		if (!isSmallLetter(str[i]))
			return false;
	}
	return true;
}

class Student
{
	char name[MaxNameLength];
	int age;

	bool isValidAge(int age)
	{
		return age >= MinAge && age <= MaxAge;
	}

	bool isValidName(const char* name)
	{
		if (name == nullptr)
			return false;

		if (strlen(name) >= MaxNameLength)
			return false;

		if (!isCapitalLetter(*name))
			return false;
		return containsOnlySmallChars(name + 1);
	}

public:
	Student(const char* name, int age)
	{
		setName(name);
		setAge(age);
	}

	int getAge() const //връщаме копие!!
	{
		return age;
	}

	const char* getName() const //копие на указателя!!!
	{
		return name;
	}

	void setName(const char* name)
	{
		if (isValidName(name))
			strcpy(this->name, name);
		else
			strcpy(this->name, "Unknown");

	}
	void setAge(int age)
	{
		if (isValidAge(age))
			this->age = age;
		else
			this->age = MinAge;
	}
};

int main()
{
	Student s("Ivan", 33);
}
