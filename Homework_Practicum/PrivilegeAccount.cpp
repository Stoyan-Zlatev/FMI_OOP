#include "PrivilegeAccount.h"
#include "GlobalConstants.h"
#include "Serialize.h"
#include <iostream>

PrivilegeAccount::PrivilegeAccount() : PrivilegeAccount("", "", "", -1, 0, 0, std::time(0)) {}

PrivilegeAccount::PrivilegeAccount(const MyString& username, const MyString& password, const MyString& iban,
	size_t customerId, double overdraft, double amount, time_t dateOfCreation) : Account(username, password, iban, customerId, amount, dateOfCreation)
{
	setAccountType();
	this->overdraft = overdraft;
}

void PrivilegeAccount::setAccountType()
{
	accountType = AccountType::Privilige;
}

MyString PrivilegeAccount::getAccountType() const
{
	return PrivilegeAccountType;
}

bool PrivilegeAccount::withdraw(double amount)
{
	if (amount > (this->amount + overdraft))
	{
		throw std::invalid_argument("There are not enough money in your account!");
	}

	this->amount -= amount;
	return true;
}

Account* PrivilegeAccount::clone() const
{
	return new PrivilegeAccount(*this);
}

void PrivilegeAccount::saveToFile(std::ofstream& file)
{
	Account::saveToFile(file);
	file.write((const char*)&overdraft, sizeof(overdraft));
}

void PrivilegeAccount::readFromFile(std::ifstream& file)
{
	accountType = AccountType::Privilige;
	Account::readFromFile(file);
	file.read((char*)&overdraft, sizeof(overdraft));
}
