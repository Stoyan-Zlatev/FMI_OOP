#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable:4996)

const size_t maxFieldLength = 7;
const size_t BUFF = 1024;

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

size_t getNumberLength(size_t number)
{
	if (number == 0)
	{
		return 1;
	}
	size_t counter = 0;
	while (number != 0)
	{
		number /= 10;
		counter++;
	}
	return counter;
}

void getTagLength(const char* text, size_t& startIndex)
{
	while (text[startIndex] != '>' && text[startIndex] != '\0')
	{
		startIndex++;
	}

	if (text[startIndex] != '\0')
		startIndex++;
}

void getContent(const char* text, char* content, size_t& startIndex, bool& isFinishedLine)
{
	//check this!
	size_t textLength = strlen(text);
	if (textLength > 0)
	{
		size_t contentStartIndex = 0;
		getTagLength(text, contentStartIndex);
		size_t index = 0;
		for (contentStartIndex; contentStartIndex < textLength; contentStartIndex++)
		{
			if (isPrefix(text + contentStartIndex, "<\\"))
				break;
			content[index++] = text[contentStartIndex];
		}
		content[index] = '\0';
		getTagLength(text, contentStartIndex);
		startIndex += contentStartIndex;
		if (startIndex < textLength)
		{
			isFinishedLine = false;
			return;
		}
	}
	isFinishedLine = true;
}

void trimwhiteSpaces(const char* text, size_t& currentLineIndex)
{
	while (text[currentLineIndex] == ' ' || text[currentLineIndex] == '\t')
	{
		currentLineIndex++;
	}
}

bool isDigit(char element)
{
	return element >= '0' && element <= '9';
}

size_t parseCharToInt(char element)
{
	return element - '0';
}

enum class GenderType
{
	Male,
	Female,
	Unknown
};

const char* convertGenderToString(GenderType genderType)
{
	if (GenderType::Male == genderType)
		return "Male";
	else if (GenderType::Female == genderType)
		return "Female";
	else
		return "Unkown";
}

GenderType convertStringToGender(const char* str)
{
	if (strcmp(str, "Male") == 0)
		return GenderType::Male;
	else if (strcmp(str, "Female") == 0)
		return GenderType::Female;
	else
		return GenderType::Unknown;
}

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

bool Student::setName(const char* name)
{
	if (strlen(name) > 25)
	{
		std::cout << "Entered name is too long";
		return false;
	}
	strcpy(this->name, name);
	return true;
}

bool Student::setFn(size_t fn)
{
	this->fn = fn;
	return true;
}

bool Student::setAge(size_t age)
{
	if (age > 65 || age < 15)
	{
		std::cout << "Invalid age!" << std::endl;
		return false;
	}
	this->age = age;
	return true;
}

bool Student::setGender(GenderType gender)
{
	if (gender == GenderType::Unknown)
	{
		std::cout << "Invalid gender" << std::endl;
		return false;
	}
	this->gender = gender;
	return true;
}

bool Student::setEmail(const char* email)
{
	if (strlen(email) > 25)
	{
		std::cout << "Email name is too long!" << std::endl;
		return false;
	}

	if (!contains(email, '@'))
	{
		std::cout << "Email must contain '@'!" << std::endl;
		return false;
	}

	strcpy(this->email, email);
}

bool Student::setAvg(double avg)
{
	const size_t minGrade = 2;
	const size_t maxGrade = 6;

	if (avg < minGrade || avg > maxGrade)
	{
		std::cout << "Invalid average grade!" << std::endl;
		return false;
	}
	this->avg = avg;
	return true;
}

int Student::getFn() const
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

void swap(char*& element1, char*& element2)
{
	char* temp = element1;
	element1 = element2;
	element2 = temp;
}

void swap(double*& element1, double*& element2)
{
	double* temp = element1;
	element1 = element2;
	element2 = temp;
}

void swap(Student& a, Student& b)
{
	Student temp = a;
	a = b;
	b = temp;
}

