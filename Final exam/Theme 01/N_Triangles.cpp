#include <iostream>

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
	std::cout << p.x << " " << p.y;
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

void readTriangle(Triangle& t)
{
	readPoint(t.p1);
	readPoint(t.p2);
	readPoint(t.p3);
}

void printTriangle(const Triangle& t)
{
	printPoint(t.p1);
	std::cout << " ";
	printPoint(t.p2);
	std::cout << " ";
	printPoint(t.p3);
	std::cout << std::endl;
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
		for (size_t j = i+1; j < n; j++)
		{
			if (areas[minIndex] < areas[j])
				minIndex = j;
		}
		if (minIndex != i)
		{
			swap(areas[i], areas[minIndex]);
			swap(triangles[i], triangles[minIndex]);
		}
	}
}

double getArea(const Triangle& t)
{
	double sideA = getDistance(t.p1, t.p2);
	double sideB = getDistance(t.p1, t.p3);
	double sideC = getDistance(t.p2, t.p3);

	double halfPer = (sideA + sideB + sideC) / 2.0;

	return sqrt(halfPer * (halfPer - sideA) * (halfPer - sideB) * (halfPer - sideC));
}

double* calculateAreas(const Triangle* triangles, size_t n)
{
	double* areas = new double[n];

	for (size_t i = 0; i < n; i++)
		areas[i] = getArea(triangles[i]);

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

	delete[] areas, triangles;
	return 0;
}
