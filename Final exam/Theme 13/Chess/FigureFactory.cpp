#include "FigureFactory.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"



Figure* FigureFactory::createFigure(bool isWhite, FigureType type)
{
	switch (type)
	{
	case FigureType::BishopFigure: return new Bishop(isWhite);
	case FigureType::QueenFigure: return new Queen(isWhite);
	case FigureType::RookFigure: return new Rook(isWhite);
	}
}