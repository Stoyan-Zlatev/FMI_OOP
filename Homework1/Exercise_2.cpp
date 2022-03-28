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

void getTagLength(const char* text, size_t& startIndex)
{
	while (text[startIndex] != '>')
	{
		startIndex++;
	}
	startIndex++;
}

void getContent(const char* text, char* content, size_t& startIndex, bool& isFinishedLine)
{
	getTagLength(text, startIndex);
	size_t textLength = strlen(text);
	size_t contentIndex = 0;
	for (startIndex; startIndex < textLength; startIndex++)
	{
		if (isPrefix(text + startIndex, "<\\"))
			break;
		content[contentIndex++] = text[startIndex];
	}
	content[contentIndex] = '\0';
	getTagLength(text, startIndex);
	if (startIndex < textLength)
		isFinishedLine = false;
	else
		isFinishedLine = true;
}

void swap(char& element1, char& element2)
{
	char temp = element1;
	element1 = element2;
	element2 = temp;
}

void trimWhiteSpaces(char* text)
{
	size_t index = 0;
	size_t frontSpaces = 0;
	while (text[index] == ' ' || text[index] == '\t')
	{
		index++;
		frontSpaces++;
	}
	size_t textLength = strlen(text);
	size_t backSpaces = 0;
	for (size_t i = textLength - 1; (text[i] == ' ' || text[index] == '\t'); i--)
	{
		backSpaces++;
	}
	size_t newLength = textLength - (frontSpaces + backSpaces);
	char* resultText = new char[newLength];
	if (frontSpaces > 0)
		for (size_t i = 0; i < newLength; i++)
		{
			swap(text[i], text[i + frontSpaces]);
		}
	text[newLength] = '\0';
}

bool isDigit(char element)
{
	return element >= '0' && element <= '9';
}

size_t parseCharToInt(char element)
{
	return element - '0';
}

double parseStringToDouble(const char* content)
{
	double grade = 0;
	size_t index = 0;
	while (content[index] != '.')
	{
		if (isDigit(content[index]))
		{
			grade *= 10;
			grade += parseCharToInt(content[index]);
			index++;
		}
	}
	index++;
	double divider = 10;
	while (content[index] != '\0')
	{
		if (isDigit(content[index]))
		{
			grade += ((double)parseCharToInt(content[index])) / divider;
			index++;
		}
	}
	return grade;
}

size_t parseStringToInt(const char* content)
{
	double number = 0;
	size_t index = 0;
	while (content[index] != '\0')
	{
		if (isDigit(content[index]))
		{
			number *= 10;
			number += parseCharToInt(content[index]);
			index++;
		}
	}

	return number;
}

enum class GenderType
{
	Male,
	Female,
};

const char* convertGenderToString(GenderType genderType)
{
	if (GenderType::Male == genderType)
		return "Male";
	else if (GenderType::Female == genderType)
		return "Female";
}

GenderType convertStringToGender(const char* str)
{
	if (str == "Male")
		return GenderType::Male;
	else if (str == "Female")
		return GenderType::Female;
}

class Student
{
	char name[25];
	size_t fn;//unique
	size_t age;//[15,65]
	GenderType gender;
	char email[25];//contains(@)
	double avg;//[2,6]
public:
	void setName(const char* name);
	void setFn(size_t fn);
	void setAge(size_t age);
	void setGender(GenderType gender);
	void setEmail(const char* email);
	void setAvg(double avg);

	const char* getName() const;
	size_t getFn() const;
	size_t getAge() const;
	GenderType getGender() const;
	const char* getEmail() const;
	double getAvg() const;
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

void Student::setGender(GenderType gender)
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
	const size_t minGrade = 2;
	const size_t maxGrade = 6;

	if (avg < minGrade || avg > maxGrade)
	{
		std::cout << "Invalid average grade!" << std::endl;
	}
	this->avg = avg;
}

size_t Student::getFn() const
{
	return this->fn;
}

size_t Student::getAge() const
{
	return this->age;
}

GenderType Student::getGender() const
{
	return this->gender;
}

const char* Student::getName() const
{
	return this->name;
}

const char* Student::getEmail() const
{
	return this->email;
}

double Student::getAvg() const
{
	return this->avg;
}

int findByFn(Student* students, size_t fn, size_t studentsCount)
{
	for (size_t i = 0; i < studentsCount; i++)
	{
		if (students[i].getFn() == fn)
			return i;
	}
	return -1;
}

void swap(Student& a, Student& b)
{
	Student temp = a;
	a = b;
	b = temp;
}

void selectionSort(Student* students, size_t studentCount)
{
	for (size_t i = 0; i < studentCount - 1; i++)
	{
		int minElementIndex = i;
		for (size_t j = i + 1; j < studentCount; j++)
		{
			if (students[j].getFn() < students[minElementIndex].getFn())
				minElementIndex = j;
		}
		if (minElementIndex != i)
			swap(students[i], students[minElementIndex]);
	}
}