double getNumberValue(const char* command, size_t& startIndex)
{
	double value = 0;
	while (isDigit(command[startIndex]))
	{
		value *= 10;
		value += parseCharToInt(command[startIndex]);
		startIndex++;
	}
	if (command[startIndex] == '.')
	{
		startIndex++;
		size_t divider = 10;
		while (isDigit(command[startIndex]))
		{
			value += (double)(parseCharToInt(command[startIndex])) / (double)divider;
			startIndex++;
			divider *= 10;
		}
	}
	return value;
}

void selectionSort(Student* students, char** stringArray, size_t studentCount)
{
	for (size_t i = 0; i < studentCount - 1; i++)
	{
		int minElementIndex = i;
		for (size_t j = i + 1; j < studentCount; j++)
		{
			if (strcmp(stringArray[j], stringArray[minElementIndex]) < 0)
				minElementIndex = j;
		}
		if (minElementIndex != i)
		{
			swap(stringArray[i], stringArray[minElementIndex]);
			swap(students[i], students[minElementIndex]);
		}
	}
}

bool isUniqueFn(Student* students, int fn, size_t studentsCount)
{
	for (size_t i = 0; i < studentsCount; i++)
	{
		if (fn == students[i].getFn())
			return false;
	}
	return true;
}


void selectionSort(Student* students, double* numberArray, size_t studentCount)
{
	for (size_t i = 0; i < studentCount - 1; i++)
	{
		int minElementIndex = i;
		for (size_t j = i + 1; j < studentCount; j++)
		{
			if (numberArray[j] < numberArray[minElementIndex])
				minElementIndex = j;
		}
		if (minElementIndex != i)
		{
			swap(numberArray, numberArray);
			swap(students[i], students[minElementIndex]);
		}
	}
}

void getStringValue(const char* command, char* field, size_t& startIndex)
{
	size_t index = 0;
	while (command[startIndex] != ' ' && command[startIndex] != '\t' && command[startIndex] != '\0')
	{
		field[index++] = command[startIndex++];
	}
	field[index] = '\0';
}

void sortNumber(Student* students, size_t studentsCount, const char* field)
{
	double* numberArray = new double[studentsCount];
	if (strcmp(field, "fn") == 0)
	{
		for (size_t i = 0; i < studentsCount; i++)
		{
			numberArray[i] = students[i].getFn();
		}
	}
	else if (strcmp(field, "grade") == 0)
	{
		for (size_t i = 0; i < studentsCount; i++)
		{
			numberArray[i] = students[i].getAvg();
		}
	}
	else if (strcmp(field, "age") == 0)
	{
		for (size_t i = 0; i < studentsCount; i++)
		{
			numberArray[i] = students[i].getAge();
		}
	}
	selectionSort(students, numberArray, studentsCount);
}

void sortString(Student* students, size_t studentsCount, const char* field)
{
	char** stringArray = new char* [studentsCount];
	if (strcmp(field, "name") == 0)
	{
		for (size_t i = 0; i < studentsCount; i++)
		{
			stringArray[i] = new char[strlen(students[i].getName())];
			strcpy(stringArray[i], students[i].getName());
		}
	}
	else if (strcmp(field, "email") == 0)
	{
		for (size_t i = 0; i < studentsCount; i++)
		{
			stringArray[i] = new char[strlen(students[i].getEmail())];
			strcpy(stringArray[i], students[i].getEmail());
		}
	}
	else if (strcmp(field, "gender") == 0)
	{
		for (size_t i = 0; i < studentsCount; i++)
		{
			stringArray[i] = new char[strlen(convertGenderToString(students[i].getGender()))];
			strcpy(stringArray[i], convertGenderToString(students[i].getGender()));
		}
	}
	selectionSort(students, stringArray, studentsCount);
}

