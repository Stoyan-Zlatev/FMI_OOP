#include "ShapeCollection.h"
#include <stdexcept>
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "MyString.h"
#include "GlobalConstants.h"
#include "Utils.h"
#include "Serialize.h"

void ShapeCollection::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete data[i];
	}

	delete[] data;
}
void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	data = new Shape * [other.count];
	count = other.count;
	capacity = other.capacity;

	for (size_t i = 0; i < count; i++)
	{
		data[i] = other.data[i]->clone();
	}
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];
	for (size_t i = 0; i < count; i++)
	{
		newCollection[i] = data[i];
	}

	delete[] data;
	data = newCollection;
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	count = 0;
	data = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}
ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::addShape(Shape* shape)
{
	if (count == capacity)
	{
		resize();
	}

	data[count++] = shape;
}

void ShapeCollection::addRectangle(double x1, double y1, double width, double height, const MyString& color)
{
	Rectangle* rect = new Rectangle(x1, y1, width, height, color);
	addShape(rect);
}
void ShapeCollection::addCircle(double x1, double y1, int radius, const MyString& color)
{
	Circle* circlce = new Circle(x1, y1, radius, color);
	addShape(circlce);
}

void ShapeCollection::addLine(double x1, double y1, double x2, double y2, const MyString& color)
{
	Line* line = new Line(x1, y1, x2, y2, color);
	addShape(line);
}

void ShapeCollection::eraseFigure(size_t index, MyString& shapeType)
{
	if (index >= count)
	{
		throw std::invalid_argument("This figure does not exist!\n");
	}

	--count;

	shapeType = data[index]->getType();
	delete data[index];

	for (size_t i = index; i < count; i++)
	{
		data[index] = data[index + 1];
	}
}

void ShapeCollection::translate(double vertical, double horizontal)
{
	for (size_t i = 0; i < count; i++)
	{
		data[i]->translate(vertical, horizontal);
	}
}

void ShapeCollection::translate(double vertical, double horizontal, size_t index, MyString& shapeType)
{
	if (index > count)
	{
		throw std::out_of_range("This figure does not exist!\n");
	}

	data[index]->translate(vertical, horizontal);
	shapeType = data[index]->getType();
}

void ShapeCollection::withinRectangle(double x, double y, double width, double height) const
{
	bool containsFigures = false;
	for (size_t i = 0; i < count; i++)
	{
		if (data[i]->withinRectangle(x, y, width, height))
		{
			data[i]->print();
			containsFigures = true;
		}
	}

	if (!containsFigures)
	{
		std::cout << "No figures are located within rectangle " << x << " " << y << " " << width << " " << height << std::endl;
	}
}

void ShapeCollection::withinCircle(double cx, double cy, double radius) const
{
	bool containsFigures = false;
	for (size_t i = 0; i < count; i++)
	{
		if (data[i]->withinCircle(cx, cy, radius))
		{
			data[i]->print();
			containsFigures = true;
		}
	}

	if (!containsFigures)
	{
		std::cout << "No figures are located within circle " << cx << " " << cy << " " << radius << std::endl;
	}
}

void ShapeCollection::pointIn(double x, double y) const
{
	bool containsFigures = false;
	for (size_t i = 0; i < count; i++)
	{
		if (data[i]->isPointIn(x, y))
		{
			data[i]->print();
			containsFigures = true;
		}
	}

	if (!containsFigures)
	{
		std::cout << "No figures contain point " << x << " " << y << std::endl;
	}
}

double ShapeCollection::getPerOfFigureByIndex(size_t ind) const
{
	if (ind >= count)
	{
		throw std::out_of_range("Out of range in shapes collection!\n");
	}

	return data[ind]->getPer();
}

double ShapeCollection::getAreaOfFigureByIndex(size_t ind) const
{
	if (ind >= count)
	{
		throw std::out_of_range("Out of range in shapes collection!\n");
	}

	return data[ind]->getArea();
}

double ShapeCollection::getIfPointInShapeByIndex(size_t ind, double x, double y) const
{
	if (ind >= count)
	{
		throw std::out_of_range("Out of range in shapes collection!\n");
	}

	return data[ind]->isPointIn(x, y);
}

size_t ShapeCollection::getShapesCount() const
{
	return count;
}

void ShapeCollection::printShapes() const
{
	if (count == 0)
	{
		throw std::exception("There are no shapes in the list yet!\n");
	}

	for (size_t i = 0; i < count; i++)
	{
		std::cout << (i + 1) << ". ";
		data[i]->print();
	}
}

void ShapeCollection::printAreas() const
{
	if (count == 0)
	{
		throw std::exception("There are no shapes in the list yet!\n");
	}

	for (size_t i = 0; i < count; i++)
	{
		data[i]->printArea();
	}
}

void ShapeCollection::printPerimteres() const
{
	if (count == 0)
	{
		throw std::exception("There are no shapes in the list yet!\n");
	}

	for (size_t i = 0; i < count; i++)
	{
		data[i]->printPerimeter();
	}
}


void ShapeCollection::load(std::ifstream& sourceFile)
{
	MyString line;
	Shape* shape = nullptr;

	//Found open tag <svg>
	while (true)
	{
		line.getline(sourceFile);
		if (line == SvgCloseTag)
		{
			break;
		}

		MyString shapeType = "";
		size_t currentIndex = 0, lineSize = strlen(line.c_str());
		getShapeType(line, shapeType, lineSize, currentIndex);
		if (shapeType == "rect")
		{
			shape = new Rectangle();
		}
		else if (shapeType == "circle")
		{
			shape = new Circle();
		}
		else if (shapeType == "line")
		{
			shape = new Line();
		}

		shape->loadShape(line, lineSize, currentIndex);
		addShape(shape);
	}
}

void ShapeCollection::saveToFile(const MyString& path, const Collection<MyString>& headers)
{
	std::ofstream file(path.c_str());

	saveHeaders(file, headers);

	file << "<svg>\n";

	for (size_t i = 0; i < count; i++)
	{
		data[i]->saveShape(file);
	}

	file << "</svg>";

	file.close();
}