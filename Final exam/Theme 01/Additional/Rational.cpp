#include <iostream>
#include <cmath>

struct Rational
{
	int ch;
	int zn;
};

bool isValidRationalNumber(const Rational& number)
{
	if (number.zn != 0)
		return true;
	return false;
}

bool isInteger(const Rational& number)
{

	if (isValidRationalNumber(number) && number.ch % number.zn == 0)
		return true;
	return false;
}

void printRationalNumber(const Rational& number)
{
	if (isInteger(number))
		std::cout << (number.ch / number.zn);
	else
		std::cout << number.ch << "/" << number.zn << std::endl;
}

int еuclidRemainder(int a, int b) {
	return b == 0 ? a : еuclidRemainder(b, a % b);
}

int nok(int a, int b)
{
	return a * (b / еuclidRemainder(a, b));
}

Rational sum(const Rational& number1, const Rational& numebr2)
{
	Rational result;
	if (number1.zn != numebr2.zn)
	{
		int nokZn = nok(number1.zn, numebr2.zn);
		result.ch = number1.ch * (nokZn / number1.zn) + numebr2.ch * (nokZn / numebr2.zn);
		result.zn = nokZn;
	}
	else
	{
		result.ch = number1.ch + numebr2.ch;
		result.zn = number1.zn;
	}

	return result;
}

Rational diff(const Rational& number1, const Rational& numebr2)
{
	Rational result;
	if (number1.zn != numebr2.zn)
	{
		int nokZn = nok(number1.zn, numebr2.zn);
		result.ch = number1.ch * (nokZn / number1.zn) - numebr2.ch * (nokZn / numebr2.zn);
		result.zn = nokZn;
	}
	else
	{
		result.ch = number1.ch - numebr2.ch;
		result.zn = number1.zn;
	}

	return result;
}

Rational mult(const Rational& number1, const Rational& numebr2)
{
	Rational result;
	result.ch = number1.ch * numebr2.ch;
	result.zn = number1.zn * numebr2.zn;

	return result;
}

Rational div(const Rational& number1, const Rational& numebr2)
{
	Rational result;
	result.ch = number1.ch * numebr2.zn;
	result.zn = number1.zn * numebr2.ch;

	return result;
}

int main()
{
	Rational r{ 5, 7 };
	Rational r1{ 8, 6 };

	printRationalNumber(sum(r, r1));
	printRationalNumber(diff(r, r1));
	printRationalNumber(mult(r, r1));
	printRationalNumber(div(r, r1));

	std::cout << isInteger(r) << std::endl;
	std::cout << isValidRationalNumber(r) << std::endl;
}
