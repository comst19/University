#include "Account.h"
#include "ATMachine.h"

#include<iostream>
using namespace std;


#define nMaxAccountNum 100
Account::Account()
{
	nID = BASE_ACCOUNT_ID;
}
Account::Account(int id, int money, string name, string password)
{
	nID = id;
	nBalance = money;
	strAccountName = name;
	strPassword = password;
}

inline bool Account::authenticate(int id, string password)
{
	if (nID == id && strPassword == password)
		return true;

	else return false;
}

void Account::create(int id, int money, string name, string password)
{
	nID = id;
	nBalance = money;
	strAccountName = name;
	strPassword = password;
}

int Account::check(int id, string password)
{
	int result;
	result = authenticate(id, password);
	if (result == true) return nBalance;
	if (result == false) return AUTHENTIFICATION_FAIL;
}

int Account::deposit(int id, string password, int money)
{
	nBalance = nBalance + money;
	cout << "ÇöÀç ÀÜ¾× : " << nBalance << endl;
	return nBalance;
}

int Account::widraw(int id, string password, int money)
{
	if (nBalance >= money)
	{
		nBalance = nBalance - money;
		cout << "ÇöÀç ÀÜ¾× : " << nBalance << endl;
		return nBalance;
	}
	else
	{
		cout << "ÀÜ¾× ºÎÁ· \n" << endl;
		return -1;
	}
}

int Account::deposit(int id, int money)
{
	nBalance = nBalance + money;
	cout << "ÀÌÃ¼ ¿Ï·á" << endl;
	return nBalance;
}
