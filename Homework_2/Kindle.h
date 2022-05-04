#pragma once
#include "User.h"
#include "Book.h"
#include "Collection.hpp"

class Kindle
{
	Collection<User> users;
	User currentUser;
	bool isUsed;
	Collection<Book> booksToRead;
	bool containsUser(const MyString& username, const MyString& password) const;
	bool containsUser(const MyString& username) const;
	bool conatinsBook(const MyString& bookTitle) const;
	void saveToFile(std::fstream& file);
public:
	Kindle();
	void load(std::fstream& sourceFile);
	void login(const MyString& userName, const MyString& password);
	void signup(const MyString& userName, const MyString& password);
	void logout(std::fstream& file);
	void view() const;
	void printFirstUser() const;
	const MyString getCurrentUserName() const;

	Book& getBookByName(const MyString& name) const;
};