#pragma once
#include "Animal.h"
class Cat : public Animal
{
public:
	Cat()
	{
		type = Animal::AnimalType::Cat;
	}
	void sayHello() const override;
	Animal* clone() const override;
};