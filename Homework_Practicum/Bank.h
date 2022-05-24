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
	Collection<Customer> customers;
	AccountStore accounts;
	Collection<Transaction> log;
	bool containsUser(const MyString& customerName) const;
	int getCustomerId(const MyString& iban) const;
public:
	void addCustomer();
	void deleteCustomer();
	void addAccount();
	void deleteAccount();
	void listAllCustomers() const;
	void listAccounts() const;
	void listCustomerAccount();
	void exportLog();
	void transfer(const MyString& senderIban, const MyString& receiverIban, double amount);
	void display() const;

	void load(std::fstream& sourceFile);
	void saveToFile(std::fstream& sourceFile);
};