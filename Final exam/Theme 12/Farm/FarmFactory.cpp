#include "FarmFactory.h"
#include "Dog.h"
#include "Cat.h"

Animal* FarmFactory::createAnimal(Animal::AnimalType type) const
{
	switch (type)
	{
	case Animal::Dog: return new Dog();
	case Animal::Cat: return new Cat();
	default: return nullptr;
	}
}
