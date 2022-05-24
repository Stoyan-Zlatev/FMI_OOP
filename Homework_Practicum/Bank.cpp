#include "Bank.h"
#include <exception>
#include <iostream>

bool Bank::containsUser(const MyString& customerName) const
{
	for (size_t i = 0; i < customers.getCount(); i++)
	{
		if (customers.collection[i].getName() == customerName)
		{
			return true;
		}
	}

	return false;
}

int Bank::getCustomerId(const MyString& iban) const
{
	for (size_t i = 0; i < accounts.count; i++)
	{
		if (accounts.data[i]->getIban() == iban)
		{
			return i;
		}
	}
	return -1;
}

void Bank::addCustomer()
{
	MyString username;
	username.getline(std::cin);
	if (containsUser(username))
	{
		throw std::invalid_argument("This user already exists!");
	}

	MyString address;
	address.getline(std::cin);

	size_t customerId = customers.collection[customers.getCount()-1].getId() + 1;

	customers.add(Customer(customerId, std::move(username), std::move(address)));
}

void Bank::listAllCustomers() const
{
	for (size_t i = 0; i < customers.count; i++)
	{
		std::cout << customers.collection[i].getName() << std::endl;
	}
}

void Bank::transfer(const MyString& senderIban, const MyString& receiverIban, double amount)
{
	int senderAcountId = getCustomerId(senderIban);

	if (senderAcountId == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!");
	}

	int receiverAccountId = getCustomerId(receiverIban);

	if (senderAcountId == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!");
	}

	accounts.data[senderAcountId]->withdraw(amount);
	accounts.data[senderAcountId]->deposit(amount);
}

void Bank::load(std::fstream& sourceFile)
{
}

void Bank::saveToFile(std::fstream& sourceFile)
{
}
