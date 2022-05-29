#include <iostream>
#include <fstream>
#include <exception>
#include "ShapeCollection.h"
#include "MyString.h"
#include "Utils.h"

int main()
{
	MyString command = "figures.svg";
	//command.readLine(std::cin);

	ShapeCollection shapes;
	loadFigures(command, shapes);

	std::cout << ">";
	command.getline(std::cin);
	while (true)
	{
		size_t lineSize = strlen(command.c_str());
		size_t currentIndex = 0;
		try
		{
			if (isPrefix(command, "exit"))
			{

			}
			else if (isPrefix(command, "create"))
			{
				MyString shapeType, color;
				double x, y, field3, field4;
				getArgument(command, lineSize, currentIndex, shapeType);
				getArgument(command, lineSize, currentIndex, x);
				getArgument(command, lineSize, currentIndex, y); 
				getArgument(command, lineSize, currentIndex, field3);
				
				if (shapeType == "rectangle")
				{
					getArgument(command, lineSize, currentIndex, field4);
					getArgument(command, lineSize, currentIndex, color);
					shapes.addRectangle(x, y, field3, field4, color);
				}
				else if (shapeType == "circle")
				{
					getArgument(command, lineSize, currentIndex, color);
					shapes.addCircle(x, y, field3, color);
				}
				else if (shapeType == "line")
				{
					getArgument(command, lineSize, currentIndex, field4);
					getArgument(command, lineSize, currentIndex, color);
					shapes.addLine(x, y, field3, field4, color);
				}
				else
				{
					throw std::invalid_argument("You cannot create this shape!");
				}
			}
			else if (isPrefix(command, "erase"))
			{
				size_t index=0;
				shapes.eraseFigure(index);
			}
			else if (isPrefix(command, "translate"))
			{

			}
			else if (isPrefix(command, "within"))
			{

			}
			else if (isPrefix(command, "pointIn"))
			{

			}
			else if (isPrefix(command, "print"))
			{
				shapes.printShapes();
			}
			else if (isPrefix(command, "Areas"))
			{
				shapes.printAreas();
			}
			else if (isPrefix(command, "Pers"))
			{
				shapes.printPerimteres();
			}
			else
			{
				throw std::invalid_argument("Invalid command");
			}
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what();
		}
		catch (std::exception& e)
		{
			std::cout << e.what();
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what();
		}

		std::cout << ">";
		command.getline(std::cin);
	}
}