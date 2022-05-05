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

void Comment::saveToFile(std::fstream& file)
{
	/*MyString username;
	MyString content;*/
	size_t usernameSize = username.getSize();
	file.write((const char*)&usernameSize, sizeof(size_t));
	file.write((const char*)username.c_str(), sizeof(size_t));

	size_t contentSize = content.getSize();
	file.write((const char*)&contentSize, sizeof(size_t));
	file.write((const char*)content.c_str(), content.getSize());
}