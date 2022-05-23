#pragma once
#include "MyString.h"
#include "Collection.hpp"
#include "Customer.h"
#include "Account.h"
#include "Transaction.h"

class Bank
{
	MyString name;
	MyString address;
	Collection<Customer> customers;
	Collection<Account> accounts;
	Collection<Transaction> log;
public:
	void addCustomer();
	void deleteCustomer();
	void addAccount();
	void deleteAccount();
	void listCustomers() const;
	void listAccounts() const;
	void listCustomerAccount();
	void exportLog();
	void transfer();
	void display() const;
};