void editNumber(size_t searchedIndex, size_t startIndex, const char* field, const char* command, Student* students, size_t studentsCount)
{
	double value = getNumberValue(command, startIndex);

	bool isExecuted = false;
	if (strcmp(field, "fn") == 0)
		if (isUniqueFn(students, value, studentsCount))
			isExecuted = students[searchedIndex].setFn(value);
		else
			std::cout << "There is already student with this fn" << std::endl;
	else if (strcmp(field, "grade") == 0)
		isExecuted = students[searchedIndex].setAvg(value);
	else if (strcmp(field, "age") == 0)
		isExecuted = students[searchedIndex].setAge(value);
	if (isExecuted)
		std::cout << "Operation successfully executed!" << std::endl;
}

void editString(size_t searchedIndex, size_t startIndex, const char* field, const char* command, Student* students)
{
	const size_t maxStringFieldLength = 25;
	char value[maxStringFieldLength];
	getStringValue(command, value, startIndex);

	bool isExecuted = false;
	if (strcmp(field, "name") == 0)
		isExecuted = students[searchedIndex].setName(value);
	else if (strcmp(field, "email") == 0)
		isExecuted = students[searchedIndex].setEmail(value);
	else if (strcmp(field, "gender") == 0)
		isExecuted = students[searchedIndex].setGender(convertStringToGender(value));
	std::cout << "Operation successfully executed!" << std::endl;

}

void sort(const char* command, Student* students, size_t studentsCount)
{
	const size_t commandMaxLength = 5;
	const size_t spaceSize = 1;
	char commandField[commandMaxLength];
	size_t startIndex = 0;
	getStringValue(command, commandField, startIndex);
	startIndex += spaceSize;
	char field[maxFieldLength];
	getStringValue(command, field, startIndex);
	if (strcmp(field, "fn") == 0 || strcmp(field, "grade") == 0 || strcmp(field, "age") == 0)
		sortNumber(students, studentsCount, field);
	else if (strcmp(field, "name") == 0 || strcmp(field, "email") == 0 || strcmp(field, "gender") == 0)
		sortString(students, studentsCount, field);
	else
	{
		std::cout << "Invalid field" << std::endl;
		return;
	}

	std::cout << "Operation successfully executed!" << std::endl;
}

void edit(const char* command, Student* students, size_t studentsCount)
{
	const size_t commandMaxLength = 5;
	const size_t spaceSize = 1;
	char commandField[commandMaxLength];
	size_t startIndex = 0;
	getStringValue(command, commandField, startIndex);
	startIndex += spaceSize;
	size_t fn = getNumberValue(command, startIndex);
	size_t fnLength = getNumberLength(fn);
	size_t searchedIndex = findByFn(students, fn, studentsCount);

	if (searchedIndex == -1)
	{
		std::cout << "Student not found" << std::endl;
		return;
	}

	startIndex += spaceSize;
	char field[maxFieldLength];
	getStringValue(command, field, startIndex);
	startIndex += spaceSize;
	if (strcmp(field, "fn") == 0 || strcmp(field, "grade") == 0 || strcmp(field, "age") == 0)
		editNumber(searchedIndex, startIndex, field, command, students, studentsCount);
	else if (strcmp(field, "name") == 0 || strcmp(field, "email") == 0 || strcmp(field, "gender") == 0)
		editString(searchedIndex, startIndex, field, command, students);
	else
	{
		std::cout << "Invalid field" << std::endl;
		return;
	}
}

void saveFile(const Student* students, const char* filePath, size_t studentsCounter)
{
	std::fstream resultFile(filePath, std::ios::trunc | std::ios::in | std::ios::out | std::ios::ate);
	for (size_t i = 0; i < studentsCounter; i++)
	{
		resultFile << "<student>\n";
		resultFile << "\t<name>";
		resultFile << students[i].getName();
		resultFile << "<\\name>\n";
		resultFile << "\t<fn>";
		resultFile << students[i].getFn();
		resultFile << "<\\fn>\n";
		resultFile << "\t<age>";
		resultFile << students[i].getAge();
		resultFile << "<\\age>\n";
		resultFile << "\t<gender>";
		resultFile << convertGenderToString(students[i].getGender());
		resultFile << "<\\gender>\n";
		resultFile << "\t<email>";
		resultFile << students[i].getEmail();
		resultFile << "<\\email>\n";
		resultFile << "\t<grade>";
		resultFile << students[i].getAvg();
		resultFile << "<\\grade>\n";
		resultFile << "<\\student>\n\n";
	}
	resultFile.close();
}

