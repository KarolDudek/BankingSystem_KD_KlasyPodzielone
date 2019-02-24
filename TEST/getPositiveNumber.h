#pragma once
using namespace std;

enum type { primary, secondary };


double getPositiveNumber()
{
	double res;
	do
	{
		cout << "Provide the number: ";
		cin >> res;
		if (res < 0)
			cout << "Number has to be positive" << endl;

	} while (res < 0);
	return res;
}