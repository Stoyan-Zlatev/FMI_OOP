#pragma once
#include "MyString.h"
#include "Bank.h"

bool isPrefix(const MyString& text, const MyString& prefix);

void printMenu();

void printEditMenu();

void printCustomerMenu();

void printAccountMenu();

void printListMenu();

void printActionMenu();

void printAccountTypes();

void initBank(Bank& bank);