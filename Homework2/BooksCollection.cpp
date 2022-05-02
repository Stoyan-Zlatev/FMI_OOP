#include "BooksCollection.h"
#include "Book.h"

void BooksCollection::copyFrom(const BooksCollection& other)
{
	booksCollection = new  Book[other.booksCount];
	for (size_t i = 0; i < other.booksCount; i++)
		booksCollection[i] = other.booksCollection[i];
	booksCount = other.booksCount;
}

void BooksCollection::free()
{
	booksCount = 0;
	delete[] booksCollection;
}

void BooksCollection::resize()
{
	allocatedCellsCount *= 2;
	Book* newData = new Book[allocatedCellsCount];

	for (int i = 0; i < booksCount; i++) {
		newData[i] = booksCollection[i];
	}

	delete[] booksCollection;
	booksCollection = newData;
}

BooksCollection::BooksCollection()
{
	booksCount = 0;
	allocatedCellsCount = DEFAULT_ALLOCATED_CELLS;
}


void BooksCollection::addBook(const Book& book)
{
	if (booksCount >= allocatedCellsCount)
	{
		resize();
	}

	booksCollection[booksCount] = book;
	booksCount++;
}

size_t BooksCollection::getBooksCount() const
{
	return booksCount;
}

bool BooksCollection::containsBook(const Book& book) const
{
	for (size_t i = 0; i < booksCount; i++)
	{
		if(booksCollection[i].)
	}
}

