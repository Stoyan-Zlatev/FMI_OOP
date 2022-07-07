#include "Cat.h"
#include <iostream>

void Cat::sayHello() const
{
	std::cout << "Hello, I am a Cat!" << std::endl;
}

Animal* Cat::clone() const
{
	return new Cat(*this);
}