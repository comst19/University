#include <iostream>
#include <string>

#include "Screen.h"
#include "Pay.h"

using namespace std;


Screen::Screen(string name, int price, int r, int c)
{
	strMovieName = name;
	nRowMax = r;
	nColMax = c;
	nTicketPrice = price;
	nCurrentReservedId = 99;
	pSeatArray = new Ticket*[nRowMax];
	for (int r = 0; r< nRowMax; r++)
	{
		pSeatArray[r] = new Ticket[nColMax];
	}

	for (int i = 0; i< nRowMax; i++)
	{
		for (int j = 0; j< nColMax; j++)
		{
			pSeatArray[i][j].setCheck(SEAT_EMPTY_MARK);
		}
	}
}

void Screen::showMovieMenu()
{
	int choose = 0;
	cout << "---------------------------------------" << endl;
	cout << "	영화 메뉴 - " << strMovieName << endl;
	cout << "---------------------------------------" << endl;
	cout << " 1. 상영 영화 정보" << endl;
	cout << " 2. 좌석 예약 현황" << endl;
	cout << " 3. 예약 하기" << endl;
	cout << " 4. 예약 취소" << endl;
	cout << " 5. 결제 하기" << endl;
	cout << " 7. 메인 메뉴 이동" << endl;
	cout << "\n";
}

void Screen::showSeatMap()
{
	cout << "		[ 좌석 예약 현황 ]" << endl;
	cout << "	";

	for (int i = 1;i <= nRowMax;i++)
	{
		cout << "[" << i << "] ";
	}
	cout << "\n";

	for (int i = 1;i <= nRowMax;i++)
	{
		cout << "[" << i << "]	";
		for (int j = 0; j < nColMax;j++)
		{
			cout << "[" << pSeatArray[i - 1][j].getCheck() << "] ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void Screen::reserveTicket()
{
	int row;
	int col;
	cout << "  [ 좌석 예약 ]" << endl;
	cout << "좌석 행 번호 입력(1 - " << nRowMax << ") : ";
	cin >> row;
	cout << "좌석 열 번호 입력(1 - " << nColMax << ") : ";
	cin >> col;
	if (pSeatArray[row - 1][col - 1].getCheck() == SEAT_EMPTY_MARK)
	{
		nCurrentReservedId++;
		pSeatArray[row - 1][col - 1].setSeat(row, col);
		pSeatArray[row - 1][col - 1].setReservedID(nCurrentReservedId);
		pSeatArray[row - 1][col - 1].setCheck(SEAT_RESERVED_MARK);
		cout << "행[" << row << "] 열[" << col << "] " << nCurrentReservedId << " 예약 번호로 접수되었습니다." << endl;
	}

	else if (pSeatArray[row][col].getCheck() == SEAT_RESERVED_MARK)
		cout << "이미 예약된 자리입니다." << endl;

	else if (nRowMax < row || row < 1) cout << "없는 자리입니다." << endl;

	else if (nColMax < col || col < 1) cout << "없는 자리입니다." << endl;

	else
		cout << "이미 결제 완료된 자리입니다." << endl;
	cout << "\n";
}

void Screen::cancelReservation()
{
	int id;
	Ticket* pseat_id;
	cout << "  [ 좌석 예약 취소 ]" << endl;
	cout << "예약 번호 입력 : ";
	cin >> id;


	pseat_id = checkReservedID(id);

	if (pseat_id != NULL)
	{
		cout << id << " 예약 번호가 취소 처리되었습니다.\n" << endl;
		pseat_id->setCheck(SEAT_EMPTY_MARK);
	}
	else
		cout << "예약 번호가 틀렸습니다.\n" << endl;
}

Ticket* Screen::checkReservedID(int id)
{
	Ticket **tmp = pSeatArray;

	for (int i = 0;i < nRowMax;i++)
	{
		for (int j = 0;j<nColMax;j++)
			if (tmp[i][j].getReservedID() == id) return tmp[i] + j;
	}

	return NULL;
}

void Screen::Payment()
{
	int id;
	Ticket* pseat_id;
	cout << "  [ 좌석 예약 결제 ]" << endl;
	cout << "예약 번호 입력 : ";
	cin >> id;

	if (id <= nCurrentReservedId && 100 <= id)
	{
		pseat_id = checkReservedID(id);

		if (pseat_id->getCheck() == SEAT_EMPTY_MARK) cout << "예약된 자리가 아닙니다.\n" << endl;

		else if (pseat_id->getCheck() == SEAT_COMPLETION_MARK) cout << "이미 결제된 자리입니다.\n" << endl;

		else
		{
			int method;
			int price;
			Pay* pay;
			cout << "---------------------------------------" << endl;
			cout << "	결제 방식 선택" << endl;
			cout << "---------------------------------------" << endl;
			cout << " 1. 모바일 결제" << endl;
			cout << " 2. 은행 이체 결제" << endl;
			cout << " 3. 카드 결제\n" << endl;
			cout << " 결제 방식(1~3) : ";
			cin >> method;

			pseat_id->setPayMethod(method);

			switch (method)
			{
			case MOBILE_PHONE_PAYMENT:
				pay = new MobilePay(MOBILE_PHONE_INTEREST_RATE);
				break;

			case BANK_TRANSFER_PAYMENT:
				pay = new BankTransfer(BANK_TRANSFER_INTEREST_RATE);
				break;

			case CREDIT_CARD_PAYMENT:
				pay = new CardPay(CREDIT_CARD_INTEREST_RATE);
				break;
			}

			pseat_id->setPayAmount(pay->charge(nTicketPrice));
			pseat_id->setCheck(SEAT_COMPLETION_MARK);
			cout << pseat_id->getPayAmount() << "\n" << endl;
		}
	}

	else cout << "틀린 예약 번호 입니다.\n" << endl;
}

void EuropeScreen::showMovieInfo()
{
	cout << "---------------------------------------" << endl;
	cout << "	[ " << strMovieName << " ]" << endl;
	cout << "---------------------------------------" << endl;
	cout << " 영화관 : 유럽영화 1관" << endl;
	cout << " 주인공 : 에단 호크, 홀리 델파" << endl;
	cout << " 줄거리 : 제시와 셀린느는 유럽 횡단 열차안에서 우연히..." << endl;
	cout << "\n 가격 : " << nTicketPrice << "\n" << endl;
}

void AsiaScreen::showMovieInfo()
{
	cout << "---------------------------------------" << endl;
	cout << "	[ " << strMovieName << " ]" << endl;
	cout << "---------------------------------------" << endl;
	cout << " 영화관 : 아시아영화 2관" << endl;
	cout << " 주인공 : 장국영, 공리" << endl;
	cout << " 줄거리 : 어렸을 때부터 함께 경극을 해온 두지와 시투..." << endl;
	cout << "\n 가격 : " << nTicketPrice << "\n" << endl;
}

void PremiumScreen::showMovieInfo()
{
	cout << "---------------------------------------" << endl;
	cout << "	[ " << strMovieName << " ]" << endl;
	cout << "---------------------------------------" << endl;
	cout << " 영화관 : 프리미엄 3관" << endl;
	cout << " 주인공 : 다니엘 래드클리프" << endl;
	cout << " 줄거리 : 인권운동가 팀과 스티븐은 억울한 판결로 투옥된다..." << endl;
	cout << "\n 가격 : " << nTicketPrice << "\n" << endl;
}

Screen::~Screen()
{
	for (int i = 0; i < nRowMax; i++)
	{
		delete[] pSeatArray[i];
	}
	delete[] pSeatArray;
}

