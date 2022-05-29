#include "Line.h"
#include "Rectangle.h"
#include "GlobalConstants.h"
#include "Utils.h"
#include "Serialize.h"
#include <limits>

const MyString typeLine = "line";

Line::Line() :Line(0, 0, 0, 0, DefaultColor) {}

Line::Line(double x1, double y1, double x2, double y2, const MyString& color) : Shape(2, color)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
}
double Line::getArea() const
{
	return 0;
}
double Line::getPer() const
{
	return 0;
}

bool Line::isPointIn(double x, double y) const
{
	Shape::Point p(x, y);
	Shape::Point p0 = getPointAtIndex(0);
	Shape::Point p1 = getPointAtIndex(1);

	return p0.getDist(p) + p1.getDist(p) == p0.getDist(p1);
}

Shape* Line::clone() const
{
	return new Line(*this);
}

void Line::printData() const
{
	std::cout << typeLine << " " << getPointAtIndex(0).x << " " << getPointAtIndex(0).y << " "
		<< getPointAtIndex(1).x << " " << getPointAtIndex(1).y << " " << getColor();
}

void Line::translate(double vertical, double horizontal)
{
	setPoint(0, getPointAtIndex(0).x + horizontal, getPointAtIndex(0).y + vertical);
	setPoint(1, getPointAtIndex(1).x + horizontal, getPointAtIndex(1).y + vertical);
}

MyString Line::getType() const
{
	return typeLine;
}

bool Line::withinRectangle(double x, double y, double width, double height) const
{
	return getPointAtIndex(0).x >= x && getPointAtIndex(1).x <= x + width
		&& getPointAtIndex(0).y <= y && getPointAtIndex(1).y >= y - height;
}

bool Line::withinCircle(double x, double y, double radius) const
{
	Shape::Point p(x, y);
	Shape::Point p0 = getPointAtIndex(0);
	Shape::Point p1 = getPointAtIndex(1);

	return p0.getDist(p) <= radius && p1.getDist(p) <= radius;
}

void Line::loadShape(const MyString& line, size_t& lineSize, size_t& currentIndex)
{
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	MyString color = "";
	
	readLine(line,lineSize,currentIndex, x1, y1, x2, y2, color);

	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
	setColor(color);
}

void Line::saveShape(std::ofstream& file)
{
	Shape::Point p1 = getPointAtIndex(0);
	Shape::Point p2 = getPointAtIndex(1);
	
	saveLine(file, p1.x, p1.y, p2.x, p2.y, getColor());
}
