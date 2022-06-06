#include "AccountStore.h"

void AccountStore::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete data[i];
	}

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

void AccountStore::addAccount(Account* account)
{
	data[count++] = account->clone();
}

void AccountStore::copyFrom(const AccountStore& other)
{
	data = new Account * [other.capacity];
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

bool AccountStore::isIbanUnique(const MyString& iban)
{
	for (size_t i = 0; i < count; i++)
	{
		if (data[i]->getIban() == iban)
		{
			throw std::invalid_argument("Account with this iban already exist!");
		}
	}
	return true;
}

void AccountStore::addNormalAccount(const MyString& username, const MyString& password, const MyString& iban, size_t custoemrId,
	double amount, time_t dateOfCreation)
{
	if (isIbanUnique(iban))
		data[count++] = new NormalAccount(username, password, iban, custoemrId, amount, dateOfCreation);
}

void AccountStore::addPrivilegeAccount(const MyString& username, const MyString& password, const MyString& iban, size_t custoemrId,
	double overdraft, double amount, time_t dateOfCreation)
{
	if (isIbanUnique(iban))
		data[count++] = new PrivilegeAccount(username, password, iban, custoemrId, overdraft, amount, dateOfCreation);
}

void AccountStore::addSavingsAccount(const MyString& username, const MyString& password, const MyString& iban, size_t custoemrId,
	double interestRate, double amount, time_t dateOfCreation)
{
	if (isIbanUnique(iban))
		data[count++] = new SavingsAccount(username, password, iban, custoemrId, interestRate, amount, dateOfCreation);
}

void AccountStore::remove(const Account& element)
{
	if (count == 0)
	{
		throw std::invalid_argument("There are no available accounts!");
	}

	for (size_t accountIndex = 0; accountIndex < count; accountIndex++)
	{
		if (data[accountIndex]->getIban() == element.getIban()) {
			removeAt(accountIndex);
			return;
		}
	}
}

void AccountStore::removeAt(size_t accountIndex)
{
	if (accountIndex >= count)
	{
		throw std::invalid_argument("Index out of range!");
	}

	--count;

	delete data[accountIndex];

	for (size_t currentAccountIndex = accountIndex; currentAccountIndex < count; currentAccountIndex++)
	{
		data[currentAccountIndex] = data[currentAccountIndex + 1];
	}
}

void AccountStore::printAllAccounts() const
{
	if (count == 0)
	{
		std::cout << "There are no accounts in the system yet!" << std::endl;
	}

	for (size_t accountIndex = 0; accountIndex < count; accountIndex++)
	{
		data[accountIndex]->display();
	}
}