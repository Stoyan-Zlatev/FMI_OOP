#include "Customer.h"
#include "GlobalConstants.h"
#include <exception>
#include "Serialize.h"

void Customer::setName(const MyString& name)
{
	if (name.getSize() > MaxNameLength)
	{
		throw std::invalid_argument("Entered name is too long.");
	}

	this->name = name;
}

void Customer::setAdress(const MyString& address)
{
	if(address.getSize()>MaxContentLength)
	{
		throw std::invalid_argument("Entered adress is too long.");
	}

	this->address = address;
}

void Customer::setId(size_t id)
{
	this->id = id;
}

const MyString Customer::getName() const
{
    return name;
}

const MyString Customer::getAddress() const
{
	return address;
}

size_t Customer::getId() const
{
	return id;
}

Customer::Customer() :Customer(0, "", "") {};

Customer::Customer(size_t id, const MyString& name, const MyString& address)
{
	setId(id);
	setName(name);
	setAdress(address);
}

void Customer::saveToFile(std::ofstream& sourceFile)
{
	sourceFile.write((const char*)&id, sizeof(id));
	writeString(sourceFile, name);
	writeString(sourceFile, address);
}

void Customer::readFromFile(std::ifstream& file)
{
	file.read((char*)&id, sizeof(id));
	readString(file, name);
	readString(file, address);
}
