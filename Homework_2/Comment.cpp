#include "Comment.h"
#include "MyString.h"
#include <cstring>
#pragma warning(disable:4996)

Comment::Comment() : Comment("", "") {}

Comment::Comment(const MyString username, const MyString content)
{
	setUsername(username);
	setContent(content);
}

void Comment::setUsername(const MyString username)
{
	if (username.getSize() > MaxNameLength)
	{
		return;
	}

	this->username = username;
}

void Comment::setContent(const MyString content)
{
	if (content.getSize() > MaxContentLength)
	{
		return;
	}

	this->content = content;
}

const MyString Comment::getUserName() const
{
	return username;
}

const MyString Comment::getContent() const
{
	return content;
}