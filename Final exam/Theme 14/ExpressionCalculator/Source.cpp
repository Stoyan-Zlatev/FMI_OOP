#include "ExpressionCalculator.h"
#include <iostream>

int main()
{
	ExpressionCalculator ex("(Av(B^P))");
	std::cout<<ex.isContradiction()<<std::endl;
	std::cout << ex.isTautology() << std::endl;
}