#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <string>
#include "Person.h"
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Database.h"
using namespace std;




void printMenu()
{
	cout << "//////////////////////MENU//////////////////////" << endl;
	cout << "1. Print whole database" << endl;
	cout << "2. Print all clients" << endl;
	cout << "3. Print all saving accounts" << endl;
	cout << "4. Print all checking acounts" << endl;
	cout << "5. Update client balance" << endl;
	cout << "6. Add client to database" << endl;
	cout << "7. Add account to database" << endl;
	cout << "8. Make transfer" << endl;
	cout << "9. Delete client from database" << endl;
	cout << "10. Delete account from database" << endl;
	cout << "11. Print menu once more" << endl;
	cout << "12. Leave the program" << endl;
	cout << "//////////////////////MENU//////////////////////" << endl << endl;
}

void handleOptions(Database & db)
{
	printMenu();
	int choice = -1;
	do
	{
		cout << "Choose option from menu: ";
		cin >> choice;
		if (choice > 13 || choice < 1)
		{
			cout << "This is not a valid option" << endl;
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			db.printAllClients();
			db.printAllAccounts();
			break;
		}
		case 2:
		{
			db.printAllClients();
			break;
		}
		case 3:
		{
			db.printAllSavingsAccounts();
			break;
		}
		case 4:
		{
			db.printAllCheckingAccounts();
			break;
		}
		case 5:
		{
			if (db.numberOfClients() > 0)
			{
				db.printAllClients();
				cout << "Choose id: ";
				int idChoice;
				cin >> idChoice;
				auto target = db.hasClientOfId(idChoice);
				if (target)
					target->updateBalance();
				else
					cout << "There is no such client" << endl;
			}
			else
			{
				cout << "There are no clients in database" << endl;
			}
			break;
		}
		case 6:
		{
			db.addClient();
			break;
		}
		case 7:
		{
			db.addAccount();
			break;
		}
		case 8:
		{
			db.printAllAccounts();

			int from, to;
			double amount;
			cout << "Select id of account from which u will transfer money" << endl;
			from = (int)getPositiveNumber();

			if (db.hasAccountOfId(from) == nullptr)
			{
				cout << "There is no account of that id";
				break;
			}

			cout << "Select id of account to which u will transfer money" << endl;
			to = (int)getPositiveNumber();

			if (db.hasAccountOfId(to) == nullptr)
			{
				cout << "There is no account of that id";
				break;
			}

			cout << "Select amount of money you want to transfer: " << endl;
			amount = getPositiveNumber();

			if (db.hasAccountOfId(from)->getBalance() < amount)
			{
				cout << "Not enough money on account to transfer" << endl;
				break;
			}

			db.transfer(to, from, amount);
			break;
		}
		case 9:
		{
			if (db.numberOfClients() > 0)
			{
				db.printAllClients();
				db.removeClient();
			}
			else
			{
				cout << "There are no clients in database" << endl;
			}
			break;
		}
		case 10:
		{
			if (db.numberOfAccounts() > 0)
			{
				db.printAllAccounts();
				db.removeAccount();
			}
			else
			{
				cout << "There are no accounts in database" << endl;
			}
			break;
		}
		case 11:
		{
			printMenu();
			break;
		}
		case 12:
		{
			break;
		}
		default:
		{
			break;
		}

		}

	} while (choice != 12);
}


int main()
{
	try
	{
		Database db;

		handleOptions(db);
	}

	catch (...)
	{
		cerr << "Files didn't open\n";
		outputFileClients.open("clients.txt");
		outputFileAccounts.open("accounts.txt");
		outputFileClients.close();
		outputFileAccounts.close();

		Database db;

		handleOptions(db);

	}


	return 0;
}