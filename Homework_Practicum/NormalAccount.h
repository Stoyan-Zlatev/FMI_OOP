#pragma once
#include "Account.h"

class NormalAccount : public Account
{
public:
	NormalAccount();
	NormalAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id, double amount = 0, time_t dateOfCreation = std::time(0));
	bool withdraw(double amount) override;
	void printAccountType() const override;
	virtual Account* clone()  const override;
};