#include <iostream>
#include <fstream>
#include "Item.h"
#include "ShoppingCart.h"

int main()
{
	Item item1("Basketball", 2, 5);
	Item item2("Football", 1, 2.50);
	Item item3("Gloves", 3, 10);

	ShoppingCart cart;
	cart.addItem(item2);
	cart.addItem(item2);
	cart.addItem(item3);

	ShoppingCart cart2(cart);
	cart2.addItem(item1);
	cart2.removeItem(item2.getName());
	std::cout << "Items in shopping cart:" << std::endl;
	cart2.printItemsInCart();
	std::cout << std::endl;

	std::cout << "Price of gloves: " << cart2.getPriceOf("Gloves") << "$" << std::endl;
	std::cout << "Price of basketball: " << cart2.getPriceOf("Basketball") << "$" << std::endl;

	std::cout << "Shopping cart contains football: " << std::boolalpha << cart2.exists("Football") << std::endl;
	std::cout << "Shopping cart contains basketball: " << std::boolalpha << cart2.exists("Basketball") << std::endl;
	std::cout << "Count of items in shopping cart: " << cart2.getItemsCount() << std::endl;
	std::cout << "Shopping cart total price: " << cart2.totalPrice() << "$" << std::endl;

	std::fstream stream("ShoppingCart.txt", std::ios::app);
	cart2.save(stream);
}
