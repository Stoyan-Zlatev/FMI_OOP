#pragma once
#include "Comment.h"

class CommentsCollection
{
	size_t commentsCount;
	size_t allocatedCellsCount;
	Comment* comments;
	void copyFrom(const CommentsCollection& other);
	void free();
	void resize();
public:
	CommentsCollection();
	void addComment(const Comment& comment);

	size_t getCommentsCount() const;
	void printComment(size_t commentIndex) const;
};