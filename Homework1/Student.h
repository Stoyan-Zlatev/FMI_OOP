#include "GenderType.h"
#include "Exercice_2.h"
#include <cstring>

#pragma warning(disable:4996)

class Student
{
	char name[25];
	int fn;//unique
	size_t age;//[15,65]
	GenderType gender;
	char email[25];//contains(@)
	double avg;//[2,6]
public:
	bool setName(const char* name);
	bool setFn(size_t fn);
	bool setAge(size_t age);
	bool setGender(GenderType gender);
	bool setEmail(const char* email);
	bool setAvg(double avg);

	const char* getName() const;
	int getFn() const;
	size_t getAge() const;
	GenderType getGender() const;
	const char* getEmail() const;
	double getAvg() const;
};
