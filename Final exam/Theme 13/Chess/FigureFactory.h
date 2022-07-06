#pragma once
#include "FigureBase.h"
#include "FigureType.h""

class FigureFactory
{
public:
	static Figure* createFigure(bool isWhite, FigureType); //enum
};