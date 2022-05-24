#include "SavingsAccount.h"
#include <iostream>

bool SavingsAccount::withdraw(double amount)
{
	return false;
}

SavingsAccount::SavingsAccount() : SavingsAccount("", "", "", -1, 0, 0, std::time(0)) {}

SavingsAccount::SavingsAccount(const MyString& username, const MyString& password, const MyString& iban,
	size_t id, double interestRate, double amount, time_t dateOfCreation) : Account(username, password, iban, id, amount, dateOfCreation)
{
	this->interestRate = interestRate;
}

void SavingsAccount::printAccountType() const
{
	std::cout << "Account type: " << "Privilige account" << std::endl;
}

Account* SavingsAccount::clone() const
{
	Account* newAcc = new SavingsAccount(*this);
	return newAcc;
}
