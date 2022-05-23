#pragma once
#include "MyString.h"

class Bank
{
	MyString name;
	MyString address;
	/* customers – списък от потребители. (изберете подходящ начин за представяне)
 accounts – списък от банкови сметки. (изберете подходящ начин за представяне)
 log – списък от всички извършени транзакции на банката(под транзакция
разбираме създаване на потребител, създаване на сметка, изтриване на
потребител, изтриване на сметка, deposit , withdraw etc)*/
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