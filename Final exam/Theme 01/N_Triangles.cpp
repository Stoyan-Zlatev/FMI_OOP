#include <iostream>
#include <cmath>

struct Point
{
	double x;
	double y;
};

void readPoint(Point& p)
{
	std::cin >> p.x >> p.y;
}

void printPoint(const Point& p)
{
	std::cout << p.x << " "<<p.y;
}

double getDistance(const Point& p1, const Point& p2)
{
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;

	return sqrt(dx * dx + dy * dy);
}

struct Triangle
{
	Point p1;
	Point p2;
	Point p3;
};

void readTriangle(Triangle& triangle)
{
	readPoint(triangle.p1);
	readPoint(triangle.p2);
	readPoint(triangle.p3);
}

void printTriangle(const Triangle& triangle)
{
	printPoint(triangle.p1);
	std::cout << " ";
	printPoint(triangle.p2);
	std::cout << " ";
	printPoint(triangle.p3);
	std::cout << std::endl;
}

double getArea(const Triangle& triangle)
{
	double sideA = getDistance(triangle.p1, triangle.p2);
	double sideB = getDistance(triangle.p1, triangle.p3);
	double sideC = getDistance(triangle.p2, triangle.p3);

	double halfPer = (sideA + sideB + sideC) / 2.0;

	return sqrt(halfPer * (halfPer - sideA) * (halfPer - sideB) * (halfPer - sideC));
}

void swap(double& first, double& second)
{
	double temp = first;
	first = second;
	second = temp;
}

void swap(Triangle& first, Triangle& second)
{
	Triangle temp = first;
	first = second;
	second = temp;
}

void selectionSort(double* areas, Triangle* triangles, size_t n)
{
	for (size_t i = 0; i < n-1; i++)
	{
		size_t minIndex = i;
		for (size_t j = i + 1; j < n; j++)
		{
			if (areas[j] < areas[minIndex])
				minIndex = j;
		}
		if (minIndex != i)
		{
			swap(areas[i], areas[minIndex]);
			swap(triangles[i], triangles[minIndex]);
		}
	}
}

double* calculateAreas(const Triangle* triangles, size_t n)
{
	double* areas = new double[n];

	for (size_t i = 0; i < n; i++)
	{
		areas[i] = getArea(triangles[i]);
	}

	return areas;
}

int main()
{
	size_t n;
	std::cin >> n;

	Triangle* triangles = new Triangle[n];

	for (size_t i = 0; i < n; i++)
		readTriangle(triangles[i]);

	double* areas = calculateAreas(triangles, n);

	for (size_t i = 0; i < n; i++)
		printTriangle(triangles[i]);
}
