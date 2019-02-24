#pragma once

class BankAccount
{

protected:

	double balance;
	int id;
	static int nextId;
	Person * owner;
	type t = primary;

public:

	BankAccount(Person * owner, double balance)
	{
		this->owner = owner;
		this->balance = balance;
		id = nextId;
		nextId++;
	}

	BankAccount(Person * owner, double balance, int id)
	{
		this->owner = owner;
		this->balance = balance;
		this->id = id;
		if (id >= nextId)
			nextId = id;
	}

	virtual void topUp(double amount)
	{

	}

	double getBalance()
	{
		return balance;
	}

	void takeMoney(double amount)
	{
		balance -= amount;
	}

	void addMoney(double amount)
	{
		balance += amount;
	}

	int getOwnersId()
	{
		return owner->getId();
	}

	type getType()
	{
		return t;
	}

	int getId()
	{
		return id;
	}

	virtual void withdraw(double amount)
	{

	}

	virtual void printAccountInfo()
	{
		cout << "Account of id: " << id << " and balance: " << balance << "   owner is person with id: " << owner->getId();
	}

	virtual string toString()
	{
		return "";
	}

};

int BankAccount::nextId = 0;