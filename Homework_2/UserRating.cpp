#include "UserRating.h"
#include "MyString.h"

UserRating::UserRating() : UserRating("", 0) {}

UserRating::UserRating(const MyString& username, size_t rating)
{
	this->username = username;
	setRating(rating);
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
