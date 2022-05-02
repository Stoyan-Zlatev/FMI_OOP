#pragma once
#include "Book.h"

class BooksCollection
{
	size_t booksCount;
	size_t allocatedCellsCount;
	Book* booksCollection;
	void copyFrom(const BooksCollection& other);
	void free();
	void resize();
public:
	BooksCollection();
	void addBook(const Book& book);
	bool containsBook(const Book& book) const;

	size_t getBooksCount() const;
};