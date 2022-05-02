#pragma once
#include "Page.h"
class PagesCollection
{
	Page* pages;
	size_t pagesCount;
	size_t allocatedCellsCount;
	void copyFrom(const PagesCollection& other);
	void free();
	void resize();
public:
	PagesCollection();

	void addPage(const Page& page);

	size_t getPagesCount() const;
};