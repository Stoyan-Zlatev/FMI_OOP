#pragma once
#include "User.h"

class UsersCollection
{
	size_t usersCount;
	size_t allocatedCellsCount;
	User* usersCollection;
	void copyFrom(const UsersCollection& other);
	void free();
	void resize();
public:
	UsersCollection();

	size_t getUsersCount() const;
	
	void addUser(const char* userName, const char* userPassword);
	void addUser(const User& user);
};