#include <iostream>
#include <fstream>
#include <cstring>
#include "Exercise 2.h"
#include "GenderType.h"

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

	operate(students, studentsCounter, filePath, line);
}
