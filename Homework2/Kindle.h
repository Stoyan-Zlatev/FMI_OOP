#pragma once
#include "UsersCollection.h"
#include "BooksCollection.h"

class Kindle
{
	UsersCollection users;
	User currentUser;
	bool isUsed;
	BooksCollection booksToRead;
	bool containsUser(const char* username);
	bool conatinsBook(const char* bookTitle);
public:
	void login(const char* userName, const char* password);
	void signup(const char* userName, const char* password);
	void logout();
};