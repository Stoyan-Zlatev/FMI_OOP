#pragma once
class MyString
{
	char* str;
	size_t size;

	void copyFrom(const MyString& other);
	void free();
public:
	MyString();
	MyString(const char*);

	MyString(const MyString&);
	MyString& operator=(const MyString& other);
	~MyString();

	size_t getSize() const;
	const char* getString() const;
	void concat(const MyString& other);

	bool operator<(const MyString& other) const;
	bool operator==(const MyString& other) const;

	const char* c_str() const;
};
