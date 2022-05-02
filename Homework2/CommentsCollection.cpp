#include "CommentsCollection.h"
#include "Comment.h"
#include <iostream>

void CommentsCollection::copyFrom(const CommentsCollection& other)
{
	comments = new  Comment[other.commentsCount];
	for (size_t i = 0; i < other.commentsCount; i++)
		comments[i] = other.comments[i];
	commentsCount = other.commentsCount;
}

void CommentsCollection::free()
{
	commentsCount = 0;
	delete[] comments;
}

void CommentsCollection::resize()
{
	allocatedCellsCount *= 2;
	Comment* newData = new Comment[allocatedCellsCount];

	for (int i = 0; i < commentsCount; i++) {
		newData[i] = comments[i];
	}

	delete[] comments;
	comments = newData;
}

CommentsCollection::CommentsCollection()
{
	commentsCount = 0;
	allocatedCellsCount = DEFAULT_ALLOCATED_CELLS;
}

void CommentsCollection::addComment(const Comment& comment)
{
	if (commentsCount >= allocatedCellsCount)
	{
		resize();
	}

	comments[commentsCount] = comment;
	commentsCount++;
}

size_t CommentsCollection::getCommentsCount() const
{
	return commentsCount;
}

void CommentsCollection::printComment(size_t commentIndex) const
{
	std::cout << comments[commentIndex].getContent() << std::endl;
}
