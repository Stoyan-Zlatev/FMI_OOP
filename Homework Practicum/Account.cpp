#include "Account.h"
#include "GlobalConstants.h"
#include "Serialize.h"
#include <iostream>
#include <ctime>
#pragma warning(disable : 4996)

Account::Account() : Account("", "", "", -1, 0, std::time(0)) {}

Account::Account(const MyString& username, const MyString& password, const MyString& iban, size_t customerId, double amount, time_t dateOfCreation)
{
	setUsername(username);
	setPassword(password);
	setIban(iban);
	setId(customerId);
	setAmount(amount);
	setDateOfCreation(dateOfCreation);
}

void Account::deposit(double amount)
{
	this->amount += amount;
}

void Account::display() const {
	std::cout << "Account type: " << getAccountType() << std::endl;
	std::cout << "Iban: " << iban << std::endl;
	std::cout << "Holder: " << username << std::endl;
	std::cout << "Holder id: " << customerId << std::endl;
	std::cout << "Balance: " << amount << "$" << std::endl;
	std::cout << "Date of creation: " << std::ctime(&dateOfCreation);
}
double Account::getBalance() const
{
	return amount;
}


void Account::setIban(const MyString& iban)
{
	if (iban.getSize() > MaxContentLength)
	{
		throw std::invalid_argument("Entered iban is too long!");
	}

	this->iban = iban;
}

void Account::setUsername(const MyString& username)
{
	if (username.getSize() > MaxContentLength)
	{
		throw std::invalid_argument("Entered username is too long!");
	}

	this->username = username;
}

void Account::setId(size_t customerId)
{
	if (customerId < 0)
	{
		throw std::invalid_argument("Entered id is invalid!");
	}

	this->customerId = customerId;
}

void Account::setAmount(double amount)
{
	if (amount < 0)
	{
		throw std::invalid_argument("Entered amount is invalid!");
	}

	this->amount = amount;
}

void Account::setDateOfCreation(const time_t& date)
{
	dateOfCreation = date;
}

void Account::setPassword(const MyString& password)
{
	if (password.getSize() > MaxContentLength)
	{
		throw std::invalid_argument("Entered password is too long!");
	}

	this->password = password;
}

MyString Account::getIban() const
{
	return iban;
}

MyString Account::getUsername() const
{
	return username;
}

MyString Account::getPassword() const
{
	return password;
}

size_t Account::getCustomerId() const
{
	return customerId;
}

double Account::getAmount() const
{
	return amount;
}

time_t Account::getDateOfCreation() const
{
	return dateOfCreation;
}

void Account::saveToFile(std::ofstream& file)
{
	file.write((const char*)&accountType, sizeof(accountType));
	writeString(file, username);
	writeString(file, password);
	writeString(file, iban);
	file.write((const char*)&customerId, sizeof(customerId));
	file.write((const char*)&amount, sizeof(amount));
	file.write((const char*)&dateOfCreation, sizeof(dateOfCreation));
}

void Account::readFromFile(std::ifstream& file)
{
	readString(file, username);
	readString(file, password);
	readString(file, iban);
	file.read((char*)&customerId, sizeof(customerId));
	file.read((char*)&amount, sizeof(amount));
	file.read((char*)&dateOfCreation, sizeof(dateOfCreation));
}

Account::~Account() {}
