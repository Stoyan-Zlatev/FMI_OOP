#include <iostream>
#include <exception>
#include "MyString.h"
#include "SetCalculator.h"

int main()
{
	//v - union
	//^ - intersection
		// '\' - set minus
		// '!' - complement
		// 'x' - relative complement

	SetCalculator s("(((A^B)vC)vX)");

	SetExpression::Element el;
	el.set('A', true); //element is in set A
	el.set('B', false); // element is NOT in set B
	el.set('C', true); // element is in set C

	std::cout << s.isElementIn(el) << std::endl;

	SetCalculator s1("(A^B)");
	SetCalculator s2("(!((!A)v(!B)))");
	std::cout << (s1 == s2) << std::endl; // true (De morgan laws)
}