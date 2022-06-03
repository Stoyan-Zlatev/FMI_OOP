#pragma once
#include"MyString.h"
#include "Collection.hpp"
#include<fstream>

void writeString(std::ofstream& outFile, const MyString& str);

void readString(std::ifstream& inFile, MyString& str);

void saveCircle(std::ofstream& file, double& cx, double& cy, double& radius, const MyString& color);

void readCircle(const MyString& line, size_t& lineSize, size_t& currentIndex, double& cx, double& cy, double& radius, MyString& color);

void saveRectangle(std::ofstream& file, double& x, double& y, double& width, double& height, const MyString& color);

void readRectangle(const MyString& line, size_t& lineSize, size_t& currentIndex, double& x, double& y, double& width, double& height, MyString& color);

void saveLine(std::ofstream& file, double& x1, double& y1, double& x2, double& y2, const MyString& color);

void readLine(const MyString& line, size_t& lineSize, size_t& currentIndex, double& x1, double& y1, double& x2, double& y2, MyString& color);

void saveHeaders(std::ofstream& file, const Collection<MyString>& headers);
