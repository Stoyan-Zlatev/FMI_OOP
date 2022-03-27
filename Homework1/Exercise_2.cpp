#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable:4996)

bool isPrefix(const char* text, const char* prefix)
{
	int i = 0;
	while (prefix[i] != '\0')
	{
		if (text[i] == '\0' || text[i] != prefix[i])
			return false;
		i++;
	}
	return true;
}

bool contains(const char* text, const char letter)
{
	for (size_t i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == letter)
			return true;
	}
	return false;
}

void getContent(const char* text, char* content, size_t startIndex)
{
	size_t textLength = strlen(text);
	for (size_t i = startIndex; i < textLength; i++)
	{
		if (isPrefix(text + i, "</"))
			return;
		content[i - startIndex] = text[i];
	}
}

enum Gender
{
	male,
	female
};

class Student
{
	char name[25];
	size_t fn;//unique
	size_t age;//[15,65]
	Gender gender;
	char email[25];//contains(@)
	double avg;//[2,6]
public:
	void setName(const char* name);
	void setFn(size_t fn);
	void setAge(size_t age);
	void setGender(Gender gender);
	void setEmail(const char* email);
	void setAvg(double avg);
};

void Student::setName(const char* name)
{
	if (strlen(name) > 25)
	{
		std::cout << "Entered name is too long";
		return;
	}
	strcpy(this->name, name);
}

void Student::setFn(size_t fn)
{
	//check if unique
	this->fn = fn;
}

void Student::setAge(size_t age)
{
	if (age > 65 || age < 15)
	{
		std::cout << "Invalid age!" << std::endl;
		return;
	}
	this->age = age;
}

void Student::setGender(Gender gender)
{
	this->gender = gender;
}

void Student::setEmail(const char* email)
{
	if (strlen(email) > 25)
		std::cout << "Email name is too long!" << std::endl;
	
	if (!contains(email, '@'))
		std::cout << "Email must contain '@'!" << std::endl;
	strcpy(this->email, email);
}

void Student::setAvg(double avg)
{
	if (avg < 2 || avg > 6)
	{
		std::cout << "Invalid average grade!" << std::endl;
	}
	this->avg = avg;
}

int main()
{
	const size_t maxStudents = 20;
	const size_t FieldsCount = 6;
	Student students[maxStudents];
	const size_t BUFF = 1024;
	char filePath[BUFF];
	std::cout << "Enter a file path:"<<std::endl;
	std::cout << ">";
	std::cin.getline(filePath, BUFF);
	std::fstream sourceFile(filePath, std::ios::out | std::ios::in | std::ios::app);
	char line[BUFF];
	size_t counter = 0;
	size_t fieldsCounter = 0;
	size_t tagLength;
	char content[BUFF];
	while (!sourceFile.eof())
	{
		sourceFile.getline(line, BUFF);
		if (isPrefix(line, "<student>"))
		{
			fieldsCounter = 0;
			while (!isPrefix(line, "</student>"))
			{
				if(isPrefix(line, "<grade>"))
				{ 
					tagLength = 7;
					fieldsCounter++;
					//Moje da ne e kontent a promenliva za vsqko otdelno
					getContent(line, content, tagLength);
				}
				else if (isPrefix(line, "<name>"))
				{
					tagLength = 6;
					fieldsCounter++;
				}
				else if (isPrefix(line, "<fn>"))
				{
					tagLength = 4;
					fieldsCounter++;

				}
				else if (isPrefix(line, "<age>"))
				{
					tagLength = 5;
					fieldsCounter++;
				}
				else if (isPrefix(line, "<gender>"))
				{
					tagLength = 8;
					fieldsCounter++;

				}
				else if (isPrefix(line, "<email>"))
				{
					tagLength = 7;
					fieldsCounter++;
				}
			}
			if(fieldsCounter = FieldsCount)
			counter++;
		}
	}
}
