#include <iostream>
#include "Screen.h"
#include "TicketBox.h"
#include "Statistics.h"

using namespace std;

Screen* KpuTicketBox::selectMenu()
{
	int choose = 0;
	cout << "-----------------------------" << endl;
	cout << "   상영관 메인 메뉴" << endl;
	cout << "-----------------------------" << endl;
	cout << " 1.   유럽     영화 1관" << endl;
	cout << " 2.  아시아    영화 2관" << endl;
	cout << " 3. 프리미엄   영화 3관" << endl;
	cout << " 9.   통계      관리" << endl;
	cout << "\n 선택 (1~3) 그 외 종료 : ";
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

void KpuTicketBox::Initialize()		// 스크린 객체 생성
{
	// Screen(영화제목, 티켓가격, 좌석(nRowMax), 좌석(nColMax))
	pEuropeScreen = new EuropeScreen("비포 선 라이즈", 10000, 10, 10);
	pAsiaScreen = new AsiaScreen("패왕별희", 12000, 10, 10);
	pPremiumScreen = new PremiumScreen("프리즌 이스케이프", 30000, 6, 6);
}

void KpuTicketBox::Manage()
{
	string pwd;

	cout << "-----------------------------" << endl;
	cout << "   관리자 메뉴" << endl;
	cout << "-----------------------------" << endl;
	cout << " 관리자 비밀번호 입력 : ";
	cin >> pwd;
	cout << "\n";
	if (pwd == TICKETBOX_MANAGER_PWD)
	{
		int money = 0;
		int count = 0;
		Statistics stat;
		money = stat.totalSum(pEuropeScreen);
		cout << " 1. 유럽영화 상영관 결제금액 : ";
		cout << money << endl;
		money = stat.totalSum(pAsiaScreen);
		cout << " 2. 아시아영화 상영관 결제금액 : ";
		cout << money << endl;
		money = stat.totalSum(pPremiumScreen);
		cout << " 3. 프리미엄 상영관 결제금액 : ";
		cout << money << endl;

		count = count + stat.totalCount(pEuropeScreen);
		count = count + stat.totalCount(pAsiaScreen);
		count = count + stat.totalCount(pPremiumScreen);
		cout << " 4. 전체 티켓 판매량 : ";
		cout << count << endl;
		cout << "\n";
	}
	
	else cout << " 비밀번호가 틀렸습니다.\n" << endl;
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
