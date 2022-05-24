#pragma once
#include "Account.h"
class PriviligeAccount : public Account
{
	/*клас PrivilegeAccount (привилегирована сметка)
Класът PrivilegeAccount наследява Account, като го допълва с
 overdraft – позволен овърдрафт (сума превишаваща кредита)
 и реализира методите:
 deposit – за добавяне на сума към банковата сметка.
 withdraw – за изтегляне на сума от банковата сметка. Ако наличната сума в
сметката + позволения овърдрафт е по-малко от исканата сума, връща false, иначе
намалява сумата на сметката с исканата сума и връща true (в този случай може да
се получи отрицателно число за баланса).
 display – за извеждане на информация за сметката.*/
	double overdraft;
public:
	void deposit();
	bool withdraw();
	void display() const;
};