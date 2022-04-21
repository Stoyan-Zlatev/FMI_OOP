#include <iostream>
#include <cstring>
#include <fstream>
#include "ShoppingCart.h"

const int DEFAULT_ALLOCATED_CELLS = 8;

void swap(Item& item1, Item& item2)
{
	Item temp = item1;
	item1 = item2;
	item2 = temp;
}

void ShoppingCart::copyFrom(const ShoppingCart& other)
{
	items = new Item[other.allocatedCellsCount];
	for (size_t i = 0; i < other.allocatedCellsCount; i++)
	{
		items[i] = other.items[i];
	}

	itemsCount = other.itemsCount;
	allocatedCellsCount = other.allocatedCellsCount;
}

void ShoppingCart::free()
{
	delete[] this->items;
}

ShoppingCart::ShoppingCart()
{
	items = new Item[DEFAULT_ALLOCATED_CELLS];
	allocatedCellsCount = DEFAULT_ALLOCATED_CELLS;
	itemsCount = 0;
}


ShoppingCart::ShoppingCart(const ShoppingCart& other)
{
	copyFrom(other);
}

ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ShoppingCart::~ShoppingCart()
{
	free();
}

bool ShoppingCart::exists(const char* name) const
{
	return getIndexByName(name) >= 0;
}

size_t ShoppingCart::getItemsCount() const
{
	return itemsCount;
}

bool ShoppingCart::addItem(const Item& item)
{
	int indexToAdd = getIndexByName(item.getName());
	if (indexToAdd == -1)
	{
		if (itemsCount >= allocatedCellsCount)
		{
			resize();
		}

		itemsCount++;
		items[itemsCount - 1] = item;

		return true;
	}
	items[indexToAdd].increaseQuantity(item.getQuantity());

	return false;
}

bool ShoppingCart::removeItem(const char* name)
{
	size_t indexToRemove = getIndexByName(name);
	if (indexToRemove == -1)
		return false;
	swap(items[indexToRemove], items[itemsCount - 1]);
	itemsCount--;

	return true;
}

void ShoppingCart::resize()
{
	allocatedCellsCount *= 2;
	Item* newData = new Item[allocatedCellsCount];

	for (int i = 0; i < itemsCount; i++) {
		newData[i] = items[i];
	}

	delete[] items;
	items = newData;
}

bool ShoppingCart::isEmpty() const
{
	return itemsCount == 0;
}

double ShoppingCart::totalPrice() const
{
	double totalPrice = 0;
	for (size_t i = 0; i < itemsCount; i++)
	{
		totalPrice += items[i].getPrice() * items[i].getQuantity();
	}
	return totalPrice;
}

int ShoppingCart::getIndexByName(const char* name) const
{
	for (size_t i = 0; i < itemsCount; i++)
	{
		if (strcmp(name, items[i].getName()) == 0)
			return i;
	}

	return -1;
}

double ShoppingCart::getPriceOf(const char* name) const
{
	size_t searchedIndex = getIndexByName(name);
	if (searchedIndex >= 0)
	{
		return items[searchedIndex].getPrice();
	}

	return 0;
}

void selectionSort(Item*& items, size_t itemsCount)
{
	for (size_t i = 0; i < itemsCount - 1; i++)
	{
		int minElementIndex = i;
		for (size_t j = i + 1; j < itemsCount; j++)
		{
			if (strcmp(items[j].getName(), items[minElementIndex].getName()) < 0)
				minElementIndex = j;
		}
		if (minElementIndex != i)
		{
			swap(items[i], items[minElementIndex]);
		}
	}
}

void ShoppingCart::sortByName()
{
	selectionSort(items, itemsCount);
}

void ShoppingCart::save(std::fstream& file) const
{
	for (size_t i = 0; i < itemsCount; i++)
	{
		file << "-";
		file << items[i].getName();
		file << "\nQuantity: " << items[i].getQuantity() << "\n";
		file << "Price: " << items[i].getPrice() << "$" << "\n\n";
	}
}

void ShoppingCart::printItemsInCart() const
{
	for (size_t i = 0; i < itemsCount; i++)
	{
		std::cout << items[i].getQuantity() << " " << items[i].getName() << std::endl;
	}
}
