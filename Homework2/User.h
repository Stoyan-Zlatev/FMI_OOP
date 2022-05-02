#pragma once
#include "BooksCollection.h"
#include "GlobalConstants.h"

class User
{
	char name[MaxNameLength];
	char password[MaxNameLength];
	BooksCollection readBooks;
	BooksCollection writenBooks;
	void setName(const char* name);
	void setPassword(const char* password);
public:
	User();
	User(const char* name, const char* password);

	void readBook(const Book& book);
	void readBookPage(const Book& book, size_t pageCount) const;
	void readBookComments(const Book& book) const;
	void writeBook(const Book& book);
	void writeBookComment(Book& book, const char* comment);
	void editWrittenBook(Book& book);
	void rateBook(Book& book, size_t rating);
	void editBookRating(Book& book, size_t newRating);

	const char* getName() const;
	const char* getPassword() const;

};