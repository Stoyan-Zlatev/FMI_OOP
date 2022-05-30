#pragma once
#include "Account.h"

class SavingsAccount : public Account
{
	double interestRate;
public:
	SavingsAccount();
	SavingsAccount(const MyString& username, const MyString& password, const MyString& iban, size_t customerId,
				   double interestRate = 0, double amount = 0, time_t dateOfCreation = std::time(0));
	bool withdraw(double amount) override;
	virtual Account* clone()  const override;

	void setAccountType() override;
	MyString getAccountType() const override;

	void saveToFile(std::ofstream& file) override;
	void readFromFile(std::ifstream& file) override;
};