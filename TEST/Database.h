#pragma once

class Database;


ifstream inputFileClients;
ifstream inputFileAccounts;
ofstream outputFileClients;
ofstream outputFileAccounts;



class Database
{
private:

	vector <BankAccount*> accounts;
	vector <CheckingAccount*> checkingAccounts;
	vector <SavingsAccount*> savingAccounts;
	vector <Person*> clients;


public:

	Database()
	{
		readFromFiles();
	}

	~Database()
	{
		saveToFiles();
		for (auto i : accounts)
			delete i;
		for (auto i : clients)
			delete i;
	}

	BankAccount * getAccountById(int id)
	{
		for (auto i : accounts)
			if (i->getId() == id)
				return i;

		return nullptr;
	}

	Person * getClientById(int id)
	{
		for (auto i : clients)
			if (i->getId() == id)
				return i;

		return nullptr;
	}

	CheckingAccount * getCheckingByOwnersId(int id)
	{
		for (auto i : checkingAccounts)
		{
			if (i->getOwnersId() == id)
				return i;
		}

		return nullptr;
	}

	CheckingAccount * getCheckingById(int id)
	{
		for (auto i : checkingAccounts)
			if (i->getId() == id)
				return i;

		return nullptr;
	}

	SavingsAccount * getSavingsByOwnersId(int id)
	{
		for (auto i : savingAccounts)
		{
			if (i->getOwnersId() == id)
				return i;
		}

		return nullptr;
	}

	SavingsAccount * getSavingsById(int id)
	{
		for (auto i : savingAccounts)
			if (i->getId() == id)
				return i;

		return nullptr;
	}


	int numberOfClients()
	{
		return clients.size();
	}

	void printAllAccounts()
	{
		cout << "Printing all accounts:\n";
		for (auto i : accounts)
			i->printAccountInfo();
	}

	void printAllClients()
	{
		cout << "Prining all clients: \n";
		for (auto i : clients)
			i->printPerson();
	}

	void printAllSavingsAccounts()
	{
		for (auto account : savingAccounts)
			account->printAccountInfo();
	}

	void printAllCheckingAccounts()
	{
		for (auto account : checkingAccounts)
			account->printAccountInfo();
	}

	void transfer(int idDest, int idSender, double amount)
	{
		BankAccount *sender = getAccountById(idSender);

		if (sender == nullptr)
		{
			cout << "There is no such bank account to send money from!" << endl;
			return;
		}

		BankAccount *destination = getAccountById(idDest);

		if (destination == nullptr)
		{
			cout << "There is no such bank account to send money to!" << endl;
			return;
		}

		if (sender->getBalance() >= amount)
		{
			sender->takeMoney(amount);
			destination->addMoney(amount);
		}
		else
		{
			cout << "Sender has not enought money to send it!" << endl;
		}

	}

	Person * hasClientOfId(int id)
	{

		for (auto client : clients)
		{
			if (client->getId() == id)
				return client;
		}
		return nullptr;
	}

	BankAccount * hasAccountOfId(int id)
	{

		for (auto account : accounts)
		{
			if (account->getId() == id)
				return account;
		}
		return nullptr;
	}

	int numberOfAccounts()
	{
		return accounts.size();
	}

	void addAccount()
	{
		cout << "Select id of person for whom you want to create account: ";

		int idPerson = (int)getPositiveNumber();
		Person * client = getClientById(idPerson);

		if (client == nullptr)
		{
			cout << "There is no client with such id" << endl;
			return;
		}

		cout << "Choose if you want to create checking or savings account, choose 1 or 2: ";
		char choice;
		cin >> choice;

		if (choice != '1' && choice != '2')
		{
			cout << "There is no such option!" << endl;
			return;
		}


		if (choice == '1')
		{
			for (auto i : checkingAccounts)
			{
				if (i->getOwnersId() == idPerson)
				{
					cout << "Client already has an account!" << endl;
					return;
				}
			}
		}

		bool hasChecking = false;

		if (choice == '2')
		{

			for (auto i : accounts)
			{
				if (i->getOwnersId() == idPerson && i->getType() == primary)
					hasChecking = true;

				if (i->getOwnersId() == idPerson && i->getType() == secondary)
				{
					cout << "Client already has a savings account!" << endl;
					return;
				}
			}
		}


		if (choice == '1')
		{

			cout << "Choose the amount of money from client to be the starting balance, you can choose 0 also: ";
			double amount = getPositiveNumber();

			if (amount > client->getBalance())
			{
				cout << "Client has not enough money to do that! Creating account with balance 0" << endl;
				amount = 0;
			}

			client->takeMoney(amount);

			auto * res = new CheckingAccount(client, amount);
			accounts.push_back(res);
			checkingAccounts.push_back(res);
			cout << "Checking account successfully created" << endl;
		}
		if (choice == '2')
		{
			if (!hasChecking)
			{
				cout << "You cannot create savings account for client without checking account" << endl;
				return;
			}
			cout << "Choose the amount of money from client to be the starting balance, you can choose 0 also: ";
			double amount = getPositiveNumber();

			if (amount > client->getBalance())
			{
				cout << "Client has not enough money to do that! Creating account with balance 0" << endl;
				amount = 0;
			}

			client->takeMoney(amount);
			auto * res = new SavingsAccount(client, amount, getCheckingByOwnersId(idPerson));
			accounts.push_back(res);
			savingAccounts.push_back(res);
		}

	}

