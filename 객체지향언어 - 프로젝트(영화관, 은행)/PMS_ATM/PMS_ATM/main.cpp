#include <iostream>
#include "Account.h"
#include "ATMachine.h"
#include "Statistics.h"


using namespace std;

int main(void)
{
	int select;

	ATMachine atm(100, 50000, "admin");

	while (1)
	{
		atm.displayMenu();
		cout << "메뉴를 선택하세요:";
		cin >> select;
		cout << endl;

		switch (select)
		{
		case 1:
			atm.createAccount();
			break;

		case 2:
			atm.checkMoney();
			break;
		case 3:
			atm.depositMoney();
			break;
		case 4:
			atm.widrawMoney();
			break;
		case 5:
			atm.transfer();
			break;
		case 6:
			atm.managerMode();
			break;
		case 9:
			atm. ~ATMachine();
			break;

		default:
			cout << "번호 확인 후 다시 입력하세요." << endl;
		}

		if (select == 9)
		{
			cout << "안녕히 가세요" << endl;
			break;
		}

	}
	return 0;
}