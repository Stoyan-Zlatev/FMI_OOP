#include "Utils.h"

bool isCapitalLetter(const char& letter)
{
	return letter >= 'A' && letter <= 'Z';
}

size_t getLetterPosition(const char& capitalLetter)
{
	return capitalLetter - 'A';
}
