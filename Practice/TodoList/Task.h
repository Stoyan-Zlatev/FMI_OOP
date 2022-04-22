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
};