void orderByFn(Student* students, size_t fn, size_t studentsCount)
{
	size_t searchedIndex = findByFn(students, fn, studentsCount);
	if (searchedIndex == -1)
	{
		std::cout << "Student not found" << std::endl;
		return;
	}
	selectionSort(students, studentsCount);
}

//Do a parent function that searches by fn and edit by number and string and sort by number and string
void editNumber(Student* students, double number, size_t fn, size_t studentsCount)
{
	size_t searchedIndex = findByFn(students, fn, studentsCount);
	if (searchedIndex == -1)
	{
		std::cout << "Student not found" << std::endl;
		return;
	}


	students[searchedIndex].setFn(fn);
}

void saveFile(const Student* students, const char* filePath, size_t studentsCounter)
{
	std::fstream resultFile(filePath, std::ios::trunc | std::ios::out | std::ios::app);
	for (size_t i = 0; i < studentsCounter; i++)
	{
		resultFile << "<student>\n";
		resultFile << "\t<name>";
		resultFile << students[i].getName();
		resultFile << "</name>\n";
		resultFile << "\t<fn>";
		resultFile << students[i].getFn();
		resultFile << "</fn>\n";
		resultFile << "\t<age>";
		resultFile << students[i].getAge();
		resultFile << "</age>\n";
		resultFile << "\t<gender>";
		resultFile << convertGenderToString(students[i].getGender());
		resultFile << "</gender>\n";
		resultFile << "\t<email>";
		resultFile << students[i].getEmail();
		resultFile << "</email>\n";
		resultFile << "\t<grade>";
		resultFile << students[i].getAvg();
		resultFile << "</grade>\n";
		resultFile << "</student>\n\n";
	}
	resultFile.close();
}

int main()
{
	const size_t maxStudents = 20;
	const size_t FieldsCount = 6;
	Student students[maxStudents];
	const size_t BUFF = 1024;
	char filePath[BUFF];
	std::cout << "Enter a file path:" << std::endl;
	std::cout << ">";
	std::cin.getline(filePath, BUFF);
	std::fstream sourceFile(filePath, std::ios::out | std::ios::in | std::ios::app);

	if (!sourceFile.is_open())
	{
		std::cout << "Error" << std::endl;
		return -1;
	}

	std::cout << "File loaded successfully!" << std::endl;

	char line[BUFF];
	size_t studentsCounter = 0;
	size_t fieldsCounter = 0;
	size_t currentLineIndex = 0;;
	char content[BUFF];
	bool isFinishedLine = true;
	while (!sourceFile.eof())
	{
		sourceFile.getline(line, BUFF);
		if (isPrefix(line, "<student>"))
		{
			Student student;
			fieldsCounter = 0;
			while (!isPrefix(line, "<\\student>"))
			{
				if (isFinishedLine)
				{
					currentLineIndex = 0;
					sourceFile.getline(line, BUFF);
				}
				if (isPrefix(line + currentLineIndex, "<grade>"))
				{
					fieldsCounter++;
					getContent(line, content, currentLineIndex, isFinishedLine);
					trimWhiteSpaces(content);
					student.setAvg(parseStringToDouble(content));
				}
				else if (isPrefix(line + currentLineIndex, "<name>"))
				{
					fieldsCounter++;
					getContent(line, content, currentLineIndex, isFinishedLine);
					trimWhiteSpaces(content);
					student.setName(content);
				}
				else if (isPrefix(line + currentLineIndex, "<fn>"))
				{
					fieldsCounter++;
					getContent(line, content, currentLineIndex, isFinishedLine);
					trimWhiteSpaces(content);
					student.setFn(parseStringToInt(content));
				}
				else if (isPrefix(line + currentLineIndex, "<age>"))
				{
					fieldsCounter++;
					getContent(line, content, currentLineIndex, isFinishedLine);
					trimWhiteSpaces(content);
					student.setAge(parseStringToInt(content));
				}
				else if (isPrefix(line + currentLineIndex, "<gender>"))
				{
					fieldsCounter++;
					getContent(line, content, currentLineIndex, isFinishedLine);
					trimWhiteSpaces(content);
					student.setGender(convertStringToGender(content));
				}
				else if (isPrefix(line + currentLineIndex, "<email>"))
				{
					fieldsCounter++;
					getContent(line, content, currentLineIndex, isFinishedLine);
					trimWhiteSpaces(content);
					student.setEmail(content);
				}
			}
			if (fieldsCounter == FieldsCount)
			{
				students[studentsCounter] = student;
				studentsCounter++;
			}
		}
	}

	saveFile(students, filePath, studentsCounter);
}
