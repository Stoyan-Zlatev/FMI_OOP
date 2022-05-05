#include "Book.h"
#include <iostream>
#pragma warning(disable:4996)

Book::Book() : Book("", "") {}

Book::Book(const MyString& title, const MyString& authorName)
{
	setTitle(title);
	setAuthorName(authorName);
}

void Book::setTitle(const MyString& title)
{
	//if (title == "")
	//{
	//	throw std::invalid_argument("Title should not be empty!");
	//}

	this->title = title;
}
void Book::setAuthorName(const MyString& authorName)
{
	/*if (authorName == "")
	{
		throw std::invalid_argument("Author name should not be empty!");
	}*/

	this->authorName = authorName;
}

void Book::rate(const MyString& username, int rating)
{
	ratings.add(UserRating(username, rating));
}

const MyString Book::getTitle() const
{
	return title;
}
const MyString Book::getAuthorName() const
{
	return authorName;
}

double Book::sumRating() const
{
	double sum = 0;
	for (size_t i = 0; i < ratings.getCount(); i++)
	{
		sum += ratings.getElementByIndex(i).getRating();
	}

	return sum;
}


double Book::getRating() const
{
	double ratingsSum = sumRating();
	return ratingsSum / (double)ratings.getCount();
}

void Book::printComments() const
{
	for (size_t i = 0; i < comments.getCount(); i++)
	{
		std::cout << comments.getElementByIndex(i).getContent() << std::endl;
	}
}

void Book::printRatings() const
{
	for (size_t i = 0; i < ratings.getCount(); i++)
	{
		std::cout << ratings.collection[i].getUserName() << " rated " << ratings.collection[i].getRating() << " start!" << std::endl;
	}
}

size_t Book::getPagesCount() const
{
	return pages.count;
}

void Book::addComment(const MyString& username, const MyString& comment)
{
	comments.add(Comment(username, comment));
}

void Book::addPage(const MyString& content, size_t pageNumber)
{
	pages.add(Page(content, pageNumber));
}

void Book::removeLastPage()
{
	pages.remove();
}

void Book::printPageByIndex(int index) const
{
	if (index < 0)
	{
		throw std::invalid_argument("This is the first page of the book!");

	}
	else if (index > (pages.getCount() - 1))
	{
		throw std::invalid_argument("This is the last page of the book!");
	}
	std::cout << pages.getElementByIndex(index).getPageContent();
}

