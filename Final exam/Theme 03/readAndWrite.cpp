#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable:4996)

const size_t MAX_NAME_SIZE = 22;
struct Student
{
	char name[MAX_NAME_SIZE + 1];
	bool isMale;
	size_t fn;
};

void initStudent(Student& st, const char* name, size_t fn, bool isMale)
{
	if (name == nullptr || strlen(name) > MAX_NAME_SIZE)
		return;

	strcpy(st.name, name);
	st.isMale = isMale;
	st.fn = fn;
}

void saveToFile(const Student* students, size_t count, std::ofstream& file)
{
	file.write((const char*)students, count * sizeof(Student));
}

size_t getFileSize(std::ifstream& f)
{
	size_t currentPos = f.tellg();
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();

	f.seekg(currentPos);
	return size;
}

void readFromFile(Student*& ptr, size_t& studentsCount, std::ifstream& f)
{
	size_t sizeOfFile = getFileSize(f);
	studentsCount = sizeOfFile / sizeof(Student);
	ptr = new Student[studentsCount];
	f.read((char*)ptr, sizeOfFile);
}

int main()
{
	{
		const size_t studentsCount = 4;
		Student* arr = new Student[studentsCount];
		initStudent(arr[0], "Ivan", 1, true);
		initStudent(arr[1], "Petur", 2, true);
		initStudent(arr[2], "Alex", 3, true);
		initStudent(arr[3], "Katerina", 4, false);

		std::ofstream file("students.dat", std::ios::binary);

		if (!file.is_open())
		{
			std::cout << "Error while opening the file!" << std::endl;
			delete[] arr; //!
			return -1;
		}

		saveToFile(arr, studentsCount, file);

		delete[] arr;

		return 0;
	}
	{
		Student* arr;
		size_t count;
		std::ifstream file("students.dat", std::ios::binary);

		if (!file.is_open())
		{
			std::cout << "Error while opening the file!" << std::endl;
			return -1;
		}

		readFromFile(arr, count, file);

		for (int i = 0; i < count; i++)
			std::cout << "Name: " << arr[i].name << ", fn: " << arr[i].fn << ", is male: " << arr[i].isMale << std::endl;

		delete[] arr;

		return 0;
	}
}
