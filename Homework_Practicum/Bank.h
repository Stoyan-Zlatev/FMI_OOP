#pragma once
#include "MyString.h"
#include "Collection.hpp"
#include "Customer.h"
#include "Account.h"
#include "Transaction.h"
#include "AccountStore.h"

class Bank
{
	MyString name;
	MyString address;
	AccountStore accounts;
	Collection<Customer> customers;
	Collection<MyString> log;
	int getUserIndex(const MyString& customerName) const;
	int getAccountIndex(const MyString& iban) const;
public:
	void addCustomer(const MyString& username, const MyString& address);
	void deleteCustomer(const MyString& username);
	void addAccount(const MyString& iban, const MyString& username, const MyString& password, size_t accountType, double additional = 0);
	void deleteAccount(const MyString& iban);
	void listAllCustomers() const;
	void listAllAccounts() const;
	void listCustomerAccounts(const MyString& username) const;;
	void listLog() const;
	void exportLog();
	void transfer(const MyString& senderIban, const MyString& receiverIban, double amount);
	void display() const;
	void deposit(const MyString& iban, double amount);
	void withdraw(const MyString& iban, double amount);

	void load(std::ifstream& sourceFile);
	void saveToFile(std::ofstream& sourceFile);
};