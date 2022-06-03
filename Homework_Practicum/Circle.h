#pragma once
#include "Shape.h"

class Circle : public Shape
{
	double radius;
	void setRadius(double radius);
public:
	Circle();
	Circle(double x, double y, double radius, const MyString& color);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
	void printData() const override;
	void translate(double vertical, double horizontal) override;
	MyString getType() const override;
	bool withinRectangle(double x, double y, double width, double heigth) const override;
	bool withinCircle(double x, double y, double radius) const override;
	void loadShape(const MyString& line, size_t& lineSize, size_t& currentIndex) override;
	void saveShape(std::ofstream& file) override;
};