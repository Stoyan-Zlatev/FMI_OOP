#pragma once
#include "Page.h"
#include "Comment.h"
#include "GlobalConstants.h"
#include "MyString.h"
#include "Collection.hpp"
#include "UserRating.h"

class Book
{
	MyString title;
	MyString authorName;
	Collection<UserRating> ratings;
	Collection<Page> pages;
	Collection<Comment> comments;
	void setTitle(const MyString& title);
	void setAuthorName(const MyString& authorName);
	double sumRating() const;
public:
	Book();
	Book(const MyString& title, const MyString& authorName);

	void rate(const MyString& username, int rating);
	void addComment(const MyString& username, const MyString& comment);
	void addPage(const MyString& content, size_t pageNumber);
	void removeLastPage();

	const MyString getTitle() const;
	const MyString getAuthorName() const;
	double getRating() const;
	void printPageByIndex(int index) const;
	void printComments() const;
	void printRatings() const;
	size_t getPagesCount() const;
};