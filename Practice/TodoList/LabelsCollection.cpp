#include "LabelsCollection.h"
#include <cstring>

LabelsCollection::LabelsCollection()
{
	labelsCount = 0;
}

bool LabelsCollection::containsLabel(const char* labelName) const
{
	for (size_t i = 0; i < labelsCount; i++)
	{
		if (strcmp(labelName, data[i].getName()) == 0)
			return true;
	}
	return false;
}

void LabelsCollection::addLabel(const char* labelName)
{
	if (!containsLabel(labelName))
	{
		data[labelsCount].setName(labelName);
		data[labelsCount].setId(labelsCount);
		labelsCount++;
	}
}

