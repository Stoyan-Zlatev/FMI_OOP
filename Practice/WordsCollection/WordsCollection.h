#pragma once
#include "MyString.h"

class WordsCollection
{
	MyString* words;
	size_t wordsCount;
	size_t cells;

	void copyFrom(const WordsCollection&);
	void free();
public:
	WordsCollection();
	WordsCollection(const MyString*, size_t);

	WordsCollection(const WordsCollection&);
	WordsCollection& operator=(const WordsCollection&);
	~WordsCollection();

	WordsCollection& operator*=(MyString str);
	WordsCollection& operator/=(const MyString str);
	WordsCollection& operator+=(const WordsCollection& other);
	WordsCollection& operator-=(const WordsCollection& other);

	bool operator[](MyString str);


	friend std::ostream& operator<<(std::ostream& os, const WordsCollection& v);
	friend std::istream& operator>>(std::istream&, WordsCollection& v);

	size_t getPutIndex(const MyString& str) const;
	void resize();
	void add(size_t index, const MyString& str);
	void remove(size_t index, const MyString& str);
	void selectionSort();
	int binarySearch(const MyString searched);

	int& operator[](size_t); //get set

	int operator[](size_t) const; // get

	size_t getSize() const;
};

const WordsCollection operator+(const WordsCollection& lhs, const WordsCollection& rhs);
const WordsCollection operator-(const WordsCollection& lhs, const WordsCollection& rhs);
