#pragma once
#include "MyString.h"
#include <ctime>

class Account
{
protected:
	MyString username;
	MyString password;
	MyString iban;
	size_t id;
	double amount;
	time_t dateOfCreation;
public:
	Account();
	Account(const MyString& username, const MyString& password, const MyString& iban, size_t id, double amount = 0, time_t dateOfCreation = std::time(0));
	virtual void deposit(double amount);
	virtual bool withdraw(double amount) = 0;
	virtual void display() const;
	virtual double getBalance() const;
	virtual void printAccountType() const = 0;
	virtual Account* clone()  const = 0;

	void setIban(const MyString& iban);
	void setUsername(const MyString& username);
	void setId(size_t id);
	void setAmount(double amount);
	void setDateOfCreation(const time_t& date);
	void setPassword(const MyString& password);

	MyString getIban() const;
	MyString getUsername() const;
	size_t getId() const;
	double getAmount() const;
	time_t getDateOfCreation() const;

	void saveToFile(std::ofstream& file);
	void readFromFile(std::ifstream& file);

	virtual ~Account();
};