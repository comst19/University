#include <iostream>
#include <string>

#include "Pay.h"

using namespace std;

int CardPay::charge(int amount)
{
	int num;
	string name;
	cout << "	[ �ſ�ī�� ���� ]" << endl;
	cout << "ī�� ��ȣ �Է�(12�ڸ���) : ";
	cin >> num;
	cout << "�̸� : ";
	cin >> name;
	cout << "�ſ�ī�� ������ �Ϸ�Ǿ����ϴ�. : ";

	return amount + amount*interest;
}

int BankTransfer::charge(int amount)
{
	int num;
	string name;
	cout << "	[ KPU ���� ���� ]" << endl;
	cout << "���� ��ȣ �Է�(12�ڸ���) : ";
	cin >> num;
	cout << "�̸� : ";
	cin >> name;
	cout << "KPU ���� ������ �Ϸ�Ǿ����ϴ�. : ";

	return amount + amount*interest;
}

int MobilePay::charge(int amount)
{
	int num;
	string name;
	cout << "	[ ����� ���� ]" << endl;
	cout << "�ڵ��� ��ȣ �Է�(11�ڸ���) : ";
	cin >> num;
	cout << "�̸� : ";
	cin >> name;
	
	cout << "����� ������ �Ϸ�Ǿ����ϴ�. : ";
	return amount + amount*interest;
}