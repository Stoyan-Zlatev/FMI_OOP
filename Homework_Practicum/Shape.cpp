#include "Shape.h"
#include "GlobalConstants.h"

Shape::Shape(size_t pointsCount, const MyString& color) : pointsCount(pointsCount)
{
	points = new Point[pointsCount];
	setColor(color);
}

void Shape::copyFrom(const Shape& other)
{
	points = new Point[other.pointsCount];

	for (size_t i = 0; i < other.pointsCount; i++)
		points[i] = other.points[i];

	pointsCount = other.pointsCount;
	color = other.color;
}
void Shape::free()
{
	delete[] points;
}

Shape::Shape(const Shape& other)
{
	copyFrom(other);
}
Shape& Shape::operator=(const Shape& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
Shape::~Shape()
{
	free();
}

const Shape::Point& Shape::getPointAtIndex(size_t pointIndex) const
{
	if (pointIndex >= pointsCount)
	{
		throw std::exception("Invalid point index!\n");
	}

	return  points[pointIndex];
}

void Shape::setPoint(size_t pointIndex, double x, double y)
{
	if (pointIndex >= pointsCount)
	{
		throw std::exception("Invalid point index!\n");
	}

	points[pointIndex] = Point(x, y);
}

void Shape::setColor(const MyString& color)
{
	if (color.getSize() >= MaxContentLength)
	{
		throw std::invalid_argument("Entered color is too long!\n");
	}

	this->color = color;
}

MyString Shape::getColor() const
{
	return color;
}

void Shape::print() const
{
	printData();
	std::cout << std::endl;
}

void Shape::printArea() const
{
	printData();
	std::cout << " " << std::endl << "Area: " << getArea() << std::endl;
}

void Shape::printPerimeter() const
{
	printData();
	std::cout << " " << std::endl << "Perimeter: " << getPer() << std::endl;
}
