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
	cout << "	��ȭ �޴� - " << strMovieName << endl;
	cout << "---------------------------------------" << endl;
	cout << " 1. �� ��ȭ ����" << endl;
	cout << " 2. �¼� ���� ��Ȳ" << endl;
	cout << " 3. ���� �ϱ�" << endl;
	cout << " 4. ���� ���" << endl;
	cout << " 5. ���� �ϱ�" << endl;
	cout << " 7. ���� �޴� �̵�" << endl;
	cout << "\n";
}

void Screen::showSeatMap()
{
	cout << "		[ �¼� ���� ��Ȳ ]" << endl;
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
	cout << "  [ �¼� ���� ]" << endl;
	cout << "�¼� �� ��ȣ �Է�(1 - " << nRowMax << ") : ";
	cin >> row;
	cout << "�¼� �� ��ȣ �Է�(1 - " << nColMax << ") : ";
	cin >> col;
	if (pSeatArray[row - 1][col - 1].getCheck() == SEAT_EMPTY_MARK)
	{
		nCurrentReservedId++;
		pSeatArray[row - 1][col - 1].setSeat(row, col);
		pSeatArray[row - 1][col - 1].setReservedID(nCurrentReservedId);
		pSeatArray[row - 1][col - 1].setCheck(SEAT_RESERVED_MARK);
		cout << "��[" << row << "] ��[" << col << "] " << nCurrentReservedId << " ���� ��ȣ�� �����Ǿ����ϴ�." << endl;
	}

	else if (pSeatArray[row][col].getCheck() == SEAT_RESERVED_MARK)
		cout << "�̹� ����� �ڸ��Դϴ�." << endl;

	else if (nRowMax < row || row < 1) cout << "���� �ڸ��Դϴ�." << endl;

	else if (nColMax < col || col < 1) cout << "���� �ڸ��Դϴ�." << endl;

	else
		cout << "�̹� ���� �Ϸ�� �ڸ��Դϴ�." << endl;
	cout << "\n";
}

void Screen::cancelReservation()
{
	int id;
	Ticket* pseat_id;
	cout << "  [ �¼� ���� ��� ]" << endl;
	cout << "���� ��ȣ �Է� : ";
	cin >> id;


	pseat_id = checkReservedID(id);

	if (pseat_id != NULL)
	{
		cout << id << " ���� ��ȣ�� ��� ó���Ǿ����ϴ�.\n" << endl;
		pseat_id->setCheck(SEAT_EMPTY_MARK);
	}
	else
		cout << "���� ��ȣ�� Ʋ�Ƚ��ϴ�.\n" << endl;
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
	cout << "  [ �¼� ���� ���� ]" << endl;
	cout << "���� ��ȣ �Է� : ";
	cin >> id;

	if (id <= nCurrentReservedId && 100 <= id)
	{
		pseat_id = checkReservedID(id);

		if (pseat_id->getCheck() == SEAT_EMPTY_MARK) cout << "����� �ڸ��� �ƴմϴ�.\n" << endl;

		else if (pseat_id->getCheck() == SEAT_COMPLETION_MARK) cout << "�̹� ������ �ڸ��Դϴ�.\n" << endl;

		else
		{
			int method;
			int price;
			Pay* pay;
			cout << "---------------------------------------" << endl;
			cout << "	���� ��� ����" << endl;
			cout << "---------------------------------------" << endl;
			cout << " 1. ����� ����" << endl;
			cout << " 2. ���� ��ü ����" << endl;
			cout << " 3. ī�� ����\n" << endl;
			cout << " ���� ���(1~3) : ";
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

	else cout << "Ʋ�� ���� ��ȣ �Դϴ�.\n" << endl;
}

void EuropeScreen::showMovieInfo()
{
	cout << "---------------------------------------" << endl;
	cout << "	[ " << strMovieName << " ]" << endl;
	cout << "---------------------------------------" << endl;
	cout << " ��ȭ�� : ������ȭ 1��" << endl;
	cout << " ���ΰ� : ���� ȣũ, Ȧ�� ����" << endl;
	cout << " �ٰŸ� : ���ÿ� �������� ���� Ⱦ�� �����ȿ��� �쿬��..." << endl;
	cout << "\n ���� : " << nTicketPrice << "\n" << endl;
}

void AsiaScreen::showMovieInfo()
{
	cout << "---------------------------------------" << endl;
	cout << "	[ " << strMovieName << " ]" << endl;
	cout << "---------------------------------------" << endl;
	cout << " ��ȭ�� : �ƽþƿ�ȭ 2��" << endl;
	cout << " ���ΰ� : �屹��, ����" << endl;
	cout << " �ٰŸ� : ����� ������ �Բ� ����� �ؿ� ������ ����..." << endl;
	cout << "\n ���� : " << nTicketPrice << "\n" << endl;
}

void PremiumScreen::showMovieInfo()
{
	cout << "---------------------------------------" << endl;
	cout << "	[ " << strMovieName << " ]" << endl;
	cout << "---------------------------------------" << endl;
	cout << " ��ȭ�� : �����̾� 3��" << endl;
	cout << " ���ΰ� : �ٴϿ� ����Ŭ����" << endl;
	cout << " �ٰŸ� : �αǿ�� ���� ��Ƽ���� ����� �ǰ�� �����ȴ�..." << endl;
	cout << "\n ���� : " << nTicketPrice << "\n" << endl;
}

Screen::~Screen()
{
	for (int i = 0; i < nRowMax; i++)
	{
		delete[] pSeatArray[i];
	}
	delete[] pSeatArray;
}

