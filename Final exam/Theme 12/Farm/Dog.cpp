#include "Dog.h"
#include <iostream>

void Dog::sayHello() const
{
	std::cout << "Hello, I am a Dog!" << std::endl;
}

Animal* Dog::clone() const
{
	return new Dog(*this);
}