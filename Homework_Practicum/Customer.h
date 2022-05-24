#pragma once
#include "MyString.h"
class Customer
{
	size_t id;
	MyString name;
	MyString address;
	void setId(size_t id);
public:
	Customer();
	Customer(size_t id, const MyString& name, const MyString& address);
	void saveToFile(std::fstream& file);
	void readFromFile(std::fstream& file);

	void setName(const MyString& name);
	void setAdress(const MyString& adress);

	const MyString getName() const;
	const MyString getAddress() const;
	size_t getId() const;
};