#include "Bank.h"
#include "Serialize.h"
#include <exception>
#include <iostream>

int Bank::getUserIndex(const MyString& customerName) const
{
	for (size_t i = 0; i < customers.getCount(); i++)
	{
		if (customers.data[i]->getName() == customerName)
		{
			return i;
		}
	}

	return -1;
}

int Bank::getAccountIndex(const MyString& iban) const
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

void Bank::addCustomer(const MyString& username, const MyString& address)
{
	if (getUserIndex(username) >= 0)
	{
		throw std::invalid_argument("This user already exists!");
	}

	size_t customerId = customers.getCount() > 0 ? customers.data[customers.getCount() - 1]->getId() + 1 : 1;

	customers.add(Customer(customerId, username, address));

	MyString transaction = "Added customer " + username + " with adress " + address;
	log.add(std::move(transaction));
}

void Bank::deleteCustomer(const MyString& username)
{
	int userIndex = getUserIndex(username);
	if (userIndex == -1)
	{
		throw std::invalid_argument("This user does not exists!");
	}

	customers.removeAt(userIndex);
	MyString transaction = "Deleted customer " + username;
	log.add(std::move(transaction));
}

void Bank::addAccount(const MyString& iban, const MyString& username, const MyString& password, size_t accountType, double additional)
{
	if (getUserIndex(username) == -1)
	{
		throw std::invalid_argument("This user does not exists!");
	}

	size_t accountId = accounts.count > 0 ? accounts.data[accounts.count - 1]->getId() + 1 : 1;
	MyString accType;

	if (accountType == 1)
	{
		accounts.addNormalAccount(username, password, iban, accountId);
		accType = "normal account";
	}
	else if (accountType == 2)
	{
		accounts.addPrivilegeAccount(username, password, iban, accountId, additional);
		accType = "privilege account";
	}
	else if (accountType == 3)
	{
		accounts.addSavingsAccount(username, password, iban, accountId, additional);
		accType = "savings account";
	}
	else
		throw std::invalid_argument("Invalid acccount type!");

	MyString transaction = "Added " + accType + " with iban: " + iban + " and holder: " + username;
	log.add(std::move(transaction));
}

void Bank::deleteAccount(const MyString& iban)
{
	size_t accountIndex = getAccountIndex(iban);
	if (accountIndex == -1)
	{
		throw std::invalid_argument("This account does not exist!");
	}

	accounts.removeAt(accountIndex);
	MyString transaction = "Remove account with iban: " + iban;
	log.add(std::move(transaction));
}

void Bank::listAllCustomers() const
{
	for (size_t i = 0; i < customers.count; i++)
	{
		std::cout << customers.data[i]->getName() << std::endl;
	}
}

void Bank::listAllAccounts() const
{
	accounts.printAllAccounts();
}

void Bank::listLog() const
{
	if (log.count == 0)
	{
		throw std::invalid_argument("There are not any transactions yet!");
	}

	for (size_t i = 0; i < log.count; i++)
	{
		std::cout << log.data[i] << std::endl;
	}
}

void Bank::exportLog(std::ofstream& sourceFile)
{
	sourceFile.write((const char*)&log.count, sizeof(log.count));
	for (size_t i = 0; i < log.count; i++)
	{
		writeString(sourceFile, *(log.data[i]));
	}
}

void Bank::listCustomerAccounts(const MyString& username) const
{
	if (getUserIndex(username) == -1)
	{
		throw std::invalid_argument("This user does not exist!");
	}

	for (size_t i = 0; i < accounts.count; i++)
	{
		if (accounts.data[i]->getUsername() == username)
		{
			accounts.data[i]->display();
		}
	}
}

void Bank::transfer(const MyString& senderIban, const MyString& receiverIban, double amount)
{
	int senderAccountIndex = getAccountIndex(senderIban);

	if (senderAccountIndex == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!");
	}

	int receiverAccountIndex = getAccountIndex(receiverIban);

	if (receiverAccountIndex == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!");
	}

	accounts.data[senderAccountIndex]->withdraw(amount);
	accounts.data[receiverAccountIndex]->deposit(amount);
}

void Bank::deposit(const MyString& iban, double amount)
{
	int receiverAccountIndex = getAccountIndex(iban);

	if (receiverAccountIndex == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!");
	}

	accounts.data[receiverAccountIndex]->deposit(amount);
}

void Bank::withdraw(const MyString& iban, double amount)
{
	int accountIndex = getAccountIndex(iban);

	if (accountIndex == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!");
	}

	accounts.data[accountIndex]->withdraw(amount);
}

void Bank::load(std::ifstream& sourceFile)
{
	readString(sourceFile, name);
	readString(sourceFile, address);
	sourceFile.read((char*)&customers.count, sizeof(customers.count));
	for (size_t i = 0; i < customers.count; i++)
	{
		customers.data[i]->readFromFile(sourceFile);
	}

	sourceFile.read((char*)&log.count, sizeof(log.count));
	for (size_t i = 0; i < log.count; i++)
	{
		readString(sourceFile, *(log.data[i]));
	}

	sourceFile.read((char*)&accounts.count, sizeof(accounts.count));
	for (size_t i = 0; i < accounts.count; i++)
	{
		accounts.data[i]->readFromFile(sourceFile);
	}
}

void Bank::saveToFile(std::ofstream& sourceFile)
{
	writeString(sourceFile, name);
	writeString(sourceFile, address);
	sourceFile.write((const char*)&customers.count, sizeof(customers.count));
	for (size_t i = 0; i < customers.count; i++)
	{
		customers.data[i]->saveToFile(sourceFile);
	}

	exportLog(sourceFile);

	sourceFile.write((const char*)&accounts.count, sizeof(accounts.count));
	for (size_t i = 0; i < accounts.count; i++)
	{
		accounts.data[i]->saveToFile(sourceFile);
	}
}
