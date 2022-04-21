#pragma once
#include "Item.h"

class ShoppingCart
{
	Item* items;
	size_t itemsCount;
	size_t allocatedCellsCount;
	void copyFrom(const ShoppingCart& item);
	void free();
	int getIndexByName(const char* name) const;
	void resize();
public:
	ShoppingCart();
	~ShoppingCart();
	ShoppingCart(const ShoppingCart& shoppingCart);
	ShoppingCart& operator=(const ShoppingCart& other);

	bool addItem(const Item& item);
	bool removeItem(const char* name);
	bool exists(const char* name) const;
	size_t getItemsCount() const;
	bool isEmpty() const;
	double totalPrice() const;
	double getPriceOf(const char* name) const;
	void sortByName();
	void save(std::fstream& stream) const;
	void printItemsInCart() const;
};
