#pragma once
#include "Page.h"
#include "CommentsCollection.h"
#include "Comment.h"
#include "GlobalConstants.h"
#include "PagesCollection.h"

class Book
{
	char title[MaxNameLength];
	char authorName[MaxNameLength];
	size_t rating;
	PagesCollection pages;
	CommentsCollection comments;
public:
	Book();
	Book(const char* title, const char* authorName);

	void setTitle(const char* title);
	void setAuthorName(const char* authorName);
	void setRating(size_t rating);
	void addComment(const char* username, const char* comment);

	const char* getTitle() const;
	const char* getAuthorName() const;
	size_t getRating() const;
	void printComments() const;
};