#pragma once
#include "Label.h"
const size_t MAXLABELSCOUNT = 100;

class LabelsCollection
{
	Label data[MAXLABELSCOUNT];
	size_t labelsCount;
public:
	LabelsCollection();
	void addLabel(const char* labelName);
	bool containsLabel(const char* labelName) const;
};