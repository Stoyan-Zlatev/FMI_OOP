#pragma once
#include"MyString.h"
#include<fstream>

void writeString(std::ofstream& outFile, const MyString& str);

MyString readString(std::ifstream& inFile);