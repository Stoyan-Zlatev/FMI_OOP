#pragma once
#include "Bishop.h"
#include "Rook.h"

class Queen : public Rook, public Bishop
{
public:
	Queen(bool isWhite);
	bool canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const;
	void print() const;
};