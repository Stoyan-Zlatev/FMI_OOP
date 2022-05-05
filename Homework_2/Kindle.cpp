#include "Kindle.h"
#include "User.h"
#include <exception>
#include <iostream>

Kindle::Kindle()
{
	booksToRead.add(Book("Kniga", "Avtor 1"));
	booksToRead.add(Book("Knigata", "Avtor 2"));
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
	size_t booksCount, usersCount;
	sourceFile >> booksCount >> usersCount;
	sourceFile.read((char*)&booksToRead, booksCount * sizeof(Collection<Book>));
	sourceFile.read((char*)&users, usersCount * sizeof(Collection<User>));
}

void Kindle::saveToFile(std::fstream& file)
{
	file << booksToRead.count << users.count;
	file.write((const char*)&booksToRead, booksToRead.count * sizeof(Collection<Book>));
	file.write((const char*)&users, users.count * sizeof(Collection<User>));
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
		std::cout << i + 1 << ". " << currentBook.getTitle() << " by " << currentBook.getAuthorName() << std::endl;
	}
}

void Kindle::rateBookByName(const MyString& bookTitle, const MyString& username, int rating)
{
	if (!(isUsed && currentUser.hasUserRead(bookTitle)))
	{
		throw std::invalid_argument("You do not have access!");
	}

	size_t bookIndex = getBookIndexByName(bookTitle);
	booksToRead.collection[bookIndex].rate(username, rating);
}

void Kindle::addBook(const Book& book)
{
	booksToRead.add(book);
	currentUser.writeBook(book);
}

void Kindle::printBookComments(const MyString& bookTitle) const
{
	size_t bookIndex = getBookIndexByName(bookTitle);
	booksToRead.collection[bookIndex].printComments();
}

void Kindle::addBookComment(const MyString& bookTitle, const MyString& comment)
{
	if (!currentUser.hasUserRead(bookTitle))
	{
		throw std::invalid_argument("You can comment only books you have read!");
	}

	size_t bookIndex = getBookIndexByName(bookTitle);
	booksToRead.collection[bookIndex].addComment(currentUser.getName(), comment);
}

void Kindle::printBookPage(const MyString& bookTitle, size_t pageNumber) const
{
	size_t bookIndex = getBookIndexByName(bookTitle);
	booksToRead.collection[bookIndex].printPageByIndex(pageNumber);
}

void Kindle::printBookRating(const MyString& bookTitle) const
{
	size_t bookIndex = getBookIndexByName(bookTitle);
	booksToRead.collection[bookIndex].printRatings();
}

void Kindle::addBookPage(const MyString& bookTitle, const MyString& pageContent)
{
	if (!currentUser.isUsersBook(bookTitle))
	{
		throw std::invalid_argument("You can edit only your books!");
	}

	size_t bookIndex = getBookIndexByName(bookTitle);
	booksToRead.collection[bookIndex].addPage(pageContent, booksToRead.collection[bookIndex].getPagesCount());
}

void Kindle::removeBookLastPage(const MyString& bookTitle)
{
	if (!currentUser.isUsersBook(bookTitle))
	{
		throw std::invalid_argument("You can edit only your books!");
	}

	size_t bookIndex = getBookIndexByName(bookTitle);
	booksToRead.collection[bookIndex].removeLastPage();
}

void Kindle::readBook(const MyString& bookTitle)
{
	size_t bookIndex = getBookIndexByName(bookTitle);
	currentUser.readBook(booksToRead.collection[bookIndex]);
}

size_t Kindle::getBookIndexByName(const MyString& name) const
{
	for (size_t i = 0; i < booksToRead.count; i++)
	{
		if (name == booksToRead.collection[i].getTitle())
		{
			return i;
		}
	}

	throw std::invalid_argument("Book with this name does not exist!");
}

