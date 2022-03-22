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
		counter /= 10;
		counter++;
	}

	return counter;
}

bool isPalindrome(int number)
{
	//think about negative numbers, don't forget numbers starting with 0!
}

class Interval
{
	int a;
	int b;
public:
	Interval();
	Interval(int a, int b);

	size_t getInvervalLength() const;
	size_t calcPrimeNumbersInTheInterval() const;

	void setBorders(int a, int b);

	bool contains(int number) const;
};

Interval::Interval() : Interval(0, 0) { }

Interval::Interval(int a, int b)
{
	setBorders(a, b);
}

void Interval::setBorders(int a, int b)
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

size_t Interval::getInvervalLength() const
{
	return this->b - this->a;
}

size_t Interval::calcPrimeNumbersInTheInterval() const
{
	size_t counter = 0;
	if (b > 2)
	{
		int leftBorder = a < 2 ? 2 : a;
		for (size_t i = leftBorder; i <= b; i++)
		{
			if (isPrime(i))
			{
				std::cout << i << " ";
				counter++;
			}
		}
	}
	return counter;
}

bool Interval::contains(int number) const
{
	return number <= this->b && number >= this->a;
}

int main()
{
	Interval t1(3, 10); // [3, 10]
	Interval t2(2, 14); // [4, 14]
	Interval t3; // [0, 0]

	//Interval result = t1.intersect(t2); // [4, 10]

	//t2.isSuperInterval(result); //true

	std::cout << t2.calcPrimeNumbersInTheInterval(); // 2 (only 5 and 7)
}