#pragma once
class CheckingAccount : public BankAccount
{


public:


	virtual string toString() override
	{
		return to_string(id) + " " + "-1 " + to_string(balance) + " " + to_string(owner->getId());
	}

	CheckingAccount(Person * owner, double balance)
		:BankAccount(owner, balance)
	{

	}

	CheckingAccount(Person *owner, double balance, int id)
		: BankAccount(owner, balance, id)
	{

	}

	virtual void withdraw(double amount) override
	{
		if (balance >= amount)
		{
			balance -= amount;
			owner->addMoney(amount);
		}
		else
		{
			cout << "There is not enough money to withdraw\n";
		}
	}

	virtual void topUp(double amount) override
	{
		if (owner->getBalance() >= amount)
		{
			balance += amount;
			owner->takeMoney(amount);
		}
		else
			cout << "Client doesn't have enough money" << endl;

	}

	virtual void printAccountInfo() override
	{
		BankAccount::printAccountInfo();
		cout << "   this is primary account" << endl;
	}


};