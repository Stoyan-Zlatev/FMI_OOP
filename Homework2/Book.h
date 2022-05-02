#pragma once
#include "Page.h"
#include "CommentsCollection.h"
#include "GlobalConstants.h"
#include "PagesCollection.h"

class Book
{
	char title[MaxNameLength];
	char authorName[MaxNameLength];
	size_t rating;
	PagesCollection pages;
	size_t currentPageNumber;
	CommentsCollection comments;
public:
	Book();
	Book(const char* title, const char* authorName);

	void setTitle(const char* title);
	void setAuthorName(const char* authorName);
	void setRating(size_t rating);
	void setCurrentPageNumber(size_t currentPageNumber);
	void addComment(const char* username, const char* comment);

	const char* getTitle() const;
	const char* getAuthorName() const;
	size_t getRating() const;
	size_t getCurrentPageNumber() const;
	void printComments() const;

};