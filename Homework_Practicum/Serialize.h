#pragma once
#include"MyString.h"
#include<fstream>

void writeString(std::ofstream& outFile, const MyString& str);

void readString(std::ifstream& inFile, MyString& str);