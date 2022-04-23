#include "Project.h"
#include <cstring>
#include <iostream>

void Project::copyFrom(const Project& other)
{
	tasks = new Task[other.allocatedCellsCount];
	for (size_t i = 0; i < other.allocatedCellsCount; i++)
	{
		tasks[i] = other.tasks[i];
	}

	tasksCount = other.tasksCount;
	allocatedCellsCount = other.allocatedCellsCount;
}

void Project::free()
{
	delete[] this->tasks;
	tasksCount = 0;
	allocatedCellsCount = DEFAULT_ALLOCATED_CELLS;
}

void Project::resize()
{
	allocatedCellsCount *= 2;
	Task* newData = new Task[allocatedCellsCount];

	for (int i = 0; i < tasksCount; i++) {
		newData[i] = tasks[i];
	}

	delete[] tasks;
	tasks = newData;
}

Project::Project()
{
	tasks = new Task[DEFAULT_ALLOCATED_CELLS];
	allocatedCellsCount = DEFAULT_ALLOCATED_CELLS;
	tasksCount = 0;
}


Project::Project(const Project& other)
{
	copyFrom(other);
}

Project& Project::operator=(const Project& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Project::~Project()
{
	free();
}

void Project::addTask(const char* taskName, const char* label)
{
	addTask(taskName, label, "Low");
}

void Project::addTask(const char* taskName, const char* label, const char* priority)
{
	if (!containsTask(taskName))
	{
		if (tasksCount >= allocatedCellsCount)
			resize();

		tasks[tasksCount - 1] = Task(taskName, priority, label);
		tasksCount++;
	}
	else
		std::cout << "This task already exists!" << std::endl;
}

bool Project::containsTask(const char* taskName) const
{
	for (size_t i = 0; i < tasksCount; i++)
	{
		if (strcmp(tasks[i].getName(), taskName) == 0)
			return true;
	}

	return false;
}