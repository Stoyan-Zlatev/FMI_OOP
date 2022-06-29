#pragma once
#include "MyString.h"
#include "Collection.hpp"
#include "Customer.h"
#include "Account.h"
#include "AccountStore.h"

class Bank
{
	MyString name;
	MyString address;
	AccountStore accounts;
	Collection<Customer> customers;
	Collection<MyString> log;
	int getUserIndex(size_t customerId) const;
	int getAccountIndex(const MyString& iban) const;
public:
	Bank();
	Bank(const MyString& bankName, const MyString& bankAddress);

	void addCustomer(const MyString& customerName, const MyString& customerAddress);
	void deleteCustomer(size_t customerId);
	void addAccount(const MyString& iban, const MyString& customerName, const MyString& password, size_t customerId, size_t accountType);
	void deleteAccount(const MyString& iban);
	void listAllCustomers() const;
	void listAllAccounts() const;
	void listCustomerAccounts(size_t customerId) const;;
	void listLog() const;
	void exportLog();
	void importLog();
	void transfer(const MyString& senderIban, const MyString& receiverIban, double amount);
	void display() const;
	void deposit(const MyString& iban, double amount);
	void withdraw(const MyString& iban, double amount);

	void setBankName(const MyString& bankName);
	void setBankAdress(const MyString& bankAddress);

	MyString getBankName() const;
	MyString getBankAdress() const;

	void load(std::ifstream& sourceFile);
	void saveToFile(std::ofstream& sourceFile);
};