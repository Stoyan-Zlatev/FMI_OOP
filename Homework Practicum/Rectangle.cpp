#include "Rectangle.h"
#include "GlobalConstants.h"
#include "Utils.h"
#include "Serialize.h"

Rectangle::Rectangle() :Rectangle(0, 0, 0, 0, DefaultColor) {}

Rectangle::Rectangle(double x, double y, double width, double height, const MyString& color) : Shape(4, color)
{
	setHeight(height);
	setWidth(width);

	//It is top left rectangle point
	setPoint(0, x, y);
	setPoint(1, x, (y - height));
	setPoint(2, (x + width), (y - height));
	setPoint(3, (x + width), y);
}
void Rectangle::setWidth(double width)
{
	if (width < 0)
	{
		throw std::invalid_argument("Width cannot be negative number!\n");
	}

	this->width = width;
}
void Rectangle::setHeight(double height)
{
	if (height < 0)
	{
		throw std::invalid_argument("Height cannot be negative number!\n");
	}

	this->height = height;
}
double Rectangle::getWidth() const
{
	return width;
}
double Rectangle::getHeight() const
{
	return height;
}
double Rectangle::getArea() const
{
	Shape::Point p0 = getPointAtIndex(0);
	Shape::Point p1 = getPointAtIndex(1);
	Shape::Point p3 = getPointAtIndex(3);

	return p0.getDist(p1) * p0.getDist(p3);

}
double Rectangle::getPer() const
{
	Shape::Point p0 = getPointAtIndex(0);
	Shape::Point p1 = getPointAtIndex(1);
	Shape::Point p3 = getPointAtIndex(3);

	return 2 * (p0.getDist(p1) + p0.getDist(p3));
}

bool Rectangle::isPointIn(double x, double y) const
{
	Shape::Point p(x, y);
	Shape::Point p0 = getPointAtIndex(0);
	Shape::Point p2 = getPointAtIndex(2);

	return p.x >= p0.x && p.y >= p2.y &&
		p.y <= p0.y && p.x <= p2.x;
}
Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}

void Rectangle::printData() const
{
	Shape::Point p0 = getPointAtIndex(0);
	
	std::cout << typeRectangle << " " << p0.x << " " << p0.y << " "
		<< width << " " << height << " " << getColor();
}

void Rectangle::translate(double vertical, double horizontal)
{
	Shape::Point p0 = getPointAtIndex(0);
	Shape::Point p1 = getPointAtIndex(1);
	Shape::Point p2 = getPointAtIndex(2);
	Shape::Point p3 = getPointAtIndex(3);
	
	setPoint(0, p0.x + horizontal, p0.y + vertical);
	setPoint(1, p1.x + horizontal, p1.y + vertical);
	setPoint(2, p2.x + horizontal, p2.y + vertical);
	setPoint(3, p3.x + horizontal, p3.y + vertical);
}

MyString Rectangle::getType() const
{
	return typeRectangle;
}

bool Rectangle::withinRectangle(double x, double y, double width, double height) const
{
	Shape::Point p0 = getPointAtIndex(0);
	Shape::Point p2 = getPointAtIndex(2);

	return p0.x >= x && p2.x <= x + width
		&& p0.y <= y && p2.y >= y - height;
}

bool Rectangle::withinCircle(double x, double y, double radius) const
{
	Shape::Point p(x, y);
	Shape::Point p0 = getPointAtIndex(0);
	Shape::Point p2 = getPointAtIndex(2);
	//p0p2 line is the rectangle diagonal

	return p0.getDist(p) <= radius && p2.getDist(p) <= radius;
}

void Rectangle::loadShape(const MyString& line, size_t& lineSize, size_t& currentIndex)
{
	double x = 0, y = 0, width = 0, height = 0;
	MyString color = "";

	readRectangle(line, lineSize, currentIndex, x, y, width, height, color);

	setPoint(0, x, y);
	setPoint(1, x, (y - height));
	setPoint(2, (x + width), (y - height));
	setPoint(3, (x + width), y);
	setWidth(width);
	setHeight(height);
	setColor(color);
}

void Rectangle::saveShape(std::ofstream& file)
{
	Shape::Point p = getPointAtIndex(0);
	saveRectangle(file, p.x, p.y, width, height, getColor());
}
