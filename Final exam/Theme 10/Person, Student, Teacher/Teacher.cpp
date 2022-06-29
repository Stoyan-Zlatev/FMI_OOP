#include "Teacher.h"

#pragma warning (disable:4996)

Teacher::Teacher(const char* name, int age, const char* const* subjects, size_t subjectsCount) : Person(name, age)
{
	this->subjects = new char* [subjectsCount];

	for (size_t i = 0; i < subjectsCount; i++)
	{
		this->subjects[i] = new char[strlen(subjects[i]) + 1];
		strcpy(this->subjects[i], subjects[i]);
	}
	this->subjectsCount = subjectsCount;
}

void Teacher::free()
{
	for (size_t i = 0; i < subjectsCount; i++)
		delete[] subjects[i];
	delete[] subjects;
}
void Teacher::copyFrom(const Teacher& other)
{
	subjects = new char* [other.subjectsCount];

	for (size_t i = 0; i < other.subjectsCount; i++)
	{
		subjects[i] = new char[strlen(other.subjects[i]) + 1];
		strcpy(subjects[i], other.subjects[i]);
	}

	subjectsCount = other.subjectsCount;
}

Teacher::Teacher(const Teacher& other) : Person(other)
{
	copyFrom(other); //only the teacher stuff is copied
}

Teacher& Teacher::operator=(const Teacher& other)
{
	if (this != &other)
	{
		Person::operator=(other); //delete data of person + copy the data from person
		free(); //teacher
		copyFrom(other); //teacher
	}
	return *this;
}



Teacher::~Teacher()
{
	free();
} // destr person