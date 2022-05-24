#include "PrivilegeAccount.h"
#include <iostream>

PriviligeAccount::PriviligeAccount() : PriviligeAccount("", "", "", -1, 0, 0, std::time(0)) {}

PriviligeAccount::PriviligeAccount(const MyString& username, const MyString& password, const MyString& iban,
	size_t id, double overdraft, double amount, time_t dateOfCreation) : Account(username, password, iban, id, amount, dateOfCreation)
{
	this->overdraft = overdraft;
}

bool PriviligeAccount::withdraw(double amount)
{
	if (amount > (this->amount + overdraft))
		return false;

	this->amount -= amount;
	return true;
}

void PriviligeAccount::printAccountType() const
{
	std::cout << "Account type: " << "Privilige account" << std::endl;
}

Account* PriviligeAccount::clone() const
{
	Account* newAcc = new PriviligeAccount(*this);
	return newAcc;
}
