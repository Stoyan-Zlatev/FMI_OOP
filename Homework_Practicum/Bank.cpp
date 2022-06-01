#include "Bank.h"
#include "Account.h"
#include "Serialize.h"
#include <exception>
#include <iostream>

int Bank::getUserIndex(size_t customerId) const
{
	for (size_t i = 0; i < customers.getCount(); i++)
	{
		if (customers.data[i]->getId() == customerId)
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

Bank::Bank() :Bank("", "") {}

Bank::Bank(const MyString& bankName, const MyString& bankAddress)
{
	setBankName(bankName);
	setBankAdress(bankAddress);
}

void Bank::addCustomer(const MyString& customerName, const MyString& customerAddress)
{
	size_t customerId = customers.getCount() > 0 ? customers.data[customers.getCount() - 1]->getId() + 1 : 1;

	customers.add(Customer(customerId, customerName, customerAddress));

	MyString transaction = "Added customer " + customerName + " with adress " + customerAddress;
	log.add(std::move(transaction));
}

void Bank::deleteCustomer(size_t customerId)
{
	int userIndex = getUserIndex(customerId);
	if (userIndex == -1)
	{
		throw std::invalid_argument("This user does not exists!\n");
	}

	MyString transaction = "";
	for (size_t accountIndex = 0; accountIndex < accounts.count; accountIndex++)
	{
		if (accounts.data[accountIndex]->getCustomerId() == customers.data[userIndex]->getId())
		{
			transaction = "Deleted account with iban: " + accounts.data[accountIndex]->getIban();
			accounts.removeAt(accountIndex);
			log.add(std::move(transaction));
		}
	}

	customers.removeAt(userIndex);
	transaction = "Deleted customer with id: " + (MyString)customerId;
	log.add(std::move(transaction));
}

void Bank::addAccount(const MyString& iban, const MyString& username, const MyString& password, size_t customerId, size_t accountType)
{
	size_t userIndex = getUserIndex(customerId);
	if (userIndex == -1)
	{
		throw std::invalid_argument("This user does not exists!");
	}

	MyString accType;

	if (accountType == 1)
	{
		accounts.addNormalAccount(username, password, iban, customerId);
		accType = "normal account";
	}
	else if (accountType == 2)
	{
		double overdraft;
		std::cout << "Enter overdraft: ";
		std::cin >> overdraft;
		std::cin.ignore();
		accounts.addPrivilegeAccount(username, password, iban, customerId, overdraft);
		accType = "privilege account";
	}
	else if (accountType == 3)
	{
		double interestRate;
		std::cout << "Enter interest rate: ";
		std::cin >> interestRate;
		std::cin.ignore();
		accounts.addSavingsAccount(username, password, iban, customerId, interestRate);
		accType = "savings account";
	}
	else
	{
		throw std::invalid_argument("Invalid acccount type!");
	}

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
	if (customers.count == 0)
	{
		std::cout << "There are no customers in the system yet!" << std::endl;
	}

	for (size_t customerIndex = 0; customerIndex < customers.count; customerIndex++)
	{
		std::cout << "Customer number " << (customerIndex + 1) << std::endl;
		std::cout << "Name: " << customers.data[customerIndex]->getName() << std::endl;
		std::cout << "Address: " << customers.data[customerIndex]->getAddress() << std::endl;
		std::cout << "Id: " << customers.data[customerIndex]->getId() << std::endl;
		std::cout << std::endl;
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
		throw std::invalid_argument("There are not any transactions yet!\n");
	}

	for (size_t logIndex = 0; logIndex < log.count; logIndex++)
	{
		std::cout << log.data[logIndex]->c_str() << std::endl;
	}
}

void Bank::exportLog()
{
	std::ofstream logFile("log.txt");

	if (!logFile.is_open())
	{
		throw std::invalid_argument("Error while opening the file!\n");
	}

	logFile << log.count << '\n';
	for (size_t logIndex = 0; logIndex < log.count; logIndex++)
	{
		logFile << *(log.data[logIndex]) << '\n';
	}

	logFile.close();
}

void Bank::importLog()
{
	size_t count;
	std::ifstream logFile("log.txt", std::ios::in);

	if (!logFile.is_open())
	{
		throw std::invalid_argument("Error while opening the log file!\n");
	}

	MyString accountCount;
	accountCount.readLine(logFile);
	count = std::atoi(accountCount.c_str());

	for (size_t i = 0; i < count; i++)
	{
		MyString str;
		str.readLine(logFile);
		log.add(str);
	}

	logFile.close();
}

void Bank::listCustomerAccounts(size_t customerId) const
{
	if (getUserIndex(customerId) == -1)
	{
		throw std::invalid_argument("This user does not exist!");
	}

	if (accounts.count == 0)
	{
		throw std::invalid_argument("This customer has no accounts in the system yet!\n");
	}

	for (size_t accountIndex = 0; accountIndex < accounts.count; accountIndex++)
	{
		if (accounts.data[accountIndex]->getCustomerId() == customerId)
		{
			accounts.data[accountIndex]->display();
		}

		std::cout << std::endl;
	}
}

void Bank::transfer(const MyString& senderIban, const MyString& receiverIban, double amount)
{
	int senderAccountIndex = getAccountIndex(senderIban);

	if (senderAccountIndex == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!\n");
	}

	int receiverAccountIndex = getAccountIndex(receiverIban);

	if (receiverAccountIndex == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!\n");
	}

	accounts.data[senderAccountIndex]->withdraw(amount);
	accounts.data[receiverAccountIndex]->deposit(amount);
	MyString transaction = "Transfered money from account with iban: " + accounts.data[senderAccountIndex]->getIban() + " "
		+ "to account with iban: " + accounts.data[receiverAccountIndex]->getIban();
	log.add(std::move(transaction));
}

void Bank::display() const
{
	std::cout << "Bank: " << name << std::endl;
	std::cout << "Customers count: " << customers.count << std::endl;
	std::cout << "Accounts count: " << accounts.count << std::endl;
}

void Bank::deposit(const MyString& iban, double amount)
{
	int receiverAccountIndex = getAccountIndex(iban);

	if (receiverAccountIndex == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!\n");
	}

	accounts.data[receiverAccountIndex]->deposit(amount);
	MyString transaction = "Deposited to account with iban: " + accounts.data[receiverAccountIndex]->getIban();
	log.add(std::move(transaction));
}

void Bank::withdraw(const MyString& iban, double amount)
{
	int accountIndex = getAccountIndex(iban);

	if (accountIndex == -1)
	{
		throw std::invalid_argument("Account with this iban does not exist!\n");
	}

	accounts.data[accountIndex]->withdraw(amount);
	MyString transaction = "Withdrew from account with iban: " + accounts.data[accountIndex]->getIban();
	log.add(std::move(transaction));
}

void Bank::setBankName(const MyString& bankName)
{
	if (bankName.getSize() > MaxNameLength)
	{
		throw std::invalid_argument("Entered name is too long.\n");
	}

	name = bankName;
}

void Bank::setBankAdress(const MyString& bankAddress)
{
	if (bankAddress.getSize() > MaxContentLength)
	{
		throw std::invalid_argument("Entered adress is too long.\n");
	}

	address = bankAddress;
}

MyString Bank::getBankName() const
{
	return name;
}

MyString Bank::getBankAdress() const
{
	return address;
}

void Bank::load(std::ifstream& sourceFile)
{
	readString(sourceFile, name);
	readString(sourceFile, address);
	size_t count;
	sourceFile.read((char*)&count, sizeof(count));
	for (size_t i = 0; i < count; i++)
	{
		Customer customer;

		customer.readFromFile(sourceFile);
		customers.add(customer);
	}

	sourceFile.read((char*)&count, sizeof(count));
	AccountType accountType;
	Account* account = nullptr;
	for (size_t i = 0; i < count; i++)
	{
		sourceFile.read((char*)&accountType, sizeof(accountType));
		if (accountType == AccountType::Normal)
		{
			account = new NormalAccount();
		}
		else if (accountType == AccountType::Privilige)
		{
			account = new PrivilegeAccount();
		}
		else if (accountType == AccountType::Savings)
		{
			account = new SavingsAccount();
		}
		double additional = 0;
		account->readFromFile(sourceFile);

		accounts.addAccount(account);
	}

	sourceFile.close();

	importLog();
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

	sourceFile.write((const char*)&accounts.count, sizeof(accounts.count));
	for (size_t i = 0; i < accounts.count; i++)
	{
		accounts.data[i]->saveToFile(sourceFile);
	}

	sourceFile.close();

	exportLog();
}
