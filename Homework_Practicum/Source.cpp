#include <iostream>
#include "MyString.h"
#include "Bank.h"
#include "Utils.h"

void main()
{
	std::fstream sourceFile("FMIKindle.dat", std::ios::in | std::ios::binary);

	if (!sourceFile.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
	}

	MyString command;
	MyString field1;
	MyString field2;

	Bank bank;
	bank.load(sourceFile);

	sourceFile.close();

	printMenu();
	std::cout << ">";
	command.getline(std::cin);


	while (true)
	{
		try
		{
			if (isPrefix(command, "1"))
			{
				printEditMenu();
				std::cout << ">";
				command.getline(std::cin);

				if (isPrefix(command, "a"))
				{
					printCustomerMenu();
					std::cout << ">";
					command.getline(std::cin);

					if (isPrefix(command, "i"))
					{
						bank.addCustomer();
					}
					else if (isPrefix(command, "ii"))
					{

					}
				}
				else if (isPrefix(command, "b"))
				{
					printAccountMenu();
					std::cout << ">";
					command.getline(std::cin);

					if (isPrefix(command, "i"))
					{

					}
					else if (isPrefix(command, "ii"))
					{

					}
				}
			}
			else if (isPrefix(command, "2"))
			{
				printListMenu();
				std::cout << ">";
				command.getline(std::cin);
				if (isPrefix(command, "a"))
				{
					bank.listAllCustomers();
				}
				else if (isPrefix(command, "b"))
				{

				}
				else if (isPrefix(command, "c"))
				{

				}
				else if (isPrefix(command, "d"))
				{

				}
			}
			else if (isPrefix(command, "3"))
			{
				printAccountMenu();
				std::cout << ">";
				command.getline(std::cin);
				if (isPrefix(command, "a"))
				{
				}
				else if (isPrefix(command, "b"))
				{

				}
				else if (isPrefix(command, "c"))
				{
					std::cout << "Enter your iban: ";
					MyString senderIban;
					senderIban.getline(std::cin);

					std::cout << "Enter receiver's iban: ";
					MyString receiverIban;
					receiverIban.getline(std::cin);

					std::cout << "Enter amount you want to transfer: ";
					double amount;
					std::cin >> amount;

					bank.transfer(senderIban, receiverIban, amount);
				}
			}
			else if (isPrefix(command, "4"))
			{

			}
			else if (isPrefix(command, "5"))
			{

			}
			else
			{

			}

		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
		}

		std::cout << ">";
		command.getline(std::cin);
	}
}