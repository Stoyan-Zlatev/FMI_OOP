#pragma once
#include "Animal.h"

class Dog : public Animal
{
	Dog()
	{
		type = Animal::AnimalType::Dog;
	}
	void sayHello() const override;
	Animal* clone() const override;
};