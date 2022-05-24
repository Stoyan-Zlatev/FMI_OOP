#pragma once
#include "MyString.h"
#include <ctime>

class Account
{
	MyString username;
	MyString password;
	MyString iban;
	MyString id;
	double amount;
	time_t dateOfCreation;
public:
	void deposit();
	void withdraw();
	void display() const;
	double getBalance() const;
};