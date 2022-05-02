#pragma once
#include "User.h"
#include <cstring>
#pragma warning(disable:4996)

User::User() : User("", "") {}

User::User(const char* name, const char* password)
{
	setName(name);
	setPassword(password);
}

void User::setName(const char* name)
{
	if (strlen(name) > MaxNameLength)
	{
		return;
	}

	strcpy(this->name, name);
}

void User::setPassword(const char* password)
{
	if (strlen(password) > MaxNameLength)
	{
		return;
	}

	strcpy(this->password, password);
}

void User::readBook(const Book& book)
{
	readBooks.addBook(book);
}

void User::writeBook(const Book& book)
{
	writenBooks.addBook(book);
}


void User::readBookPage(const Book& book, size_t pageCount) const
{
	//
}

void User::readBookComments(const Book& book) const
{
	book.printComments();
}

void User::writeBookComment(Book& book, const char* comment)
{
	book.addComment(name, comment);
}

void User::editWrittenBook(Book& book)
{
	//todo
}

void User::rateBook(Book& book, size_t rating)
{
	book.setRating(rating);
}

void User::editBookRating(Book& book, size_t newRating)
{
	rateBook(book, newRating);
}

const char* User::getName() const
{
	return name;
}

const char* User::getPassword() const 
{
	return password;
}