#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
	double width;
	double height;
public:
	Rectangle();
	Rectangle(double x, double y, double width, double height, const MyString& color);
	void setWidth(double width);
	void setHeight(double height);
	
	double getWidth() const;
	double getHeight() const;
	double getArea() const override;
	double getPer() const override;
	MyString getType() const override;

	Shape* clone() const override;
	
	void translate(double vertical, double horizontal) override;

	bool withinRectangle(double x, double y, double width, double heigth) const override;
	bool withinCircle(double x, double y, double radius) const override;
	bool isPointIn(double x, double y) const override;
	
	void loadShape(const MyString& line, size_t& lineSize, size_t& currentIndex) override;
	void saveShape(std::ofstream& file) override;


	void printData() const override;
};