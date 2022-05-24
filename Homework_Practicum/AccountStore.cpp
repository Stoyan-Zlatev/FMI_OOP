#include "AccountStore.h"

void AccountStore::free()
{
	for (size_t i = 0; i < count; i++)
		delete data[i];
	delete[] data;
}

AccountStore::AccountStore()
{
	data = new Account * [DEFAULT_ALLOCATED_CELLS];
	capacity = DEFAULT_ALLOCATED_CELLS;
	count = 0;
}

AccountStore::AccountStore(const AccountStore& other)
{
	copyFrom(other);
}

AccountStore& AccountStore::operator=(const AccountStore& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return (*this);
}

AccountStore::~AccountStore()
{
	free();
}

void AccountStore::copyFrom(const AccountStore& other)
{
	data = new Account * [other.count];
	count = other.count;
	capacity = other.capacity;

	for (size_t i = 0; i < count; i++)
	{
		data[i] = other.data[i]->clone();
	}
}

void AccountStore::resize()
{
	Account** newCollection = new Account * [capacity *= ResizeFactor];
	for (size_t i = 0; i < count; i++)
	{
		newCollection[i] = data[i];
	}

	delete[] data;
	data = newCollection;
}

void AccountStore::addNormalAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
	double amount, time_t dateOfCreation)
{
	data[count++] = new NormalAccount(username, password, iban, id, amount, dateOfCreation);
}

void AccountStore::addPrivilegeAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
	double overdraft, double amount, time_t dateOfCreation)
{
	data[count++] = new PriviligeAccount(username, password, iban, id, overdraft, amount, dateOfCreation);
}

void AccountStore::addSavingsAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
	double interestRate, double amount, time_t dateOfCreation)
{
	data[count++] = new SavingsAccount(username, password, iban, id, interestRate, amount, dateOfCreation);
}

void AccountStore::printAllAccounts() const
{
	for (size_t i = 0; i < count; i++)
	{
		data[i]->display();
	}
}
