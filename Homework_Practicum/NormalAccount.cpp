#include "NormalAccount.h"
#include "Serialize.h"
#include "GlobalConstants.h"
#include <iostream>

Account* NormalAccount::clone() const
{
	return new NormalAccount(*this);
}

void NormalAccount::setAccountType()
{
	accountType = AccountType::Normal;
}

MyString NormalAccount::getAccountType() const
{
	return NormalAccountType;
}

void NormalAccount::saveToFile(std::ofstream& file)
{
	file.write((const char*)&accountType, sizeof(accountType));
	writeString(file, username);
	writeString(file, password);
	file.write((const char*)&id, sizeof(id));
	file.write((const char*)&amount, sizeof(amount));
	file.write((const char*)&dateOfCreation, sizeof(dateOfCreation));
}

void NormalAccount::readFromFile(std::ifstream& file)
{
	file.read((char*)&accountType, sizeof(accountType));
	readString(file, username);
	readString(file, password);
	file.read((char*)&id, sizeof(id));
	file.read((char*)&amount, sizeof(amount));
	file.read((char*)&dateOfCreation, sizeof(dateOfCreation));
}

NormalAccount::NormalAccount() : NormalAccount("", "", "", -1, 0, std::time(0)) {}

NormalAccount::NormalAccount(const MyString& username, const MyString& password, const MyString& iban,
	size_t id, double amount, time_t dateOfCreation) : Account(username, password, iban, id, amount, dateOfCreation){}

bool NormalAccount::withdraw(double amount)
{
	if (amount > this->amount)
	{
		throw std::invalid_argument("There are not enough money in your account!");
	}

	this->amount -= amount;
	return true;
}
