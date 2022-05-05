#pragma once
#include "GlobalConstants.h"
#include "MyString.h"

class Comment
{
	MyString username;
	MyString content;
	void setUsername(const MyString username);
public:
	Comment();
	Comment(const MyString username, const MyString content);

	void setContent(const MyString content);

	const MyString getUserName() const;
	const MyString getContent() const;
};