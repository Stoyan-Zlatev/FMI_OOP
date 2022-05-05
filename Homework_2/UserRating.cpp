#include "UserRating.h"
#include "MyString.h"

UserRating::UserRating() : UserRating("", 0) {}

UserRating::UserRating(const MyString& username, size_t rating)
{
	this->username = username;
	setRating(rating);
}

void UserRating::saveToFile(std::fstream& file)
{
	/*	MyString username;
	size_t rating;*/
	size_t usernameSize = username.getSize();
	file.write((const char*)&usernameSize, sizeof(size_t));
	file.write((const char*)username.c_str(), sizeof(size_t));

	file.write((const char*)&rating, sizeof(size_t));
}

void UserRating::setRating(size_t rating)
{
	if (rating < 0 || rating>5)
	{
		throw std::invalid_argument("Rating should be between 0 and 5!");
	}

	this->rating = rating;
}

size_t UserRating::getRating() const
{
	return rating;
}

const MyString UserRating::getUserName() const
{
	return username;
}
