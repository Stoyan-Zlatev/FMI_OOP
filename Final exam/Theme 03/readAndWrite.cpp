#include <iostream>
#include <cstring>
#include <fstream>

const size_t MAX_NAME_SIZE = 22;
struct Student
{
	char name[MAX_NAME_SIZE + 1];
	bool isMale;
	size_t fn;
};

void initStudent(Student& st, const char* name, bool isMale, size_t fn)
{
	if (name == nullptr || strlen(name) > MAX_NAME_SIZE)
		return;

	strcpy(st.name, name);
	st.isMale = isMale;
	st.fn = fn;
}

void saveToFile(std::ofstream& file, const Student* students, size_t studentsCount)
{
	file.write((const char*)students, studentsCount * sizeof(Student));
}

size_t getFileSize(std::ifstream& file)
{
	size_t currPos = file.tellg();
	file.seekg(0, std::ios::end);

	size_t size = file.tellg();
	file.seekg(currPos);

	return size;
}

void readFromFile(std::ifstream& file, const Student* students)
{
	size_t studentsCount = getFileSize(file) / sizeof(Student);
	students = new Student[studentsCount];
	file.read((char*)students, studentsCount * sizeof(Student));
}

int main()
{
	{
		const size_t studentsCount = 3;
		Student* students = new Student[studentsCount];
		initStudent(students[0], "Ivan", true, 2);
		initStudent(students[1], "Peter", true, 3);
		initStudent(students[2], "Ivana", false, 4);

		std::ofstream file("students.dat", std::ios::binary);

		if (!file.is_open())
		{
			std::cout << "Error, opening the file!";
			delete[] students;
			return -1;
		}

		saveToFile(file, students, studentsCount);

		delete[] students;
		return 0;
	}
	{
		Student* students;

		std::ifstream file("students.dat", std::ios::binary);

		if (!file.is_open())
		{
			std::cout << "Error, opening the file!";
			delete[] students;
			return -1;
		}

		readFromFile(file, students);

		delete[] students;
		return 0;
	}
}
