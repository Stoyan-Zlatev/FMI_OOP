#pragma once
#include "GlobalConstants.h"

template <typename T>
class Collection
{
	size_t count;
	size_t capacity;
	T** data;
	void copyFrom(const Collection<T>& other);
	void free();
	void resize();
public:
	Collection();
	Collection(const Collection<T>& other);
	Collection(const Collection<T>&& other);
	Collection<T>& operator=(const Collection<T>& other);
	Collection<T>& operator= (Collection<T>&& other);

	void add(const T& element);
	void edit(const T& element, int index);
	void remove(const T& element);
	void removeAt(size_t index);

	size_t getCount() const;
	T getElementAt(size_t index) const;

	~Collection();
};

template <typename T>
Collection<T>::Collection()
{
	data = new T * [DEFAULT_ALLOCATED_CELLS]();
	count = 0;
	capacity = DEFAULT_ALLOCATED_CELLS;
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
void Collection<T>::copyFrom(const Collection<T>& other)
{
	data = new  T * [other.capacity];
	for (size_t i = 0; i < other.count; i++)
	{
		data[i] = new T(*other.data[i]);
	}

	count = other.count;
	capacity = other.capacity;
}

template <typename T>
void Collection<T>::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete data[i];
	}

	delete[] data;
}

template <typename T>
void Collection<T>::resize()
{
	capacity *= ResizeFactor;
	T** newData = new T * [capacity];

	for (int i = 0; i < count; i++) {
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
}

template <typename T>
void Collection<T>::add(const T& element)
{
	if (count >= capacity)
	{
		resize();
	}

	data[count++] = new T(element);
}

template <typename T>
void Collection<T>::edit(const T& element, int index)
{
	if (index<0 || index>count)
	{
		throw std::invalid_argument("This element does not exist!\n");
	}

	(*data)[index] = element;
}

template <typename T>
void Collection<T>::remove(const T& element)
{
	if (count == 0)
	{
		throw std::invalid_argument("It is already empty!\n");
	}

	for (size_t i = 0; i < count; i++)
	{
		if (data[i] == element) {
			removeAt(i);
			return;
		}
	}
}

template <typename T>
void Collection<T>::removeAt(size_t index) {
	if (index >= count)
	{
		throw std::invalid_argument("Index out of range!\n");
	}

	--count;

	for (size_t i = index; i < count; i++)
	{
		data[index] = data[index + 1];
	}
	delete data[count];
}

template <typename T>
size_t Collection<T>::getCount() const
{
	return count;
}

template <typename T>
Collection<T>::Collection(const Collection<T>&& other) {
	data = other.data;
	count = other.count;
	capacity = other.capacity;
	other.data = nullptr;
}

template <typename T>
Collection<T>& Collection<T>::operator= (Collection<T>&& other) {
	for (size_t i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;
	data = other.data;
	count = other.count;
	capacity = other.capacity;
	other.data = nullptr;

	return (*this);
}

template <typename T>
T Collection<T>::getElementAt(size_t index) const
{
	return (*data[index]);
}
