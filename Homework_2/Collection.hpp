#pragma once
#include "GlobalConstants.h"

template <typename T>
class Collection
{
	size_t count;
	size_t allocatedCellsCount;
	T* collection;
	void copyFrom(const Collection& other);
	void free();
	void resize();
public:
	Collection();
	Collection(const Collection<T>& other);
	Collection<T>& operator=(const Collection<T>& other);

	void add(const T& element);
	void remove();
	T& getElementByIndex(size_t index) const;

	size_t getCount() const;
	friend class Kindle;
	friend class Book;

	~Collection();
};

template <typename T>
Collection<T>::Collection()
{
	collection = new T[DEFAULT_ALLOCATED_CELLS];
	count = 0;
	allocatedCellsCount = DEFAULT_ALLOCATED_CELLS;
}

template <typename T>
Collection<T>::Collection(const Collection<T>& other)
{
	copyFrom(other);
}

template <typename T>
Collection<T>& Collection<T>::operator=(const Collection<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}


template <typename T>
Collection<T>::~Collection()
{
	free();
}

template <typename T>
void Collection<T>::copyFrom(const Collection& other)
{
	collection = new  T[other.count];
	for (size_t i = 0; i < other.count; i++)
		collection[i] = other.collection[i];
	count = other.count;
}

template <typename T>
void Collection<T>::free()
{
	delete[] collection;
	count = 0;
	allocatedCellsCount = DEFAULT_ALLOCATED_CELLS;
}

template <typename T>
void Collection<T>::resize()
{
	allocatedCellsCount *= 2;
	T* newData = new T[allocatedCellsCount];

	for (int i = 0; i < count; i++) {
		newData[i] = collection[i];
	}

	delete[] collection;
	collection = newData;
}

template <typename T>
void Collection<T>::add(const T& element)
{
	if (count >= allocatedCellsCount)
	{
		resize();
	}

	collection[count] = element;
	count++;
}

template <typename T>
void Collection<T>::remove()
{
	count--;
}

template <typename T>
size_t Collection<T>::getCount() const
{
	return count;
}

template <typename T>
T& Collection<T>::getElementByIndex(size_t index) const
{
	return collection[index];
}