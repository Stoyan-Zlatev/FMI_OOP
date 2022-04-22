#pragma once
const size_t MAXNAMELENGTH = 64;
class Label
{
	char name[MAXNAMELENGTH];
	size_t id;
public:
	Label();
	Label(const char* name);
	
	void setName(const char* name);
	void setId(size_t id);

	const char* getName() const;
	size_t getId() const;
};