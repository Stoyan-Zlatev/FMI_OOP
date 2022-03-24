#include <iostream>

using namespace std;

bool isPrime(size_t currentNumber)
{
	size_t maxPrimeBorder = sqrt(currentNumber);
	for (size_t j = 2; j <= maxPrimeBorder; j++)
	{
		if (currentNumber % j == 0)
			return false;
	}
	return true;
}

size_t getNumberLength(int number)
{
	size_t counter = 0;
	while (number != 0)
	{
		number /= 10;
		counter++;
	}

	return counter;
}

size_t absNumber(int number)
{
	return number >= 0 ? number : (-number);
}

size_t powTen(size_t power)
{
	size_t powerTen = 1;
	for (size_t i = 1; i < power; i++)
	{
		powerTen *= 10;
	}
	return powerTen;
}

bool hasUniqueDigits(size_t number)
{
	const int digitsCount = 10;
	bool hash[digitsCount] = {};
	if (number > 10)
	{
		while (number != 0)
		{
			size_t lastDigit = number % 10;
			if (hash[lastDigit])
				return false;
			hash[lastDigit]++;
			number /= 10;
		}
	}
	return true;
}

bool isPalindrome(size_t number)
{
	const int minNumberLength = 2;
	size_t numberLength = getNumberLength(number);
	size_t powerTen = powTen(numberLength);
	size_t halfLength = numberLength / 2;
	for (size_t i = 0; i < halfLength; i++)
	{
		if ((number % 10) != ((number / powerTen) % 10))
			return false;
		powerTen /= 10;
	}
	return numberLength >= minNumberLength;
}

class Interval
{
	int a;
	int b;
public:
	Interval();
	Interval(int a, int b);

	size_t calcInvervalLength() const;
	size_t calcPrimeNumbersInTheInterval() const;
	size_t countPalindromes() const;
	size_t countNonRepeatingDigitNumbers() const;
	size_t countNumbers(bool (*func)(size_t)) const;

	int getLeftBorder() const;
	int getRightBorder() const;

	bool areBordersPowerOfTwo() const;
	bool isSuperInterval(const Interval& otherInterval) const;
	bool isInInterval(int number) const;
	bool containsInterval(const Interval& otherInterval) const;

	Interval intersect(const Interval& otherInterval) const;
	Interval unionInterval(const Interval& otherInterval) const;

	void setInterval(int a, int b);
	void setLeftBorder(int a);
	void setRightBorder(int b);

};

Interval::Interval() : Interval(0, 0) { }

Interval::Interval(int a, int b)
{
	setInterval(a, b);
}

int Interval::getLeftBorder() const
{
	return a;
}

int Interval::getRightBorder() const
{
	return b;
}

void Interval::setInterval(int a, int b)
{
	if (a <= b)
	{
		this->a = a;
		this->b = b;
	}
	else
	{
		this->a = this->b = 0;
	}
}

void Interval::setRightBorder(int b)
{
	if (a <= b)
	{
		this->b = b;
	}
	else
	{
		this->a = this->b = 0;
	}
}

void Interval::setLeftBorder(int a)
{
	if (a <= b)
	{
		this->a = a;
	}
	else
	{
		this->a = this->b = 0;
	}
}

size_t Interval::calcInvervalLength() const
{
	return absNumber(getRightBorder() - getLeftBorder());
}

size_t Interval::countNumbers(bool (*func)(size_t)) const
{
	size_t counter = 0;
	for (int i = a; i <= b; i++)
	{
		if (func(absNumber(i)))
			counter++;
	}
	return counter;
}

size_t Interval::calcPrimeNumbersInTheInterval() const
{
	return countNumbers(isPrime);
}

size_t Interval::countPalindromes() const
{
	return countNumbers(isPalindrome);
}

size_t Interval::countNonRepeatingDigitNumbers() const
{
	return countNumbers(hasUniqueDigits);
}

bool Interval::isInInterval(int number) const
{
	return (number <= getRightBorder()) && (number >= getLeftBorder());
}

bool Interval::areBordersPowerOfTwo() const
{
	if (a <= 0 || b <= 0)
		return false;
	return (a > 0 && (a & (a - 1)) == 0) && (b > 0 && (b & (b - 1)) == 0);
}

bool Interval::isSuperInterval(const Interval& otherInterval) const
{
	return (a <= otherInterval.a) && (b >= otherInterval.b);
}

Interval Interval::intersect(const Interval& otherInterval) const
{
	int leftBorder = (a > otherInterval.a) ? a : otherInterval.a;
	int rightBorder = (b < otherInterval.b) ? b : otherInterval.b;
	Interval result(leftBorder, rightBorder);
	return result;
}

Interval Interval::unionInterval(const Interval& otherInterval) const
{
	int leftBorder = (a < otherInterval.a) ? a : otherInterval.a;
	int rightBorder = (b > otherInterval.b) ? b : otherInterval.b;
	Interval result(leftBorder, rightBorder);
	return result;
}

bool Interval::containsInterval(const Interval& otherInterval) const
{
	return isInInterval(otherInterval.getLeftBorder()) && isInInterval(otherInterval.getRightBorder());
}

int main()
{
	Interval t1(3, 10); // [3, 10]
	Interval t2(4, 14); // [4, 14]
	Interval t3(1, 130); // [1, 130]
	Interval t4(2, 32); // [2, 2^5]

	Interval result = t1.intersect(t2); // [4, 10]
	std::cout << t1.calcInvervalLength() << std::endl;
	std::cout << t2.calcPrimeNumbersInTheInterval() << std::endl; //4 (5,7,11,13)
	std::cout << t3.countPalindromes() << std::endl; //12 (11 22 33 44 55 66 77 88 99 101 111 121)
	std::cout << t3.countNonRepeatingDigitNumbers() << std::endl; //107
	std::cout << std::boolalpha << t2.areBordersPowerOfTwo() << std::endl;//[4,14] false
	std::cout << std::boolalpha << t4.areBordersPowerOfTwo() << std::endl;//[2,32] true
	std::cout << std::boolalpha << t2.isSuperInterval(result) << std::endl; //true
	std::cout << std::boolalpha << t2.isInInterval(7) << std::endl; //true
	std::cout << result.calcPrimeNumbersInTheInterval() << std::endl; // 2 (only 5 and 7)
}
