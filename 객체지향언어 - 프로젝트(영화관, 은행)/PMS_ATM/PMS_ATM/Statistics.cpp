#include "Statistics.h"
#include "Account.h"
#include "ATMachine.h"

#include <iostream>

int Statistics::sum(Account* pArray, int size)
{
	int sum = 0;
	for (int i = 0;i < size;i++)
		sum = sum + pArray[i].getBalance();
	return sum;
}

int Statistics::average(Account* pArray, int size)
{
	int sum = 0;
	for (int i = 0;i < size;i++)
		sum = sum + pArray[i].getBalance();
	return sum/size;
}

int Statistics::max(Account* pArray, int size)
{
	int max = 0;
	max = pArray[0].getBalance();
	for (int i = 0;i < size;i++)
	{
		if (max <= pArray[i].getBalance())
			max = pArray[i].getBalance();
	}
	return max;
}
