#pragma once
#include <iostream>
#include <exception>

template <typename T>
class Optional
{
	T* data;

	void copyFrom(const Optional<T>& other);
	void free();
public:
	Optional();
	Optional(const T& obj);

	Optional(const Optional<T>& other);
	Optional<T>& operator=(const Optional<T>& other);

	bool containsData() const;
	const T& getData() const;
	void setData(const T& el);
	void clear();

	~Optional();
};

template <typename T>
Optional<T>::Optional() : data(nullptr) {}

template <typename T>
Optional<T>::Optional(const T& obj)
{
	setData(obj);
}

template <typename T>
void Optional<T>::setData(const T& obj)
{
	delete data;
	data = new T(obj);
}

template <typename T>
void Optional<T>::copyFrom(const Optional<T>& other)
{
	if (other.containsData())
		data = new T(*other.data);
	else
		data = nullptr;
}

template <typename T>
void Optional<T>::free()
{
	delete data;
}

template <typename T>
void Optional<T>::clear()
{
	free();
	data = nullptr;
}

template <typename T>
Optional<T>::Optional(const Optional<T>& other)
{
	copyFrom(other);
}


template <typename T>
Optional<T>& Optional<T>::operator=(const Optional<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
Optional<T>::~Optional()
{
	free();
}