#include "ChessBoard.h"
#include "FigureFactory.h"

ChessBoard::ChessBoard()
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		board[1][i].f = FigureFactory::createFigure(false, FigureType::RookFigure);
	}
	//todo
}

void ChessBoard::print() const
{
	std::cout << "--------";
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j].print();
		}
		std::cout << std::endl;
	}
	std::cout << "--------"<<std::endl;
}

void ChessBoard::moveFigure(size_t x, size_t y, size_t destX, size_t destY)
{
	if (board[x][y].f->getType() != QueenFigure && board[x][y].f->getType() != RookFigure && board[x][y].f->getType() != BishopFigure)
	{
		//something else
	}
	else
	{
		if (board[x][y].f && board[x][y].f->canBeMoved(x, y, destX, destY))
		{
			delete board[destX][destY].f;
			board[destX][destY].f = board[x][y].f;
			board[x][y].f = nullptr;
		}
	}
}
