#pragma once
class Item
{
	double price;
	size_t quantity;
	char* name;
	void copyFrom(const Item& item);
	void free();

public:
	Item();
	~Item();
	Item(const char* name, size_t quantity, double price);
	Item(const Item& other);
	Item& operator=(const Item& other);


	const char* getName() const;
	size_t getQuantity() const;
	double getPrice() const;

	void setName(const char* name);
	void setQuantity(size_t quantity);
	void setPrice(double price);

	void increaseQuantity(size_t quantity);
};
