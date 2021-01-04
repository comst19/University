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
	cout << "1. ���� ����" << endl;
	cout << "2. ���� ��ȸ" << endl;
	cout << "3. ���� �Ա�" << endl;
	cout << "4. ���� ���" << endl;
	cout << "5. ���� ��ü" << endl;
	cout << "6. �� ����" << endl;
	cout << "9. ���� ���� \n" << endl;
}

void ATMachine::createAccount()
{
	string name;
	string password;
	static int id = BASE_ACCOUNT_ID;
	int balance = 0;
	if (nCurrentAccountNum < nMaxAccountNum)
	{
		cout << "------- ���� -------" << endl;
		cout << "�̸� �Է� : ";
		cin >> name;
		cout << "��й�ȣ �Է� : ";
		cin >> password;
		pAcctArray[nCurrentAccountNum].create(id, balance, name, password);
		cout << "\n" << endl;
		cout << name << "�� " << id << "�� " << "���¹�ȣ�� ���������� �����Ǿ����ϴ�. �����մϴ�." << endl;
		id++;
		nCurrentAccountNum++;
	}
	else
		cout << "�� �� �ʰ�, ���� ���� ����" << endl;
}

void ATMachine::checkMoney()
{
	int id;
	string password;
	cout << "------- ��ȸ ------" << endl;
	cout << "���¹�ȣ �Է� : ";
	cin >> id;
	cout << "��й�ȣ �Է� : ";
	cin >> password;
	int index = id - nMaxAccountNum;

	int nBlance;
	nBlance = pAcctArray[index].check(id, password);

	if (nBlance == AUTHENTIFICATION_FAIL)
		cout << "��й�ȣ Ʋ�Ƚ��ϴ�. ó������ ���ư��ϴ�. \n" << endl;
	else
		cout << "���� �ܾ� : " << nBlance << "\n" << endl;
}


void ATMachine::depositMoney()
{
	int id;
	string password;
	int money;
	cout << "------- �Ա� ------" << endl;
	cout << "���¹�ȣ �Է� : ";
	cin >> id;
	cout << "��й�ȣ �Է� : ";
	cin >> password;
	int index = id - nMaxAccountNum;
	int nBlance;
	nBlance = pAcctArray[index].check(id, password);

	if (nBlance == AUTHENTIFICATION_FAIL)
		cout << "��й�ȣ Ʋ�Ƚ��ϴ�. ó������ ���ư��ϴ�. \n" << endl;
	else
	{
		cout << "�Աݾ�  �Է�:";
		cin >> money;
		nMachineBalance = nMachineBalance + money;
		nBlance = pAcctArray[index].deposit(id, password, money);
		cout << "�Ա� �Ϸ�" << endl;
	}
}

void ATMachine::widrawMoney()
{
	int id;
	string password;
	int money;
	cout << "------- ��� ------" << endl;
	cout << "���¹�ȣ �Է� : ";
	cin >> id;
	cout << "��й�ȣ �Է� : ";
	cin >> password;
	int index = id - nMaxAccountNum;
	int nBlance;
	nBlance = pAcctArray[index].check(id, password);

	if (nBlance == AUTHENTIFICATION_FAIL)
		cout << "��й�ȣ Ʋ�Ƚ��ϴ�. ó������ ���ư��ϴ�. \n" << endl;
	else
	{
		cout << "��ݾ�   �Է� : ";
		cin >> money;
		nMachineBalance = nMachineBalance - money;
		nBlance = pAcctArray[index].widraw(id, password, money);
		
		if (nBlance != -1)cout << "��� �Ϸ�" << endl;
	}
}

void ATMachine::transfer()
{
	int id;
	string password;
	cout << "------- ��ü ------" << endl;
	cout << "���¹�ȣ �Է� : ";
	cin >> id;
	cout << "��й�ȣ �Է� : ";
	cin >> password;
	int index = id - nMaxAccountNum;

	int nBlance;
	nBlance = pAcctArray[index].check(id, password);

	if (nBlance == AUTHENTIFICATION_FAIL)
		cout << "��й�ȣ Ʋ�Ƚ��ϴ�. ó������ ���ư��ϴ�. \n" << endl;
	else
	{
		int trans_id;
		int trans_money;
		cout << "��ü���� �Է� : ";
		cin >> trans_id;
		cout << "��ü�ݾ� �Է� : ";
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
	cout << "ATM ���� �ܰ�:		" << nMachineBalance << endl;
	cout << "�� �ܰ� ���:		" << sum <<"(��"<< nCurrentAccountNum <<"��)"<< endl;
	cout << "�� �ܰ� ���:		" << avg << endl;
	cout << "�� �ܰ� �ְ�:		" << max << endl;

	cout << "\n-------������Ȳ------" << endl;
	cout << "---------------------" << endl;
	for (int i = 0;i < nCurrentAccountNum;i++)
		cout << pAcctArray[i].getAccountName() << "	" << i + nMaxAccountNum << "	" << pAcctArray[i].getBalance() << endl;
}

void  ATMachine::managerMode()
{
	int result;
	string password;
	cout << "------- ���� ------\n" << endl;
	cout << "������ ��й�ȣ �Է�: ";
	cin >> password;
	result = isManager(password);
	if (result == true)
	{
		cout << "�������Դϴ�.\n" << endl;
		displayReport();
	}
	else cout << "������ ��й�ȣ Ʋ�Ƚ��ϴ�. ó������ ���ư��ϴ�.\n" << endl;

		
}
ATMachine:: ~ATMachine()
{
	delete[]pAcctArray;
}