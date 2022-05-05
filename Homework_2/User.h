#pragma once
#include "Book.h"
#include "Collection.hpp"
#include "GlobalConstants.h"
#include "MyString.h"

class User
{
	MyString name;
	MyString password;
	Collection<Book> readBooks;
	Collection<Book> writtenBooks;
	bool isUsersBook(const Book& book) const;
	void setName(const MyString& name);
	void setPassword(const MyString& password);
public:
	User();
	User(const MyString& name, const MyString& password);

	void readBook(const Book& book);
	void readBookPage(const Book& book, size_t pageCount) const;
	void readBookComments(const Book& book) const;
	void writeBook(const Book& book);
	void writeBookComment(Book& book, const MyString comment);
	void editWrittenBook(Book& book);
	void rateBook(Book& book, size_t rating);
	void editBookRating(Book& book, size_t newRating);

	const MyString getName() const;
	const MyString getPassword() const;
};