#include <iostream>
#include "Screen.h"
#include "TicketBox.h"
#include "Statistics.h"

using namespace std;

Screen* KpuTicketBox::selectMenu()
{
	int choose = 0;
	cout << "-----------------------------" << endl;
	cout << "   �󿵰� ���� �޴�" << endl;
	cout << "-----------------------------" << endl;
	cout << " 1.   ����     ��ȭ 1��" << endl;
	cout << " 2.  �ƽþ�    ��ȭ 2��" << endl;
	cout << " 3. �����̾�   ��ȭ 3��" << endl;
	cout << " 9.   ���      ����" << endl;
	cout << "\n ���� (1~3) �� �� ���� : ";
	cin >> choose;
	cout << endl;

	switch (choose)
	{
		case 1:
			return pEuropeScreen;

		case 2:
			return pAsiaScreen;

		case 3:
			return pPremiumScreen;
		
		case 9:
			Manage();
			return NULL;

		default:
			return NULL;
	}
}

void KpuTicketBox::Initialize()		// ��ũ�� ��ü ����
{
	// Screen(��ȭ����, Ƽ�ϰ���, �¼�(nRowMax), �¼�(nColMax))
	pEuropeScreen = new EuropeScreen("���� �� ������", 10000, 10, 10);
	pAsiaScreen = new AsiaScreen("�пպ���", 12000, 10, 10);
	pPremiumScreen = new PremiumScreen("������ �̽�������", 30000, 6, 6);
}

void KpuTicketBox::Manage()
{
	string pwd;

	cout << "-----------------------------" << endl;
	cout << "   ������ �޴�" << endl;
	cout << "-----------------------------" << endl;
	cout << " ������ ��й�ȣ �Է� : ";
	cin >> pwd;
	cout << "\n";
	if (pwd == TICKETBOX_MANAGER_PWD)
	{
		int money = 0;
		int count = 0;
		Statistics stat;
		money = stat.totalSum(pEuropeScreen);
		cout << " 1. ������ȭ �󿵰� �����ݾ� : ";
		cout << money << endl;
		money = stat.totalSum(pAsiaScreen);
		cout << " 2. �ƽþƿ�ȭ �󿵰� �����ݾ� : ";
		cout << money << endl;
		money = stat.totalSum(pPremiumScreen);
		cout << " 3. �����̾� �󿵰� �����ݾ� : ";
		cout << money << endl;

		count = count + stat.totalCount(pEuropeScreen);
		count = count + stat.totalCount(pAsiaScreen);
		count = count + stat.totalCount(pPremiumScreen);
		cout << " 4. ��ü Ƽ�� �Ǹŷ� : ";
		cout << count << endl;
		cout << "\n";
	}
	
	else cout << " ��й�ȣ�� Ʋ�Ƚ��ϴ�.\n" << endl;
}

KpuTicketBox::KpuTicketBox()
{
	pEuropeScreen = NULL;
	pAsiaScreen = NULL;
	pPremiumScreen = NULL;
}

KpuTicketBox::~KpuTicketBox()
{
	delete pEuropeScreen;
	delete pAsiaScreen;
	delete pPremiumScreen;
}
