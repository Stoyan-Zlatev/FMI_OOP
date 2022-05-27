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
	Account::saveToFile(file);
}

void NormalAccount::readFromFile(std::ifstream& file)
{
	accountType = AccountType::Normal;
	Account::readFromFile(file);
}

NormalAccount::NormalAccount() : NormalAccount("", "", "", -1, 0, std::time(0)) {}

NormalAccount::NormalAccount(const MyString& username, const MyString& password, const MyString& iban,
	size_t id, double amount, time_t dateOfCreation) : Account(username, password, iban, id, amount, dateOfCreation)
{
	setAccountType();
}

bool NormalAccount::withdraw(double amount)
{
	if (amount > this->amount)
	{
		throw std::invalid_argument("There are not enough money in your account!");
	}

	this->amount -= amount;
	return true;
}
