#include <iostream>
#include <exception>
#include "MyString.h"
#include "Bank.h"
#include "Utils.h"

void main()
{
	std::ifstream sourceFile("Bank.dat", std::ios::in | std::ios::binary);

	Bank bank;
	if (!sourceFile.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
	}
	else
	{
		try
		{
			bank.load(sourceFile);
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "File loaded successfully" << std::endl;
	}

	sourceFile.close();

	if (bank.getBankName() == EmptyString)
	{
		initBank(bank);
	}
	printMenu();

	MyString command;
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


					if (isPrefix(command, "ii"))
					{
						size_t customerId;
						std::cout << "Enter customer id:";
						std::cin >> customerId;
						std::cin.ignore();

						bank.deleteCustomer(customerId);
						std::cout << "Customer deleted successfully!" << std::endl;
					}
					else if (isPrefix(command, "i"))
					{
						MyString username;
						std::cout << "Enter username:";
						username.getline(std::cin);

						std::cout << "Enter customer address:";
						MyString address;
						address.getline(std::cin);

						bank.addCustomer(std::move(username), std::move(address));
						std::cout << "Customer added successfully!" << std::endl;
					}
					else
					{
						throw std::invalid_argument("Invalid command!");
					}
				}
				else if (isPrefix(command, "b"))
				{
					printAccountMenu();
					std::cout << ">";
					command.getline(std::cin);

					if (isPrefix(command, "ii"))
					{
						MyString iban;
						std::cout << "Enter account iban: ";
						iban.getline(std::cin);

						bank.deleteAccount(iban);
						std::cout << "Account deleted successfully!" << std::endl;
					}
					else if (isPrefix(command, "i"))
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

						size_t customerId;
						std::cout << "Enter holder id: ";
						std::cin >> customerId;
						std::cin.ignore();

						size_t accountType;
						printAccountTypes();
						std::cout << ">";
						std::cin >> accountType;
						std::cin.ignore();

						bank.addAccount(std::move(iban), std::move(username), std::move(password), customerId, accountType);
						std::cout << "Account added successfully!" << std::endl;
					}
					else
					{
						throw std::invalid_argument("Invalid command!");
					}
				}
				else
				{
					throw std::invalid_argument("Invalid command!");
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
					size_t customerId;
					std::cout << "Enter customer id:";
					std::cin >> customerId;
					std::cin.ignore();

					bank.listCustomerAccounts(customerId);
				}
				else if (isPrefix(command, "d"))
				{
					bank.listLog();
				}
				else
				{
					throw std::invalid_argument("Invalid command!");
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
					std::cin.ignore();
					bank.withdraw(std::move(iban), amount);
					std::cout << "Successfully withdrew " << amount << "$" << std::endl;
				}
				else if (isPrefix(command, "b"))
				{
					std::cout << "Enter account iban: ";
					MyString receiverIban;
					receiverIban.getline(std::cin);

					std::cout << "Enter amount to deposit: ";
					double amount;
					std::cin >> amount;
					std::cin.ignore();

					bank.deposit(std::move(receiverIban), amount);
					std::cout << "Successfully deposited " << amount << "$" << std::endl;
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
					std::cin.ignore();

					bank.transfer(std::move(senderIban), std::move(receiverIban), amount);
					std::cout << "Successfully transfered " << amount << "$" << std::endl;
				}
				else
				{
					throw std::invalid_argument("Invalid command!");
				}
			}
			else if (isPrefix(command, "4"))
			{
				bank.display();
			}
			else if (isPrefix(command, "5"))
			{
				std::ofstream file("Bank.dat");
				bank.saveToFile(file);
				break;
			}
			else
			{
				throw std::invalid_argument("Invalid command");
			}
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
		}

		std::cout << ">";
		command.getline(std::cin);
	}
}