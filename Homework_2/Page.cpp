#include "Page.h"
#include "MyString.h"
#include <cstring>
#pragma warning(disable:4996)

Page::Page() : Page("", 0) {}

Page::Page(const MyString& pageContent, size_t pageNumber)
{
	setPageContent(pageContent);
	setPageNumber(pageNumber);
}

void Page::setPageContent(const MyString& pageContent)
{
	/*if (pageContent == "")
	{
		throw std::invalid_argument("Page content should not be empty!");
	}*/

	this->content = pageContent;
}

void Page::setPageNumber(size_t pageNumber)
{
	/*if (pageNumber <= 0)
	{
		throw std::invalid_argument("Page number should be positive number!");
	}*/

	this->pageNumber = pageNumber;
}

size_t Page::getPageNumber() const
{
	return pageNumber;
}

const MyString Page::getPageContent() const
{
	return content;
}

void Page::saveToFile(std::fstream& file)
{
	/*size_t pageNumber;
	MyString content;*/
	file.write((const char*)&pageNumber, sizeof(size_t));

	size_t contentSize = content.getSize();
	file.write((const char*)&contentSize, sizeof(size_t));
	file.write((const char*)content.c_str(),content.getSize());
}
