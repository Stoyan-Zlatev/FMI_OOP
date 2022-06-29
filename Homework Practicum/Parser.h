#pragma once
#include "MyString.h"

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, double& argument, char startSeparator, char endSeparator);

void parseArgument(const MyString& line, size_t& lineSize, size_t& currentIndex, MyString& argument, char startSeparator, char endSeparator);

MyString parseDoubleToString(double value);

MyString parseIntToString(int value);

char parseIntToChar(size_t value);

size_t getNumSize(int number);

void swap(char& el1, char& el2);
