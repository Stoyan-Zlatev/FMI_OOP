#include "Farm.h"
#include <exception>

void Farm::copyFrom(const Farm& other)
{
	animals = new Animal * [other.capacity];
	capacity = other.capacity;
	animalsCount = other.animalsCount;
	
	for (size_t i = 0; i < animalsCount; i++)
	{
		animals[i] = other.animals[i]->clone();
	}
}
void Farm::free()
{
	for (size_t i = 0; i < animalsCount; i++)
		delete animals[i];
	delete[] animals;
}

void Farm::resize()
{
	Animal** temp = new Animal * [capacity *= 2];

	for (size_t i = 0; i < animalsCount; i++)
	{
		temp[i] = animals[i];
	}

	delete[] animals;
	animals = temp;
}

Farm::Farm()
{
	capacity = 8;
	animalsCount = 0;
	animals = new Animal * [capacity];
}

Farm::Farm(const Farm& other)
{
	copyFrom(other);
}

Farm& Farm::operator=(const Farm& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Farm::~Farm()
{
	free();
}

void Farm::allSayHello() const
{
	for (size_t i = 0; i < animalsCount; i++)
	{
		if (animals[i] != nullptr)
			animals[i]->sayHello();
	}
}

Animal::AnimalType Farm::getTypeByIndex(size_t index) const
{
	if (index >= capacity)
		throw "Error";

	return animals[index]->getType();
}

void Farm::addAnimal(const Animal& animal)
{
	if (animalsCount == capacity)
		resize();

	animals[animalsCount++] = new Animal(animal);
}