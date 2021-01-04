#include <iostream>
#include <string>

#include "Pay.h"

using namespace std;

int CardPay::charge(int amount)
{
	int num;
	string name;
	cout << "	[ 신용카드 결제 ]" << endl;
	cout << "카드 번호 입력(12자리수) : ";
	cin >> num;
	cout << "이름 : ";
	cin >> name;
	cout << "신용카드 결제가 완료되었습니다. : ";

	return amount + amount*interest;
}

int BankTransfer::charge(int amount)
{
	int num;
	string name;
	cout << "	[ KPU 은행 결제 ]" << endl;
	cout << "은행 번호 입력(12자리수) : ";
	cin >> num;
	cout << "이름 : ";
	cin >> name;
	cout << "KPU 은행 결제가 완료되었습니다. : ";

	return amount + amount*interest;
}

int MobilePay::charge(int amount)
{
	int num;
	string name;
	cout << "	[ 모바일 결제 ]" << endl;
	cout << "핸드폰 번호 입력(11자리수) : ";
	cin >> num;
	cout << "이름 : ";
	cin >> name;
	
	cout << "모바일 결제가 완료되었습니다. : ";
	return amount + amount*interest;
}