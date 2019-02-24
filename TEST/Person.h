#pragma once
#include "getPositiveNumber.h"


using namespace std;
class Person
{
	string name;
	string surname;
	int id;
	static int nextId;
	double balance;

public:

	Person(string name, string surname, double balance)
	{
		this->name = name;
		this->surname = surname;
		this->balance = balance;
		id = nextId;
		nextId++;
	}
	Person(string name, string surname, double balance, int ID)
	{
		this->name = name;
		this->surname = surname;
		this->balance = balance;
		id = ID;
		if (ID >= nextId)
			nextId = ID;
	}
	int getId()
	{
		return id;
	}

	double getBalance()
	{
		return balance;
	}

	void addMoney(double amount)
	{
		balance += amount;
	}

	void takeMoney(double amount)
	{
		balance -= amount;
	}

	virtual void printPerson()
	{
		printf("%s %s with id: %d and balance %f\n", name.c_str(), surname.c_str(), id, balance);
	}

	virtual string getPerson()
	{
		return name + " " + surname + " " + to_string(id) + " " + to_string(balance);
	}

	void updateBalance()
	{
		double b;

		cout << "What is the new balance?: " << endl;
		b = getPositiveNumber();

		balance = b;
	}

};

int Person::nextId = 0;
