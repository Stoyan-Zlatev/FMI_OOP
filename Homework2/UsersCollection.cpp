#pragma once
#include "UsersCollection.h"

void UsersCollection::copyFrom(const UsersCollection& other)
{
	usersCollection = new  User[other.getUsersCount()];
	for (size_t i = 0; i < other.getUsersCount(); i++)
		usersCollection[i] = other.usersCollection[i];
	usersCount = other.getUsersCount();
}

void UsersCollection::free()
{
	usersCount = 0;
	delete[] usersCollection;
}

void UsersCollection::resize()
{
	allocatedCellsCount *= 2;
	User* newData = new User[allocatedCellsCount];

	for (int i = 0; i < usersCount; i++) {
		newData[i] = usersCollection[i];
	}

	delete[] usersCollection;
	usersCollection = newData;
}

UsersCollection::UsersCollection()
{
	usersCount = 0;
	allocatedCellsCount = DEFAULT_ALLOCATED_CELLS;
}


size_t UsersCollection::getUsersCount() const
{
	return this->usersCount;
}

void UsersCollection::addUser(const char* userName, const char* userPassword) 
{
	addUser(User(userName, userPassword));
}

void UsersCollection::addUser(const User& user)
{
	if (usersCount >= allocatedCellsCount)
	{
		resize();
	}

	usersCollection[usersCount] = user;
	usersCount++;
}
