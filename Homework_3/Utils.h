#pragma once
#include "MyString.h"
#include "ShapeCollection.h"
#include "Collection.hpp"

bool isPrefix(const MyString& text, const MyString& prefix);

void loadFigures(const MyString& path, ShapeCollection& shapes, Collection<MyString>& headers);

void getShapeType(const MyString& line, MyString& type, size_t& lineSize, size_t& currentIndex);

void readUnnecessaryLines(std::ifstream& sourceFile, Collection<MyString>& headers);

int getStartindex(const MyString& line, size_t& lineSize);

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument);

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument);

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument);

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument);

void getTranslateArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument);

void printHelpMenu();