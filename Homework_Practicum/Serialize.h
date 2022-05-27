#pragma once
#include"MyString.h"
#include "Account.h"
#include<fstream>

void writeString(std::ofstream& outFile, const MyString& str);

void readString(std::ifstream& inFile, MyString& str);

void writeAccount(std::ofstream& sourceFile, const Account& account);

void readAccount(std::ifstream& inFile, Account& str);

