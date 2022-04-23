#include <cstring>
#include <iostream>
#include "Label.h"
#include "LabelsCollection.h"
#pragma warning(disable:4996)

Label::Label() : Label("") {}

Label::Label(const char* name)
{
	setName(name);
	setId(0);
}

void Label::setName(const char* name)
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

void Label::setId(size_t id)
{
	this->id = id;
}

const char* Label::getName() const
{
	return name;
}

size_t Label::getId() const
{
	return id;
}
