#pragma once

class Person
{
	char* name;
	double* grades;
	size_t gradesCount;

	void copyFrom(const Person& other);
	void free();
	bool isValidName(const char* name) const;
	bool areValidGrades(const double* grades) const;
public: 
	Person();
	Person(const Person& other);
	Person& operator=(const Person& other);
	~Person();

	void setName(const char* name);
	void setGrades(const double* grades, size_t gradesCount);

	const char* getName() const;
	const double* getGrades() const;
};
