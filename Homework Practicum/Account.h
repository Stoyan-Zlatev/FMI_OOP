#pragma once
#include "MyString.h"
#include "AccountType.h"
#include <ctime>

class Account
{
protected:
	MyString username;
	MyString password;
	MyString iban;
	AccountType accountType;
	size_t customerId;
	double amount;
	time_t dateOfCreation;
	
	void setId(size_t customerId);
	void setIban(const MyString& iban);
	void setDateOfCreation(const time_t& date);
	virtual void setAccountType() = 0;
public:
	Account();
	Account(const MyString& username, const MyString& password, const MyString& iban, size_t customerId, double amount = 0, time_t dateOfCreation = std::time(0));
	virtual void deposit(double amount);
	virtual bool withdraw(double amount) = 0;
	virtual void display() const;
	virtual double getBalance() const;
	virtual Account* clone()  const = 0;

	void setUsername(const MyString& username);
	void setAmount(double amount);
	void setPassword(const MyString& password);

	virtual MyString getAccountType() const = 0;
	MyString getIban() const;
	MyString getUsername() const;
	MyString getPassword() const;
	size_t getCustomerId() const;
	double getAmount() const;
	time_t getDateOfCreation() const;

	virtual void saveToFile(std::ofstream& file);
	virtual void readFromFile(std::ifstream& file);

	friend class Bank;

	virtual ~Account();
};