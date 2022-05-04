#include "Kindle.h"
#include "User.h"
#include <exception>
#include <iostream>

Kindle::Kindle()
{
	booksToRead.add(Book("Kniga 1", "Avtor 1"));
	booksToRead.add(Book("Kniga 2", "Avtor 2"));
	currentUser = User("", "");
	isUsed = false;
}

bool Kindle::containsUser(const MyString& username) const
{
	for (size_t i = 0; i < users.getCount(); i++)
	{
		if (username == users.getElementByIndex(i).getName())
		{
			return true;
		}
	}

	return false;
}

bool Kindle::containsUser(const MyString& username, const MyString& password) const
{
	for (size_t i = 0; i < users.getCount(); i++)
	{
		if (username == users.getElementByIndex(i).getName() && password == users.getElementByIndex(i).getPassword())
		{
			return true;
		}
	}

	return false;
}

bool Kindle::conatinsBook(const MyString& bookTitle) const
{
	return false;
}

void Kindle::login(const MyString& username, const MyString& password)
{
	if (isUsed)
	{
		throw std::invalid_argument("There is already logged user!");
	}

	if (!containsUser(username, password))
	{
		throw std::invalid_argument("User with this username and password does not exist!");
	}

	User currentUser = User(username, password);
	users.add(currentUser);
	this->currentUser = currentUser;
	isUsed = true;
}

void Kindle::signup(const MyString& username, const MyString& password)
{
	if (containsUser(username))
	{
		throw std::invalid_argument("User with this username already exists!");
	}

	User currentUser = User(username, password);
	users.add(currentUser);
	this->currentUser = currentUser;
	isUsed = true;
}

void Kindle::logout(std::fstream& file)
{
	saveToFile(file);
	isUsed = false;
}

size_t getFileSize(std::fstream& file)
{
	size_t currentPosition = file.tellg();

	file.seekg(0, std::ios::end);
	size_t result = file.tellg();
	file.seekg(currentPosition);
	return result;
}

void Kindle::load(std::fstream& sourceFile)
{
	size_t sizeOfFile = getFileSize(sourceFile);
	sourceFile.read((char*)this, sizeOfFile);
}

void Kindle::saveToFile(std::fstream& file)
{
	//not working
	size_t totalFileSize = users.getCount() * sizeof(Collection<User>);
	totalFileSize += booksToRead.getCount() * sizeof(Collection<Book>) + sizeof(User) + sizeof(bool);
	file.write((const char*)this, sizeof(totalFileSize));
}

void Kindle::printFirstUser() const
{
	std::cout << users.getElementByIndex(0).getName() << std::endl;
	std::cout << users.getElementByIndex(0).getPassword() << std::endl;
}

const MyString Kindle::getCurrentUserName() const
{
	return currentUser.getName();
}

void Kindle::view() const
{
	if (!isUsed)
	{
		throw std::invalid_argument("You do not have access!");
	}
	for (size_t i = 0; i < booksToRead.getCount(); i++)
	{
		Book currentBook = booksToRead.getElementByIndex(i);
		std::cout << i + 1 << ". " << currentBook.getTitle() << "by " << currentBook.getAuthorName() << std::endl;
	}
}

Book& Kindle::getBookByName(const MyString& name) const
{
	for (size_t i = 0; i < booksToRead.getCount(); i++)
	{
		if (booksToRead.getElementByIndex(i).getTitle() == name)
		{
			return booksToRead.getElementByIndex(i);
		}
	}
	throw std::invalid_argument("Book with this name does not exist!");
}


