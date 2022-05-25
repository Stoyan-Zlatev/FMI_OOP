#include "NormalAccount.h"
#include <iostream>

void NormalAccount::printAccountType() const
{
	std::cout << "Account type: " << "Normal account" << std::endl;
}

Account* NormalAccount::clone() const
{
	return new NormalAccount(*this);
}

NormalAccount::NormalAccount() : NormalAccount("", "", "", -1, 0, std::time(0)) {}

NormalAccount::NormalAccount(const MyString& username, const MyString& password, const MyString& iban,
	size_t id, double amount, time_t dateOfCreation) : Account(username, password, iban, id, amount, dateOfCreation){}

bool NormalAccount::withdraw(double amount)
{
	if (amount > this->amount)
		return false;

	this->amount -= amount;
	return true;
}
