#include "Circle.h"
#include "Rectangle.h"
#include "GlobalConstants.h"
#include "Utils.h"
#include "Serialize.h"

const double PI = 3.1415;

void Circle::setRadius(double radius)
{
	this->radius = radius;
}

Circle::Circle() : Circle(0, 0, 0, DefaultColor) {}

Circle::Circle(double cx, double cy, double radius, const MyString& color) : Shape(1, color), radius(radius)
{
	setPoint(0, cx, cy);
}

double Circle::getArea() const
{
	return PI * radius * radius;
}
double Circle::getPer() const
{
	return 2 * PI * radius;
}
bool Circle::isPointIn(double cx, double cy) const
{
	Shape::Point p(cx, cy);

	return p.getDist(getPointAtIndex(0)) <= radius;
}
Shape* Circle::clone() const
{
	return new Circle(*this);
}

void Circle::printData() const
{
	Shape::Point center(getPointAtIndex(0));
	std::cout << typeCircle << " " << center.x << " " << center.y << " " << radius << " " << getColor();
}

void Circle::translate(double vertical, double horizontal)
{
	Shape::Point center(getPointAtIndex(0));
	setPoint(0, center.x + horizontal, center.y + vertical);
}

MyString Circle::getType() const
{
	return typeCircle;
}

bool Circle::withinRectangle(double x, double y, double width, double height) const
{
	Shape::Point center = getPointAtIndex(0);

	return center.x + radius <= x + width && center.x - radius >= x &&
		center.y + radius <= y&& center.y - radius >= y - height;
}

bool Circle::withinCircle(double x, double y, double radius) const
{
	Shape::Point otherCenter(x, y);
	double distance = otherCenter.getDist(getPointAtIndex(0));

	return radius >= (distance + this->radius);
}

void Circle::loadShape(const MyString& line, size_t& lineSize, size_t& currentIndex)
{
	double x = 0, y = 0, radius = 0;
	MyString color = "";

	readCircle(line, lineSize, currentIndex, x, y, radius, color);

	setPoint(0, x, y);
	setRadius(radius);
	setColor(color);
}

void Circle::saveShape(std::ofstream& file)
{
	Shape::Point center = getPointAtIndex(0);
	saveCircle(file, center.x, center.y, radius, getColor());
}

