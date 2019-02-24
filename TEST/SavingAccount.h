#pragma once

class SavingsAccount : public BankAccount
{

private:

	CheckingAccount * mainAccount;

public:

	SavingsAccount(Person * owner, double balance, CheckingAccount * mainacc)
		:BankAccount(owner, balance)
	{
		mainAccount = mainacc;
		t = secondary;
	}
	SavingsAccount(Person * owner, double balance, CheckingAccount * mainacc, int id)
		:BankAccount(owner, balance, id)
	{
		mainAccount = mainacc;
		t = secondary;
	}

	virtual string toString() override
	{
		return to_string(id) + " " + to_string(mainAccount->getId()) + " " + to_string(balance) + " " + to_string(owner->getId());
	}


	virtual void withdraw(double amount) override
	{
		if (balance >= amount)
		{
			balance -= amount;
			mainAccount->addMoney(amount);
		}
		else
		{
			cout << "There is not enough money to withdraw\n";
		}
	}

	virtual void topUp(double amount) override
	{
		if (mainAccount->getBalance() >= amount)
		{
			balance += amount;
			mainAccount->takeMoney(amount);
		}
		else
			cout << "There is not enough money on primary account, sorry" << endl;
	}

	virtual void printAccountInfo() override
	{
		BankAccount::printAccountInfo();
		cout << "   this is a savings account with primary account of id: " << mainAccount->getId() << endl;
	}


};
