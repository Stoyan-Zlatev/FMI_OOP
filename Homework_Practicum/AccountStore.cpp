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

void AccountStore::resizeDown(size_t index)
{
	capacity /= ResizeFactor;
	Account** newData = new Account * [capacity];

	for (size_t i = 0; i < index; i++)
	{
		newData[i] = data[i];
	}

	for (size_t i = index; i < count; i++)
	{
		newData[i] = data[i + 1];
	}

	for (size_t i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;
	data = newData;
	return;
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

void AccountStore::addNormalAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
	double amount, time_t dateOfCreation)
{
	if (isIbanUnique(iban))
		data[count++] = new NormalAccount(username, password, iban, id, amount, dateOfCreation);
}

void AccountStore::addPrivilegeAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
	double overdraft, double amount, time_t dateOfCreation)
{
	if (isIbanUnique(iban))
		data[count++] = new PrivilegeAccount(username, password, iban, id, overdraft, amount, dateOfCreation);
}

void AccountStore::addSavingsAccount(const MyString& username, const MyString& password, const MyString& iban, size_t id,
	double interestRate, double amount, time_t dateOfCreation)
{
	if (isIbanUnique(iban))
		data[count++] = new SavingsAccount(username, password, iban, id, interestRate, amount, dateOfCreation);
}

void AccountStore::remove(const Account& element)
{
	if (count == 0)
	{
		throw std::invalid_argument("It is already empty!");
	}

	for (size_t i = 0; i < count; i++)
	{
		if (data[i]->getIban() == element.getIban()) {
			removeAt(i);
			return;
		}
	}
}

void AccountStore::removeAt(size_t index)
{
	if (index >= count)
	{
		throw std::invalid_argument("Index out of range!");
	}

	--count;

	if (count * ResizeFactor * ResizeFactor <= capacity)
	{
		resizeDown(index);
	}

	for (size_t i = index; i < count; i++)
	{
		data[index] = data[index + 1];
	}

	delete data[count - 1];
}

void AccountStore::printAllAccounts() const
{
	if (count == 0)
	{
		std::cout << "There are no accounts in the system yet!" << std::endl;
	}

	for (size_t i = 0; i < count; i++)
	{
		data[i]->display();
		std::cout << std::endl;
	}
}