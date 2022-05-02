#include "Page.h"
#include <cstring>
#pragma warning(disable:4996)

Page::Page() : Page("", 0) {}

Page::Page(const char* pageContent, size_t pageNumber)
{
	setPageContent(pageContent);
	setPageNumber(pageNumber);
}

void Page::setPageContent(const char* pageContent)
{
	if (pageContent == nullptr)
	{
		return;
	}

	strcpy(this->content, pageContent);
}

void Page::setPageNumber(size_t pageNumber)
{
	if (pageNumber <= 0)
	{
		return;
	}

	this->pageNumber = pageNumber;
}

size_t Page::getPageNumber() const
{
	return pageNumber;
}

const char* Page::getPageContent() const
{
	return content;
}