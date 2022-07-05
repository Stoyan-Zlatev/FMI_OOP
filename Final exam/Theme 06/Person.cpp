#include "Person.h"
#include <cstring>

void Person::copyFrom(const Person& other)
{
	setName(other.name);
	setGrades(other.grades,other.gradesCount);
}

void Person::free()
{
	delete[] name, grades;
}
bool Person::isValidName(const char* name) const
{
	return (name != nullptr) && (name != this->name);
}
bool Person::areValidGrades(const double* grades) const
{
	return (grades != nullptr) && (grades != this->grades);
}
	Person::Person() : name(nullptr),grades(nullptr), gradesCount(0){}
	Person::Person(const Person& other)
	{
		copyFrom(other);
	}

	Person& Person::operator=(const Person& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}

		return *this;
	}

	Person::~Person()
	{
		free();
	}

	void Person::setName(const char* name)
	{
		if (!isValidName(name))
			return;

		this->name = new char[strlen(name)];
		strcpy(this->name, name);
	}

	void Person::setGrades(const double* grades, size_t gradesCount)
	{
		if (!areValidGrades(grades))
			return;

		this->grades = new double[gradesCount];
		for (size_t i = 0; i < gradesCount; i++)
			this->grades[i] = grades[i];

		this->gradesCount = gradesCount;
	}

	const char* Person::getName() const
	{
		return name;
	}

	const double* Person::getGrades() const
	{
		return grades;
	}
