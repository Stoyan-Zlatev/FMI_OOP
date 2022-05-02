#include "Comment.h"
#include <cstring>
#pragma warning(disable:4996)

Comment::Comment() : Comment("", ""){}

Comment::Comment(const char* username, const char* content)
{
	setUsername(username);
	setContent(content);
}

void Comment::setUsername(const char* username)
{
	if (strlen(username) > MaxNameLength)
	{
		return;
	}

	strcpy(this->username, username);
}

void Comment::setContent(const char* content)
{
	if (strlen(content) > MaxContentLength)
	{
		return;
	}

	strcpy(this->content, content);
}

const char* Comment::getUserName() const
{
	return username;
}

const char* Comment::getContent() const
{
	return content;
}