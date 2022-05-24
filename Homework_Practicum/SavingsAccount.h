#pragma once
#include "Account.h"

class SavingsAccount : public Account
{
	double interestRate;
public:
	SavingsAccount();
	SavingsAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
				   double interestRate = 0, double amount = 0, time_t dateOfCreation = std::time(0));
	bool withdraw(double amount) override;
	void printAccountType() const override;
	virtual Account* clone()  const override;
};