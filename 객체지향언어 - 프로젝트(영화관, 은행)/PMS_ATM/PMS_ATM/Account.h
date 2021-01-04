#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "ATMachine.h"
using std::string;

#define AUTHENTIFICATION_FAIL -1
#define AUTHENTIFICATION_SUCCESS 1
#define BASE_ACCOUNT_ID 100

class Account
{
private:
	int nID;
	int nBalance;
	string strAccountName;
	string strPassword;

private:
	inline bool authenticate(int id, string password);

public:
	Account();
	Account(int id, int money, string name, string password);
	void create(int id, int money, string name, string password);
	int check(int id, string password);
	int deposit(int id, string password, int money);
	int widraw(int id, string password, int money);
	int deposit(int id, int money);

	int getAcctID() { return nID; }
	int getBalance() { return nBalance; }
	string getAccountName() { return strAccountName; }
};

#endif