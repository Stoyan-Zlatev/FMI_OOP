#include "User.h"
#include <cstring>
#pragma warning(disable:4996)

User::User() : User("", "") {}

User::User(const MyString& name, const MyString& password)
{
	setName(name);
	setPassword(password);
}

void User::setName(const MyString& name)
{
	if (name.getSize() > MaxNameLength)
	{
		return;
	}

	this->name = name;
}

void User::setPassword(const MyString& password)
{
	if (password.getSize() > MaxNameLength)
	{
		return;
	}

	this->password = password;
}

void User::readBook(const Book& book)
{
	readBooks.add(book);
}

void User::writeBook(const Book& book)
{
	writtenBooks.add(book);
}


void User::readBookPage(const Book& book, size_t pageCount) const
{
	book.printPageByIndex(pageCount);
}

void User::readBookComments(const Book& book) const
{
	book.printComments();
}

void User::writeBookComment(Book& book, const MyString comment)
{
	book.addComment(name, comment);
}

void User::editWrittenBook(Book& book)
{
	if (isUsersBook(book.getTitle()))
	{
		writeBook(book);
	}
}

void User::rateBook(Book& book, size_t rating)
{
	book.rate(name, rating);
}

void User::editBookRating(Book& book, size_t newRating)
{
	rateBook(book, newRating);
}

const MyString User::getName() const
{
	return name;
}

const MyString User::getPassword() const
{
	return password;
}

bool User::isUsersBook(const MyString& bookTitle) const
{
	for (size_t i = 0; i < writtenBooks.getCount(); i++)
	{
		if (writtenBooks.getElementByIndex(i).getTitle() == bookTitle)
		{
			return true;
		}
	}

	return false;
}

bool User::hasUserRead(const MyString& bookTitle) const
{
	for (size_t i = 0; i < readBooks.getCount(); i++)
	{
		if (readBooks.getElementByIndex(i).getTitle() == bookTitle)
		{
			return true;
		}
	}

	return false;
}
