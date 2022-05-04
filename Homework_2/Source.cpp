#include <iostream>
#include <cstring>
#include <fstream>
#include "MyString.h"
#include "Kindle.h"
#include "Book.h"

int main()
{
	std::fstream sourceFile("FMIKindle.dat", std::ios::app, std::ios::binary);

	if (!sourceFile.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
		return -1;
	}

	MyString command = "";
	Kindle fmiKindle;
	//fmiKindle.load(sourceFile);
	//	fmiKindle.printFirstUser();
	std::cout << ">";
	std::cin >> command;
	while (!(command == "exit"))
	{
		try
		{
			if (command == "login")
			{
				MyString username;
				std::cout << "Enter username: ";
				std::cin >> username;
				MyString password;
				std::cout << "Enter password: ";
				std::cin >> password;
				fmiKindle.login(std::move(username), std::move(password));
				std::cout << "\tWelcome," << fmiKindle.getCurrentUserName() << std::endl;
			}
			else if (command == "signup")
			{
				MyString username;
				std::cout << "Enter username: ";
				std::cin >> username;
				MyString password;
				std::cout << "Enter password: ";
				std::cin >> password;
				fmiKindle.signup(std::move(username), std::move(password));
				std::cout << "\tUser registered!" << std::endl;
			}
			else if (command == "logout")
			{
				fmiKindle.logout(sourceFile);
			}
			else if (command == "view")
			{
				fmiKindle.view();
			}
			else if (command == "read")
			{
				char readCommand = '\0';
				int currentIndex = 0;
				//MyString gets to first space
				/*char buffer[MaxContentLength];
				std::cin.getline(buffer, MaxContentLength);
				MyString bookName = "";
				for (size_t i = 0; i < strlen(buffer); i++)
				{
					bookName += (char)buffer[i];
				}*/
				while (readCommand != 'q')
				{
					Book book = fmiKindle.getBookByName(command);
					if (command == 'n')
					{

					}
					else if (command == 'p')
					{

					}
					std::cin >> readCommand;
				}
			}
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
		}

		std::cout << ">";
		std::cin >> command;
	}
}