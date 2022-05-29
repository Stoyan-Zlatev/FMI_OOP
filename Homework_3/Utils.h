#pragma once
#include "MyString.h"
#include "ShapeCollection.h"

bool isPrefix(const MyString& text, const MyString& prefix);

void loadFigures(const MyString& path, ShapeCollection& shapes);

void getShapeType(const MyString& line, MyString& type, size_t& lineSize, size_t& currentIndex);

int getStartindex(const MyString& line, size_t& lineSize);

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument, char el);

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument);

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument);

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument, char el);

void loadArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument);

void getArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument);

void readUnnecessaryLines(std::ifstream& sourceFile, MyString& line);
