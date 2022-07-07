#pragma once
#include "Animal.h"

class FarmFactory
{
public:
	Animal* createAnimal(Animal::AnimalType type) const;
};