void change(std::fstream& sourceFile, Student* students, char* line, size_t& studentsCounter)
{
	const size_t FieldsCount = 6;
	size_t fieldsCounter = 0;
	size_t currentLineIndex = 0;
	size_t lastLineIndex = 0;
	char content[BUFF];
	bool isFinishedLine = false;
	while (!sourceFile.eof())
	{
		sourceFile.getline(line, BUFF);
		if (isPrefix(line, "<student>"))
		{
			Student student;
			fieldsCounter = 0;
			isFinishedLine = false;
			while (!isPrefix(line, "<\\student>"))
			{
				if (isFinishedLine)
				{
					currentLineIndex = 0;
					lastLineIndex = 0;
					sourceFile.getline(line, BUFF);
				}

				trimwhiteSpaces(line, currentLineIndex);
				lastLineIndex = currentLineIndex;
				getContent(line + currentLineIndex, content, currentLineIndex, isFinishedLine);

				if (isPrefix(line + lastLineIndex, "<grade>"))
				{
					size_t startIndex = 0;
					if (student.setAvg(getNumberValue(content, startIndex)))
						fieldsCounter++;
				}
				else if (isPrefix(line + lastLineIndex, "<name>"))
				{
					if (student.setName(content))
						fieldsCounter++;
				}
				else if (isPrefix(line + lastLineIndex, "<fn>"))
				{
					size_t startIndex = 0;
					int fn = getNumberValue(content, startIndex);
					if (isUniqueFn(students, fn, studentsCounter))
					{
						student.setFn(fn);
						fieldsCounter++;
					}
				}
				else if (isPrefix(line + lastLineIndex, "<age>"))
				{
					size_t startIndex = 0;
					if (student.setAge(getNumberValue(content, startIndex)))
						fieldsCounter++;
				}
				else if (isPrefix(line + lastLineIndex, "<gender>"))
				{
					if (student.setGender(convertStringToGender(content)))
						fieldsCounter++;
				}
				else if (isPrefix(line + lastLineIndex, "<email>"))
				{
					if (student.setEmail(content))
						fieldsCounter++;
				}
			}
			if (fieldsCounter == FieldsCount)
			{
				students[studentsCounter] = student;
				studentsCounter++;
			}
		}
	}
	sourceFile.close();
}

void printStudentsData(Student* students, size_t studentsCounter)
{
	for (unsigned i = 0; i < studentsCounter; i++)
	{
		std::cout << "Fn: " << students[i].getFn() << std::endl;
		std::cout << "Name: " << students[i].getName() << std::endl;
		std::cout << "Age: " << students[i].getAge() << std::endl;
		std::cout << "Gender: " << convertGenderToString(students[i].getGender()) << std::endl;
		std::cout << "Average grade: " << students[i].getAvg() << std::endl;
		std::cout << "Email: " << students[i].getEmail() << std::endl;
	}
}

int main()
{
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

	size_t studentsCounter = 0;
	char line[BUFF];
	const size_t maxStudents = 20;
	Student students[maxStudents];

	change(sourceFile, students, line, studentsCounter);

	std::cout << ">";
	std::cin.getline(line, BUFF);
	while (!isPrefix(line, "save"))
	{
		if (isPrefix(line, "edit"))
			edit(line, students, studentsCounter);
		else if (isPrefix(line, "sort"))
			sort(line, students, studentsCounter);
		else if (isPrefix(line, "print"))
			printStudentsData(students, studentsCounter);
		else
			std::cout << "Invalid command" << std::endl;
		std::cout << ">";
		std::cin.getline(line, BUFF);
	}
	saveFile(students, filePath, studentsCounter);
}
