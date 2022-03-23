#include <iostream>

bool isPrime(int currentNumber)
{
	int maxPrimeBorder = sqrt(currentNumber);
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

size_t asbNumber(int number)
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

bool hasRepeatingDigits(int number)
{
	size_t absNumber = asbNumber(number);
	const int digitsCount = 10;
	int hash[digitsCount] = {};
	if (absNumber > 10)
	{
		while (absNumber != 0)
		{
			int lastDigit = absNumber % 10;
			if (hash[lastDigit] > 0)
				return true;
			hash[lastDigit]++;
			absNumber /= 10;
		}
	}
	return false;
}

bool isPalindrome(int number)
{
	const int minNumberLength = 2;
	int absNumber = asbNumber(number);
	size_t numberLength = getNumberLength(absNumber);
	size_t powerTen = powTen(numberLength);
	size_t halfLength = numberLength / 2;
	for (size_t i = 0; i < halfLength; i++)
	{
		if ((absNumber % 10) != ((absNumber / powerTen) % 10))
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

	bool areBordersPowerOfTwo() const;
	bool isSuperInterval(const Interval& otherInterval) const;
	bool isInInterval(int number) const;

	Interval intersect(const Interval& otherInterval) const;

	void setInterval(int a, int b);

};

Interval::Interval() : Interval(0, 0) { }

Interval::Interval(int a, int b)
{
	setInterval(a, b);
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

size_t Interval::calcInvervalLength() const
{
	return this->b - this->a;
}

size_t Interval::calcPrimeNumbersInTheInterval() const
{
	size_t counter = 0;
	if (b > 2)
	{
		//2 is the first prime number
		int leftBorder = a < 2 ? 2 : a;
		for (size_t i = leftBorder; i <= b; i++)
		{
			if (isPrime(i))
			{
				counter++;
			}
		}
	}
	return counter;
}

bool Interval::isInInterval(int number) const
{
	return (number <= b) && (number >= a);
}

size_t Interval::countPalindromes() const
{
	size_t counter = 0;
	for (int i = a; i <= b; i++)
	{
		if (isPalindrome(i))
			counter++;
	}
	return counter;
}

size_t Interval::countNonRepeatingDigitNumbers() const
{
	size_t counter = 0;
	for (size_t i = a; i <= b; i++)
	{
		if (!hasRepeatingDigits(i))
			counter++;
	}

	return counter;
}

bool Interval::areBordersPowerOfTwo() const
{
	if (a <= 0 || b <= 0)
		return false;
	return ((a & (a - 1)) == 0) && ((b & (b - 1)) == 0);
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
