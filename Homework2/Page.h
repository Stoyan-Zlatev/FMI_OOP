#pragma once
#include "GlobalConstants.h"

class Page
{
	size_t pageNumber;
	char content[MaxContentLength];
public:
	Page();
	Page(const char* pageContent, size_t pageNumber);

	void setPageContent(const char* pageContent);
	void setPageNumber(size_t pageNumber);

	size_t getPageNumber() const;
	const char* getPageContent() const;
};