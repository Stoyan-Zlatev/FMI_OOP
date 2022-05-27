#include "PrivilegeAccount.h"
#include "GlobalConstants.h"
#include "Serialize.h"
#include <iostream>

PrivilegeAccount::PrivilegeAccount() : PrivilegeAccount("", "", "", -1, 0, 0, std::time(0)) {}

PrivilegeAccount::PrivilegeAccount(const MyString& username, const MyString& password, const MyString& iban,
	size_t id, double overdraft, double amount, time_t dateOfCreation) : Account(username, password, iban, id, amount, dateOfCreation)
{
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
	file.write((const char*)&accountType, sizeof(accountType));
	writeString(file, username);
	writeString(file, password);
	file.write((const char*)&id, sizeof(id));
	file.write((const char*)&amount, sizeof(amount));
	file.write((const char*)&dateOfCreation, sizeof(dateOfCreation));
	file.write((const char*)&overdraft, sizeof(overdraft));
}

void PrivilegeAccount::readFromFile(std::ifstream& file)
{
	file.read((char*)&accountType, sizeof(accountType));
	readString(file, username);
	readString(file, password);
	file.read((char*)&id, sizeof(id));
	file.read((char*)&amount, sizeof(amount));
	file.read((char*)&dateOfCreation, sizeof(dateOfCreation));
	file.read((char*)&overdraft, sizeof(overdraft));
}
