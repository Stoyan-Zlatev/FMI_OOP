#include "PagesCollection.h"

void PagesCollection::copyFrom(const PagesCollection& other)
{
	pages = new  Page[other.getPagesCount()];
	for (size_t i = 0; i < other.getPagesCount(); i++)
		pages[i] = other.pages[i];
	pagesCount = other.getPagesCount();
}

void PagesCollection::free()
{
	pagesCount = 0;
	delete[] pages;
}

void PagesCollection::resize()
{
	allocatedCellsCount *= 2;
	Page* newData = new Page[allocatedCellsCount];
	for (int i = 0; i < pagesCount; i++) 
	{
		newData[i] = pages[i];
	}

	delete[] pages;
	pages = newData;
}

PagesCollection::PagesCollection()
{
	pagesCount = 0;
	allocatedCellsCount = DEFAULT_ALLOCATED_CELLS;
}

void PagesCollection::addPage(const Page& page)
{
	if (pagesCount >= allocatedCellsCount)
	{
		resize();
	}

	pages[pagesCount] = page;
	pagesCount++;
}

size_t PagesCollection::getPagesCount() const
{
	return pagesCount;
}
