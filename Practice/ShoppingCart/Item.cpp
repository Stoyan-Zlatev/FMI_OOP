#include <iostream>
#include "Item.h"
#pragma warning(disable:4996)

void Item::copyFrom(const Item& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	quantity = other.quantity;
	price = other.price;
}

void Item::free()
{
	delete[] this->name;
}

Item::Item() : Item("", 0,0){}

Item::Item(const char* name, size_t quantity, double price)
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
	setQuantity(quantity);
	setPrice(price);
}

Item::Item(const Item& other)
{
	copyFrom(other);
}

Item& Item::operator=(const Item& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Item::~Item()
{
	free();
}

const char* Item::getName() const
{
	return name;
}

size_t Item::getQuantity() const
{
	return quantity;
}

double Item::getPrice() const
{
	return price;
}

void Item::setName(const char* name)
{
	if (strcmp(name, this->name) == 0)
		return;

	delete[] this->name;
	size_t nameLen = strlen(name);
	this->name = new char[nameLen + 1];
	strcpy(this->name, name);
}

void Item::setQuantity(size_t quantity)
{
	if (quantity < 0)
		return;
	this->quantity = quantity;
}

void Item::setPrice(double price)
{
	if (price < 0)
		return;
	this->price = price;
}

void Item::increaseQuantity(size_t quantity)
{
	this->quantity += quantity;
}
