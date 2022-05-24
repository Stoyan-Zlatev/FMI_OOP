#pragma once
class SavingsAccount
{
	double interestRate;
public:
	void deposit();
	bool withdraw();
	void display() const;
	/*Класът SavingsAccount наследява Account,като го допълва с:
 interestRate – годишен лихвен процент
и реализира методите:
 deposit – за добавяне на сума към банковата сметка.
 withdraw – Винаги връща false и не позволява изтегляне на сума от банковата
сметка.
 display – за извеждане на информация за сметката*/
};