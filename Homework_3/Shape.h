#pragma once
#include <iostream>

class Shape   // Abstract class - no instances of Shape are allowed!
{
protected:
	struct Point
	{
		Point() :x(0), y(0) {}
		Point(int x, int y) :x(x), y(y) {}
		int x;
		int y;
		double getDist(const Point& other) const
		{
			int dx = x - other.x;
			int dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}
	};
	const Point& getPointAtIndex(size_t index) const;
private:
	Point* points;
	size_t pointsCount;

	void copyFrom(const Shape& other);
	void free();


public:
	Shape(size_t pointsCount);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape(); //!!!!!!

	void setPoint(size_t pointIndex, int x, int y);

	virtual double getArea() const = 0;
	virtual double getPer()  const = 0;
	virtual bool isPointIn(int x, int y) const = 0;
	virtual Shape* clone() const = 0;

};