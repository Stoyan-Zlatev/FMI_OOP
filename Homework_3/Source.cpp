#include <iostream>
#include <fstream>
#include <exception>
#include "ShapeCollection.h"
#include "MyString.h"
#include "Utils.h"
#include "Collection.hpp"

void main()
{
	MyString path;
	std::cout << ">";
	path.getline(std::cin);

	Collection<MyString> headers;
	ShapeCollection shapes;
	loadFigures(path, shapes, headers);

	std::cout << ">";
	MyString command;
	command.getline(std::cin);
	size_t lineSize = 0;
	size_t currentIndex = 0;
	while (true)
	{
		lineSize = strlen(command.c_str());
		currentIndex = 0;
		try
		{
			if (isPrefix(command, "print"))
			{
				shapes.printShapes();
			}
			else if (isPrefix(command, "areas"))
			{
				shapes.printAreas();
			}
			else if (isPrefix(command, "pers"))
			{
				shapes.printPerimteres();
			}
			else if (isPrefix(command, "save"))
			{
				shapes.saveToFile(std::move(path), headers);
			}
			else if (isPrefix(command, "exit"))
			{
				return;
			}
			else
			{
				MyString shapeType;
				if (isPrefix(command, "erase"))
				{
					double shapeIndex = 0;
					getArgument(std::move(command), lineSize, currentIndex, shapeIndex);
					shapes.eraseFigure((shapeIndex - 1), shapeType);
						std::cout << "Erased a " << shapeType << " (" << shapeIndex << ")" << std::endl;
				}
				else
				{
					double field1 = 0, field2 = 0;
					if (isPrefix(command, "pointIn"))
					{
						getArgument(command, lineSize, currentIndex, field1);
						getArgument(command, lineSize, currentIndex, field2);
						shapes.pointIn(field1, field2);
					}
					else if (isPrefix(command, "translate"))
					{
						double shapeIndex = -1;
						getTranslateArgument(command, lineSize, currentIndex, field1);
						getTranslateArgument(command, lineSize, currentIndex, field2);
						getArgument(command, lineSize, currentIndex, shapeIndex);
						if (shapeIndex == -1)
						{
							shapes.translate(field1, field2);
							std::cout << "Translated all figures" << std::endl;
						}
						else
						{
							shapes.translate(field1, field2, (shapeIndex - 1), shapeType);
							std::cout << "Translated a " << shapeType << " (" << shapeIndex << ")" << std::endl;

						}
					}
					else
					{
						double field3 = 0, field4 = 0;
						if (isPrefix(command, "create"))
						{
							MyString color;
							getArgument(command, lineSize, currentIndex, shapeType);
							getArgument(command, lineSize, currentIndex, field1);
							getArgument(command, lineSize, currentIndex, field2);
							getArgument(command, lineSize, currentIndex, field3);

							if (shapeType == "rectangle")
							{
								getArgument(command, lineSize, currentIndex, field4);
								getArgument(command, lineSize, currentIndex, color);
								shapes.addRectangle(field1, field2, field3, field4, color);
							}
							else if (shapeType == "circle")
							{
								getArgument(command, lineSize, currentIndex, color);
								shapes.addCircle(field1, field2, field3, color);
							}
							else if (shapeType == "line")
							{
								getArgument(command, lineSize, currentIndex, field4);
								getArgument(command, lineSize, currentIndex, color);
								shapes.addLine(field1, field2, field3, field4, color);
							}
							else
							{
								throw std::invalid_argument("You cannot create this shape!\n");
							}

							std::cout << "Successfully created " << shapeType << " (" << shapes.getShapesCount() << ")" << std::endl;
						}
						else if (isPrefix(command, "within"))
						{
							getArgument(command, lineSize, currentIndex, shapeType);
							getArgument(command, lineSize, currentIndex, field1);
							getArgument(command, lineSize, currentIndex, field2);
							getArgument(command, lineSize, currentIndex, field3);
							if (shapeType == "circle")
							{
								shapes.withinCircle(field1, field2, field3);
							}
							else if (shapeType == "rectangle")
							{
								getArgument(command, lineSize, currentIndex, field4);
								shapes.withinRectangle(field1, field2, field3, field4);
							}
							else
							{
								throw std::invalid_argument("Invalid shape entered!\n");
							}
						}
						else
						{
							throw std::invalid_argument("Invalid command!\n");
						}
					}
				}
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