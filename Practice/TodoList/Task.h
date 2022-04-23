#pragma once
#include "Label.h"
#include "Priority.h"

class Task
{
	char name[MAXNAMELENGTH];
	Priority priority;
	Label label;
	bool done;
public:
	Task();
	Task(const char* name, const char* priority, const char* label);

	void setName(const char* name);
	void changeState();
	void setPriority(const char* priority);
	void setLabel(const char* label);

	const char* getName() const;
	const char* getPriority() const;
	const char* getLabel() const;
	bool isDone();
};