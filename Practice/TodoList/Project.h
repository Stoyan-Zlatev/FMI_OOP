#pragma once
#include "Task.h"
#include "LabelsCollection.h"

const size_t DEFAULT_ALLOCATED_CELLS = 8;

class Project
{
	Task* tasks;
	LabelsCollection labelsCollection;
	size_t tasksCount;
	size_t allocatedCellsCount;
	void resize();
	void copyFrom(const Project& otherProject);
	void free();
public:
	Project();
	~Project();
	Project(const Project& other);
	Project& operator=(const Project& other);

	void addTask(const char* taskName, const char* label);
	void addTask(const char* taskName, const char* label, const char* priority);
	bool containsTask(const char* taskName) const;

	//think about sorted unfinished(urgent, high, medium, low), finished(lex)
};