	void removeSavingAccount(SavingsAccount * savs)
	{
		if (savs != nullptr)
		{
			savs->withdraw(savs->getBalance());

			int i = 0;
			for (auto account : savingAccounts)
			{
				if (account->getId() == savs->getId())
				{
					savingAccounts.erase(savingAccounts.begin() + i);
					break;
				}
				i++;
			}
			i = 0;
			for (auto account : accounts)
			{
				if (account->getId() == savs->getId())
				{
					accounts.erase(accounts.begin() + i);
					break;
				}
				i++;
			}

			delete savs;
		}
	}

	void removeCheckingAccount(CheckingAccount * target)
	{
		SavingsAccount *savs = getSavingsByOwnersId(target->getOwnersId());

		removeSavingAccount(savs);


		target->withdraw(target->getBalance());
		int i = 0;
		for (auto account : checkingAccounts)
		{
			if (account->getId() == target->getId())
			{
				checkingAccounts.erase(checkingAccounts.begin() + i);
			}
			i++;
		}
		i = 0;
		for (auto account : accounts)
		{
			if (account->getId() == target->getId())
			{
				accounts.erase(accounts.begin() + i);
				break;
			}
			i++;
		}

		delete target;
	}

	void removeAccount()
	{
		cout << "If you want to delete checking account corresponding savings account will be deleted too (if present).\n"
			"All money from both accounts will be transfered to owners pocket\n"
			"Choose the ID of account you want to delete: ";
		int choice = (int)getPositiveNumber();

		BankAccount *target = getAccountById(choice);

		if (target == nullptr)
		{
			cout << "There is no account of that ID." << endl;
			return;
		}

		if (target->getType() == primary)
		{
			SavingsAccount *savs = getSavingsByOwnersId(target->getOwnersId());

			removeSavingAccount(savs);

			CheckingAccount *ctarget = getCheckingById(target->getId());

			removeCheckingAccount(ctarget);

		}
		else
			if (target->getType() == secondary)
			{
				auto *savs = getSavingsById(choice);
				removeSavingAccount(savs);
			}
			else
			{

			}

	}

	void addClient()
	{
		string name;
		string surname;
		double balance;

		cout << "Choose name for client: ";
		cin >> name;
		cout << "Choose surname for client: ";
		cin >> surname;
		cout << "Choose balance of client: ";

		balance = getPositiveNumber();

		clients.push_back(new Person(name, surname, balance));

	}

	void removeClient()
	{
		cout << "Provide id of client you want to delete: ";
		int id = (int)getPositiveNumber();

		Person *target = getClientById(id);

		if (target == nullptr)
		{
			cout << "There is no such client" << endl;
			return;
		}

		cout << "Client will be deleted along with all his accounts" << endl;

		removeCheckingAccount(getCheckingByOwnersId(id));

		int i = 0;
		for (auto client : clients)
		{
			if (client->getId() == id)
			{
				clients.erase(clients.begin() + i);
				delete client;
			}
			i++;
		}


	}

	void readFromFiles()
	{
		inputFileClients.open("clients.txt");
		inputFileAccounts.open("accounts.txt");

		if (!inputFileAccounts || !inputFileClients)
			throw exception();


		string name, surname;
		int idClient, id, originId;
		double balance;

		while (inputFileClients >> name >> surname >> idClient >> balance)
		{
			clients.push_back(new Person(name, surname, balance));
		}
		while (inputFileAccounts >> id >> originId >> balance >> idClient)
		{
			if (originId < 0)
			{
				CheckingAccount * target = new CheckingAccount(getClientById(idClient), balance, id);
				checkingAccounts.push_back(target);
				accounts.push_back(target);
			}
			else
			{
				SavingsAccount * target = new SavingsAccount(getClientById(idClient), balance, getCheckingByOwnersId(idClient), id);
				savingAccounts.push_back(target);
				accounts.push_back(target);
			}
		}


		inputFileClients.close();
		inputFileAccounts.close();
	}

	void saveToFiles()
	{
		outputFileAccounts.open("accounts.txt");
		outputFileClients.open("clients.txt");

		for (auto client : clients)
		{
			outputFileClients << client->getPerson() << endl;
		}
		for (auto account : accounts)
		{
			outputFileAccounts << account->toString() << endl;
		}


		outputFileAccounts.close();
		outputFileClients.close();
	}

};