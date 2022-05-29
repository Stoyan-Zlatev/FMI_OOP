#pragma once
#include <iostream>
#include "MyString.h"

class Shape
{
protected:
	struct Point
	{
		Point() :x(0), y(0) {}
		Point(double x, double y) :x(x), y(y) {}
		double x;
		double y;
		double getDist(const Point& other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}
	};
	const Point& getPointAtIndex(size_t index) const;
private:
	Point* points;
	size_t pointsCount;
	MyString color;

	void copyFrom(const Shape& other);
	void free();


public:
	Shape(size_t pointsCount, const MyString& color);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape();

	void setPoint(size_t pointIndex, double x, double y);
	void setColor(const MyString& color);

	virtual void translate(double vertical, double horizontal) = 0;

	MyString getColor() const;
	virtual MyString getType() const = 0;
	virtual double getArea() const = 0;
	virtual double getPer()  const = 0;
	virtual Shape* clone() const = 0;
	
	virtual void print() const;
	virtual void printData() const = 0;
	virtual void printArea() const;
	virtual void printPerimeter() const;
	
	virtual bool withinRectangle(double x, double y, double height, double width) const = 0;
	virtual bool withinCircle(double x, double y, double radius) const = 0;
	virtual bool isPointIn(double x, double y) const = 0;
	
	virtual void loadShape(const MyString& line, size_t& lineSize, size_t& currentIndex) = 0;
	virtual void saveShape(std::ofstream& file) = 0;
};