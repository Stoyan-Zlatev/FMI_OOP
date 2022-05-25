#pragma once
#include "GlobalConstants.h"

template <typename T>
class Collection
{
	size_t count;
	size_t capacity;
	T** data;
	void copyFrom(const Collection& other);
	void free();
	void resize();
	void resizeDown(size_t index);
public:
	Collection();
	Collection(const Collection<T>& other);
	Collection(const Collection&& other);
	Collection<T>& operator=(const Collection<T>& other);
	Collection<T>& operator= (Collection&& other);

	void add(const T& element);
	void edit(const T& element, int index);
	void remove(const T& element);
	void removeAt(size_t index);

	size_t getCount() const;
	friend class Bank;

	~Collection();
};

template <typename T>
Collection<T>::Collection()
{
	data = new T*[DEFAULT_ALLOCATED_CELLS]();
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
void Collection<T>::copyFrom(const Collection& other)
{
	data = new  T*[other.capacity];
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
	for (size_t i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;
}

template <typename T>
void Collection<T>::resize()
{
	capacity *= 2;
	T** newData = new T*[capacity];

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
		throw std::invalid_argument("This element does not exist!");
	}

	(*data)[index] = element;
}

template <typename T>
void Collection<T>::remove(const T& element)
{
	if (count == 0)
	{
		throw std::invalid_argument("It is already empty!");
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
void Collection<T>::resizeDown(size_t index)
{
	capacity /= ResizeFactor;
	T** newData = new T*[capacity];

	for (size_t i = 0; i < index; i++)
	{
		newData[i] = data[i];
	}

	for (size_t i = index; i < count; i++)
	{
		newData[i] = data[i + 1];
	}

	for (size_t i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;
	data = newData;
	return;
}

template <typename T>
void Collection<T>::removeAt(size_t index) {
	if (index >= count)
	{
		throw std::invalid_argument("Index out of range!");
	}

	--count;

	if (count * ResizeFactor * ResizeFactor <= capacity) 
	{
		resizeDown(index);
	}

	for (size_t i = index; i < count; i++)
	{
		data[index] = data[index + 1];
	}

	delete data[count - 1];
}

template <typename T>
size_t Collection<T>::getCount() const
{
	return count;
}

template <typename T>
Collection<T>::Collection(const Collection&& other) {
	data = other.data;
	count = other.count;
	capacity = other.capacity;
	other.data = nullptr;
}
 
template <typename T>
Collection<T>& Collection<T>::operator= (Collection&& other) {
	for (size_t i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;
	data = other.data;
	count = other.count;
	capacity = other.capacity;
	other.data = nullptr;
 
	return (* this);
}