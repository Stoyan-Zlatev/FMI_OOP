#pragma once
#include "Animal.h"
#include "FarmFactory.h"

class Farm
{
	Animal** animals;
	size_t animalsCount;
	size_t capacity;

	void copyFrom(const Farm& other);
	void free();
	void resize();

	FarmFactory factory;
public:
	Farm();
	Farm(const Farm& other);
	Farm& operator=(const Farm& other);
	~Farm();

	void allSayHello() const;

	Animal::AnimalType getTypeByIndex(size_t index) const;

	size_t getCount() const;
	bool isEmpty() const;

	void addAnimal(const Animal& animal);
	void addAnimal(Animal::AnimalType type);
};