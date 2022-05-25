#include <iostream>
#include <exception>
#include "MyString.h"
#include "Bank.h"
#include "Utils.h"

void main()
{
	std::ifstream sourceFile("Bank.dat", std::ios::in | std::ios::binary);

	if (!sourceFile.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
	}

	MyString command;

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
						std::cout << "Enter username:";
						MyString username;
						username.getline(std::cin);

						std::cout << "Enter customer address:";
						MyString address;
						address.getline(std::cin);

						bank.addCustomer(username, address);
					}
					else if (isPrefix(command, "ii"))
					{
						std::cout << "Enter username:";
						MyString username;
						username.getline(std::cin);

						bank.deleteCustomer(username);
					}
				}
				else if (isPrefix(command, "b"))
				{
					printAccountMenu();
					std::cout << ">";
					command.getline(std::cin);

					if (isPrefix(command, "i"))
					{
						MyString username;
						std::cout << "Enter holder username: ";
						username.getline(std::cin);

						MyString password;
						std::cout << "Enter holder password: ";
						password.getline(std::cin);

						MyString iban;
						std::cout << "Enter account iban: ";
						iban.getline(std::cin);

						size_t accountType;
						printAccountTypes();
						std::cout << ">";
						std::cin >> accountType;

						bank.addAccount(iban, username, password, accountType);
					}
					else if (isPrefix(command, "ii"))
					{
						MyString iban;
						std::cout << "Enter account iban: ";
						iban.getline(std::cin);

						bank.deleteAccount(iban);
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
					bank.listAllAccounts();
				}
				else if (isPrefix(command, "c"))
				{
					MyString username;
					std::cout << "Enter username: ";
					username.getline(std::cin);

					bank.listCustomerAccounts(username);
				}
				else if (isPrefix(command, "d"))
				{
					bank.listLog();
				}
			}
			else if (isPrefix(command, "3"))
			{
				printActionMenu();
				std::cout << ">";
				command.getline(std::cin);
				if (isPrefix(command, "a"))
				{
					std::cout << "Enter account iban: ";
					MyString iban;
					iban.getline(std::cin);

					std::cout << "Enter amount to withdraw: ";
					double amount;
					std::cin >> amount;

					bank.deposit(iban, amount);
				}
				else if (isPrefix(command, "b"))
				{
					std::cout << "Enter account iban: ";
					MyString receiverIban;
					receiverIban.getline(std::cin);

					std::cout << "Enter amount to deposit: ";
					double amount;
					std::cin >> amount;

					bank.deposit(receiverIban, amount);
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
				std::ofstream file("Bank.dat");
				bank.saveToFile(file);
				return;
			}
			else
			{
				throw std::invalid_argument("Invalid command");
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