#ifndef ATMACHINE_H
#define ATMACHINE_H

#include "Account.h"
#include <string>
using std::string;

#define NEGATIVE_ATM_BALANCE -10

class Account;
class ATMachine
{
private:
	Account* pAcctArray;
	int nMachineBalance;
	int nMaxAccountNum;
	int nCurrentAccountNum;
	string strManagerPassword;
	bool isManager(string nBalance);
	void displayReport();

public:
	ATMachine(int size, int balance, string password);
	~ATMachine();

	void displayMenu();
	void createAccount();
	void checkMoney();
	void depositMoney();
	void widrawMoney();
	void transfer();
	void managerMode();
};

#endif