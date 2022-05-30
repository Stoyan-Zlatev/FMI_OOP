#pragma once
#include "Shape.h"
#include "Collection.hpp"
#include "MyString.h"

class ShapeCollection
{
	Shape** data;
	size_t count;
	size_t capacity;

	void free();
	void copyFrom(const ShapeCollection& other);
	void resize();

	void addShape(Shape* shape);

public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();

	void addRectangle(double x1, double y1, double width, double height, const MyString& color);
	void addCircle(double x1, double y1, int radius, const MyString& color);
	void addLine(double x1, double y1, double x2, double y2, const MyString& color);

	bool eraseFigure(size_t index, MyString& shapeType);
	void translate(double vertical, double horizontal);
	void translate(double vertical, double horizontal, size_t index, MyString& shapeType);

	void withinRectangle(double x, double y, double width, double heigth) const;
	void withinCircle(double cx, double cy, double radius) const;
	void pointIn(double x, double y) const;

	double getPerOfFigureByIndex(size_t ind) const;
	double getAreaOfFigureByIndex(size_t ind) const;
	double getIfPointInShapeByIndex(size_t ind, double x, double y) const;
	size_t getShapesCount() const;

	void printShapes() const;
	void printAreas() const;
	void printPerimteres() const;

	void load(std::ifstream& sourceFile);
	void saveToFile(const MyString& path,const Collection<MyString>& headers);
};