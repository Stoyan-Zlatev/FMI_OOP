#pragma once
#include "User.h"
#include "GlobalConstants.h"

class Comment
{
	char username[MaxNameLength];
	char content[MaxContentLength];
public:
	Comment();
	Comment(const char* username, const char* content);

	void setUsername(const char* username);
	void setContent(const char* content);

	const char* getUserName() const;
	const char* getContent() const;
};