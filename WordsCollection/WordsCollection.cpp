#include "WordsCollection.h"
#include <cstring>
#pragma warning(disable:4996)

const size_t DEFAULT_CELLS_ALLOCATION = 8;

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
}

WordsCollection::WordsCollection()
{
	words = new MyString[DEFAULT_CELLS_ALLOCATION];
	wordsCount = 0;
}

WordsCollection::WordsCollection(const MyString* data, size_t size)
{
	wordsCount = size;
	words = new MyString[wordsCount/DEFAULT_CELLS_ALLOCATION+DEFAULT_CELLS_ALLOCATION];
	for (size_t i = 0; i < wordsCount; i++)
	{
		words[i] = new char[data[i].getSize() + 1];
		words[i] = data[i];
	}
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
