#pragma once
#include "Account.h"

class NormalAccount : public Account
{
	//should probably override from account
public:
	void deposit();
	bool withdraw();
	void display() const;
};