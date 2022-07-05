#include <iostream>
#include <cstring>

#pragma warning(disable:4996)

const size_t MAX_NAME_SIZE = 20;
const size_t MAX_AGE = 90;
const size_t MIN_AGE = 5;

class Person
{
	char name[MAX_NAME_SIZE + 1];
	size_t age;

	bool isValidName(const char* name)
	{
		return (name != nullptr) && strlen(name) <= MAX_NAME_SIZE;
	}

	bool isValidAge(size_t age)
	{
		return age <= MAX_AGE && age >= MIN_AGE;
	}
public:
	Person(const char* name, size_t age)
	{
		setName(name);
		setAge(age);
	}

	void setName(const char* name)
	{
		if (isValidName(name))
			strcpy(this->name, name);
		else
			strcpy(this->name, "Unknown");
	}

	void setAge(size_t age)
	{
		if (isValidAge(age))
			this->age = age;
		else
			this->age = MIN_AGE;

	}

	const char* getName() const
	{
		return name;
	}

	size_t getAge() const
	{
		return age;
	}
};

int main()
{
	Person p1("Ivan", 13);//OK
	Person p2("Ivan", 95);//Error 95>90
	Person p3("Anastasius Papastopolus", 50);//Unknown
	std::cout << p3.getName();
}
