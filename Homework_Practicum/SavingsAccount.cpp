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
	size_t customerId, double interestRate, double amount, time_t dateOfCreation) : Account(username, password, iban, customerId, amount, dateOfCreation)
{
	setAccountType();
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
	Account::saveToFile(file);
	file.write((const char*)&interestRate, sizeof(interestRate));
}

void SavingsAccount::readFromFile(std::ifstream& file)
{
	accountType = AccountType::Savings;
	Account::readFromFile(file);
	file.read((char*)&interestRate, sizeof(interestRate));
}