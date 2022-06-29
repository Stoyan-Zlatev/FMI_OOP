#pragma once
#include "Person.h"

class Teacher : public Person
{
	char** subjects;
	size_t subjectsCount;

	void free();
	void copyFrom(const Teacher& other);// ���� ������, ����� �� �� Teacher
public:
	Teacher(const char* name, int age, const char* const* subjects, size_t subjectsCount);

	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);
	~Teacher();
};