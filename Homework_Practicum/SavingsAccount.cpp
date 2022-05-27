#include "SavingsAccount.h"
#include "GlobalConstants.h"
#include "Serialize.h"
#include <iostream>

bool SavingsAccount::withdraw(double amount)
{
	throw std::invalid_argument("You are not allowed to withdraw from savings account!");
}

SavingsAccount::SavingsAccount() : SavingsAccount("", "", "", -1, 0, 0, std::time(0)) {}

SavingsAccount::SavingsAccount(const MyString& username, const MyString& password, const MyString& iban,
	size_t id, double interestRate, double amount, time_t dateOfCreation) : Account(username, password, iban, id, amount, dateOfCreation)
{
	this->interestRate = interestRate;
}

void SavingsAccount::setAccountType()
{
	accountType = AccountType::Savings;
}

MyString SavingsAccount::getAccountType() const
{
	return SavingsAccountType;
}

Account* SavingsAccount::clone() const
{
	return new SavingsAccount(*this);
}

void SavingsAccount::saveToFile(std::ofstream& file)
{
	file.write((const char*)&accountType, sizeof(accountType));
	writeString(file, username);
	writeString(file, password);
	file.write((const char*)&id, sizeof(id));
	file.write((const char*)&amount, sizeof(amount));
	file.write((const char*)&dateOfCreation, sizeof(dateOfCreation));
	file.write((const char*)&interestRate, sizeof(interestRate));
}

void SavingsAccount::readFromFile(std::ifstream& file)
{
	file.read((char*)&accountType, sizeof(accountType));
	readString(file, username);
	readString(file, password);
	file.read((char*)&id, sizeof(id));
	file.read((char*)&amount, sizeof(amount));
	file.read((char*)&dateOfCreation, sizeof(dateOfCreation));
	file.read((char*)&interestRate, sizeof(interestRate));
}