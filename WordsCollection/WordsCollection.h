#pragma once
#include "MyString.h"

class WordsCollection
{
	MyString* words;
	size_t wordsCount;

	void copyFrom(const WordsCollection&);
	void free();
public:
	WordsCollection();
	WordsCollection(const MyString*, size_t);

	WordsCollection(const WordsCollection&);
	WordsCollection& operator=(const WordsCollection&);
	~WordsCollection();

	size_t getSize() const;
};
