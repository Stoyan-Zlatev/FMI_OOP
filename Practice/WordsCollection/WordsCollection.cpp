#include "WordsCollection.h"
#include <cstring>
#include <fstream>
#include <iostream>
#pragma warning(disable:4996)

const size_t DEFAULT_CELLS_ALLOCATION = 8;

void swap(MyString& col1, MyString& col2)
{
	MyString temp = col1;
	col1 = col2;
	col2 = temp;
}

void WordsCollection::selectionSort()
{
	for (size_t i = 0; i < wordsCount - 1; i++)
	{
		int minElementIndex = i;
		for (size_t j = i + 1; j < wordsCount; j++)
		{
			if (words[j] < words[minElementIndex])
				minElementIndex = j;
		}
		if (minElementIndex != i)
		{
			swap(words[minElementIndex], words[i]);
		}
	}
}

int WordsCollection::binarySearch(const MyString searched)
{
	size_t fromIndex = 0;
	size_t toIndex = wordsCount - 1;

	while (fromIndex <= toIndex)
	{
		size_t midIndex = fromIndex + (toIndex - fromIndex) / 2;

		if (words[midIndex] == searched)
			return midIndex;

		if (words[midIndex] < searched)
			fromIndex = midIndex + 1;
		else
			toIndex = midIndex - 1;
	}

	return -1;
}

void WordsCollection::copyFrom(const WordsCollection& other)
{
	words = new MyString[other.getSize() + 1];
	for (size_t i = 0; i < other.getSize(); i++)
	{
		words[i] = new char[other.words[i].getSize() + 1];
		words[i] = other.words[i];
	}
	wordsCount = other.wordsCount;
}
void WordsCollection::free()
{
	delete[] words;
	wordsCount = 0;
}

WordsCollection::WordsCollection()
{
	words = new MyString[DEFAULT_CELLS_ALLOCATION];
	wordsCount = 0;
}

WordsCollection::WordsCollection(const MyString* data, size_t size)
{
	wordsCount = size;
	words = new MyString[wordsCount / DEFAULT_CELLS_ALLOCATION + DEFAULT_CELLS_ALLOCATION];
	for (size_t i = 0; i < wordsCount; i++)
	{
		words[i] = new char[data[i].getSize() + 1];
		words[i] = data[i];
	}
	selectionSort();
}

WordsCollection::WordsCollection(const WordsCollection& other)
{
	copyFrom(other);
}

WordsCollection& WordsCollection::operator=(const WordsCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

WordsCollection::~WordsCollection()
{
	free();
}

size_t WordsCollection::getSize() const
{
	return wordsCount;
}

void WordsCollection::resize()
{
	cells *= 2;
	MyString* tempWords = new MyString[cells];
	for (size_t i = 0; i < wordsCount; i++)
	{
		tempWords[i] = words[i];
	}
	words = tempWords;
}

void WordsCollection::add(size_t index, const MyString& str)
{
	MyString* tempWords = new MyString[wordsCount - (index + 1)];
	for (size_t i = index; i < wordsCount; i++)
	{
		tempWords[i - index] = words[i];
	}
	words[index] = str;
	for (size_t i = index + 1; i < wordsCount + 1; i++)
	{
		words[i] = tempWords[i - (index + 1)];
	}
}

void WordsCollection::remove(size_t index, const MyString& str)
{
	MyString* tempWords = new MyString[wordsCount - (index + 2)];
	for (size_t i = index + 1; i < wordsCount; i++)
	{
		tempWords[i - (index + 1)] = words[i];
	}

	words[index] = str;

	for (size_t i = index; i < wordsCount - 1; i++)
	{
		words[i] = tempWords[i - index];
	}
}

WordsCollection& WordsCollection::operator*=(const MyString str)
{
	if (binarySearch(str)==-1)
	{
		if (wordsCount + 1 == cells)
		{
			resize();
		}

		size_t indexToPut = binarySearch(str);

		if (indexToPut == wordsCount)
		{
			words[wordsCount] = str;
		}
		else
		{
			add(indexToPut, str);
		}
		wordsCount += 1;
	}

	return *this;
}

WordsCollection& WordsCollection::operator/=(const MyString str)
{
	if (binarySearch(str) == -1)
	{
		size_t indexToRemove = binarySearch(str);

		if (indexToRemove == wordsCount)
		{
			words[wordsCount] = MyString();
		}
		else
		{
			remove(indexToRemove, str);
		}
		wordsCount += 1;
	}

	return *this;
}

WordsCollection& WordsCollection::operator+=(const WordsCollection& other)
{
	for (size_t i = 0; i < other.getSize(); i++)
	{
		*this *= (other.words[i]);
	}

	return *this;
}

WordsCollection& WordsCollection::operator-=(const WordsCollection& other)
{
	for (size_t i = 0; i < other.getSize(); i++)
	{
		*this /= (other.words[i]);
	}

	return *this;
}

const WordsCollection operator+(const WordsCollection& lhs, const WordsCollection& rhs)
{
	WordsCollection
		lhsCopy(lhs);
	lhsCopy += rhs;

	return lhsCopy;
}

const WordsCollection operator-(const WordsCollection& lhs, const WordsCollection& rhs)
{
	WordsCollection lhsCopy(lhs);
	lhsCopy -= rhs;

	return lhsCopy;
}

std::ostream& operator<<(std::ostream& os, const WordsCollection& v)
{
	os << "{ ";
	for (int i = 0; i < v.getSize(); i++)
		os << v[i] << " ";
	os << " }";

	return os;
}

std::istream& operator>>(std::istream& is, WordsCollection& v)
{
	is >> v[v.getSize()];

	return is;
}

bool WordsCollection::operator[](MyString str)
{
	return binarySearch(str)!=-1;
}

