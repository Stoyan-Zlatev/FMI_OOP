#include <iostream>
#include "Pair.h"

int main()
{
	Pair<int, char> p(3, 'd');

	std::cout << p.getSecond();

	p.setSecond('a');

}
