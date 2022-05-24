#pragma once
#include "Account.h"
#include "NormalAccount.h"
#include "PrivilegeAccount.h"
#include "SavingsAccount.h"
#include "GlobalConstants.h"
#include <iostream>

class AccountStore
{
private:
	Account** data;
	size_t capacity;
	size_t count;

	void copyFrom(const AccountStore& other);
	void free();
	void resize();

public:
	AccountStore();
	AccountStore(const AccountStore& other);
	AccountStore& operator=(const AccountStore& other);
	~AccountStore();

	void addNormalAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
		double amount = 0, time_t dateOfCreation = std::time(0));
	void addPrivilegeAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
		double overdraft = 0, double amount = 0, time_t dateOfCreation = std::time(0));
	void addSavingsAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
		double interestRate = 0, double amount = 0, time_t dateOfCreation = std::time(0));

	void printAllAccounts() const;
	friend class Bank;
};