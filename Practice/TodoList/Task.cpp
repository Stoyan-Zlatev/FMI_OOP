#include "Task.h"
#include <cstring>
#include <iostream>
#pragma warning(disable:4996)

Task::Task() : Task("", "Low", "") {}

Task::Task(const char* name, const char* priority, const char* label)
{
	setName(name);
	setPriority(priority);
	setLabel(label);
	done = false;
}

void Task::setName(const char* name)
{
	if (name == nullptr)
		return;
	if (strlen(name) > 64)
	{
		std::cout << "Name is too long" << std::endl;
		return;
	}

	strcpy(this->name, name);
}

void Task::changeState()
{
	done = !done;
}

void Task::setPriority(const char* priority)
{
	if (strcmp(priority, "Low"))
		this->priority = Priority::LOW;
	else if (strcmp(priority, "High"))
		this->priority = Priority::HIGH;
	else if (strcmp(priority, "Medium"))
		this->priority = Priority::MEDIUM;
	else if (strcmp(priority, "Urgent"))
		this->priority = Priority::URGENT;
}

void Task::setLabel(const char* labelName)
{
	label = Label(labelName);
}

const char* Task::getName() const
{
	return name;
}

const char* Task::getPriority() const
{
	if (this->priority == Priority::LOW)
		return "Low";
	else if (this->priority == Priority::HIGH)
		return "High";
	else if (this->priority == Priority::MEDIUM)
		return "Medium";
	else if (this->priority == Priority::URGENT)
		return "Urgent";
}

const char* Task::getLabel() const
{
	return this->label.getName();
}

bool Task::isDone()
{
	return done;
}