#include "Book.h"
#include <cstring>
#pragma warning(disable:4996)

Book::Book() : Book("", "") {}

Book::Book(const char* title, const char* authorName)
{
	setTitle(title);
	setAuthorName(authorName);
}

void Book::setTitle(const char* title)
{
	if (title == nullptr)
	{
		return;
	}

	strcpy(this->title, title);
}
void Book::setAuthorName(const char* authorName)
{
	if (authorName == nullptr)
	{
		return;
	}

	strcpy(this->authorName, authorName);
}

void Book::setRating(size_t rating)
{
	if (rating < 0 || rating>10)
	{
		return;
	}

	this->rating = rating;
}

const char* Book::getTitle() const
{
	return title;
}
const char* Book::getAuthorName() const
{
	return authorName;
}
size_t Book::getRating() const
{
	return rating;
}

void Book::printComments() const
{
	for (size_t i = 0; i < comments.getCommentsCount(); i++)
	{
		comments.printComment(i);
	}
}

void Book::addComment(const char* username,const char* comment) 
{
	comments.addComment(Comment(username, comment));
}

