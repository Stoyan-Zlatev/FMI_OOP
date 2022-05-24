#include "Utils.h"
#include "GlobalConstants.h"
#include <iostream>

bool isPrefix(const MyString& text, const MyString& prefix)
{
	int i = 0;
	for (size_t i = 0; i < prefix.getSize(); i++)
	{
		if (i >= text.getSize() || text[i] != prefix[i])
			return false;
	}

	return true;
}

void printMenu()
{
	std::cout << "1. Edit" << std::endl;
	std::cout << "  a. Customer" << std::endl;
	printCustomerMenu();
	std::cout << "  b. Account" << std::endl;
	printAccountMenu();
	std::cout << "2. List" << std::endl;
	printListMenu();
	std::cout << "3. Action" << std::endl;
	printAccountMenu();
	std::cout << "4. Display info for the bank" << std::endl;
	std::cout << "5. Quit" << std::endl;
}

void printEditMenu()
{
	std::cout << "  a. Customer" << std::endl;
	std::cout << "  b. Account" << std::endl;
}

void printCustomerMenu()
{
	std::cout << "    i. Add new customer" << std::endl;
	std::cout << "    ii. Delete customer" << std::endl;
}

void printAccountMenu()
{
	std::cout << "    i. Add new account" << std::endl;
	std::cout << "    ii. Delete account" << std::endl;
}

void printListMenu()
{
	std::cout << "  a. List all customers" << std::endl;
	std::cout << "  b. List all accounts" << std::endl;
	std::cout << "  c. List customer account" << std::endl;
	std::cout << "  d. List log" << std::endl;
}

void printActionMenu()
{
	std::cout << "  a. Withdraw from account" << std::endl;
	std::cout << "  b. Deposit to account" << std::endl;
	std::cout << "  c. Transfer" << std::endl;
}