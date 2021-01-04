#include "ATMachine.h"
#include "Account.h"
#include "Statistics.h"

#include <iostream>

using namespace std;

int MachineBalance = 0;

ATMachine::ATMachine(int size, int balance, string password)
{
	pAcctArray = new Account[size];
	nMaxAccountNum = size;
	nMachineBalance = balance;
	MachineBalance = balance;
	strManagerPassword = password;
	nCurrentAccountNum = 0;
}

void ATMachine::displayMenu()
{
	cout << "\n" << endl;
	cout << "--------------------" << endl;
	cout << "-     KPU bank     -" << endl;
	cout << "--------------------" << endl;
	cout << "1. 계좌 개설" << endl;
	cout << "2. 계좌 조회" << endl;
	cout << "3. 계좌 입금" << endl;
	cout << "4. 계좌 출금" << endl;
	cout << "5. 계좌 이체" << endl;
	cout << "6. 고객 관리" << endl;
	cout << "9. 업무 종료 \n" << endl;
}

void ATMachine::createAccount()
{
	string name;
	string password;
	static int id = BASE_ACCOUNT_ID;
	int balance = 0;
	if (nCurrentAccountNum < nMaxAccountNum)
	{
		cout << "------- 개설 -------" << endl;
		cout << "이름 입력 : ";
		cin >> name;
		cout << "비밀번호 입력 : ";
		cin >> password;
		pAcctArray[nCurrentAccountNum].create(id, balance, name, password);
		cout << "\n" << endl;
		cout << name << "님 " << id << "번 " << "계좌번호가 정상적으로 개설되었습니다. 감사합니다." << endl;
		id++;
		nCurrentAccountNum++;
	}
	else
		cout << "고객 수 초과, 계좌 개설 실패" << endl;
}

void ATMachine::checkMoney()
{
	int id;
	string password;
	cout << "------- 조회 ------" << endl;
	cout << "계좌번호 입력 : ";
	cin >> id;
	cout << "비밀번호 입력 : ";
	cin >> password;
	int index = id - nMaxAccountNum;

	int nBlance;
	nBlance = pAcctArray[index].check(id, password);

	if (nBlance == AUTHENTIFICATION_FAIL)
		cout << "비밀번호 틀렸습니다. 처음으로 돌아갑니다. \n" << endl;
	else
		cout << "현재 잔액 : " << nBlance << "\n" << endl;
}


void ATMachine::depositMoney()
{
	int id;
	string password;
	int money;
	cout << "------- 입금 ------" << endl;
	cout << "계좌번호 입력 : ";
	cin >> id;
	cout << "비밀번호 입력 : ";
	cin >> password;
	int index = id - nMaxAccountNum;
	int nBlance;
	nBlance = pAcctArray[index].check(id, password);

	if (nBlance == AUTHENTIFICATION_FAIL)
		cout << "비밀번호 틀렸습니다. 처음으로 돌아갑니다. \n" << endl;
	else
	{
		cout << "입금액  입력:";
		cin >> money;
		nMachineBalance = nMachineBalance + money;
		nBlance = pAcctArray[index].deposit(id, password, money);
		cout << "입금 완료" << endl;
	}
}

void ATMachine::widrawMoney()
{
	int id;
	string password;
	int money;
	cout << "------- 출금 ------" << endl;
	cout << "계좌번호 입력 : ";
	cin >> id;
	cout << "비밀번호 입력 : ";
	cin >> password;
	int index = id - nMaxAccountNum;
	int nBlance;
	nBlance = pAcctArray[index].check(id, password);

	if (nBlance == AUTHENTIFICATION_FAIL)
		cout << "비밀번호 틀렸습니다. 처음으로 돌아갑니다. \n" << endl;
	else
	{
		cout << "출금액   입력 : ";
		cin >> money;
		nMachineBalance = nMachineBalance - money;
		nBlance = pAcctArray[index].widraw(id, password, money);
		
		if (nBlance != -1)cout << "출금 완료" << endl;
	}
}

void ATMachine::transfer()
{
	int id;
	string password;
	cout << "------- 이체 ------" << endl;
	cout << "계좌번호 입력 : ";
	cin >> id;
	cout << "비밀번호 입력 : ";
	cin >> password;
	int index = id - nMaxAccountNum;

	int nBlance;
	nBlance = pAcctArray[index].check(id, password);

	if (nBlance == AUTHENTIFICATION_FAIL)
		cout << "비밀번호 틀렸습니다. 처음으로 돌아갑니다. \n" << endl;
	else
	{
		int trans_id;
		int trans_money;
		cout << "이체계좌 입력 : ";
		cin >> trans_id;
		cout << "이체금액 입력 : ";
		cin >> trans_money;
		int trans_index = trans_id - nMaxAccountNum;
		nBlance = pAcctArray[index].widraw(id,password,trans_money);
		nBlance = pAcctArray[trans_index].deposit(trans_id, trans_money);
	}

}

bool ATMachine::isManager(string password)
{
	if (strManagerPassword ==password) return true;
	else return false;
}

void ATMachine::displayReport()
{
	int sum,avg,max;
	Statistics stat;

	sum = stat.sum(pAcctArray, nCurrentAccountNum);
	avg = stat.average(pAcctArray, nCurrentAccountNum);
	max = stat.max(pAcctArray, nCurrentAccountNum);
	cout << "ATM 현금 잔고:		" << nMachineBalance << endl;
	cout << "고객 잔고 통액:		" << sum <<"(총"<< nCurrentAccountNum <<"명)"<< endl;
	cout << "고객 잔고 평균:		" << avg << endl;
	cout << "고객 잔고 최고:		" << max << endl;

	cout << "\n-------계좌현황------" << endl;
	cout << "---------------------" << endl;
	for (int i = 0;i < nCurrentAccountNum;i++)
		cout << pAcctArray[i].getAccountName() << "	" << i + nMaxAccountNum << "	" << pAcctArray[i].getBalance() << endl;
}

void  ATMachine::managerMode()
{
	int result;
	string password;
	cout << "------- 관리 ------\n" << endl;
	cout << "관리자 비밀번호 입력: ";
	cin >> password;
	result = isManager(password);
	if (result == true)
	{
		cout << "관리자입니다.\n" << endl;
		displayReport();
	}
	else cout << "관리자 비밀번호 틀렸습니다. 처음으로 돌아갑니다.\n" << endl;

		
}
ATMachine:: ~ATMachine()
{
	delete[]pAcctArray;
}