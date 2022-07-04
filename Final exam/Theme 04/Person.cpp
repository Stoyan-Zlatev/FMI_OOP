#include <iostream>

const size_t MinAge = 5;
const size_t MaxAge = 90;
const size_t MaxNameLength = 20;

class Student
{
	char name[MaxNameLength + 1];
	size_t age;

	bool isValidAge(size_t age)
	{
		return age >= MinAge && age <= MaxAge;
	}

	bool isValidName(const char* name)
	{
		if (name == nullptr)
			return false;

		if (strlen(name) >= MaxNameLength)
			return false;

		return true;
	}
public:
	Student(const char* name, size_t age)
	{
		setName(name);
		setAge(age);
	}

	size_t getAge() const
	{
		return age;
	}

	const char* getName() const
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
