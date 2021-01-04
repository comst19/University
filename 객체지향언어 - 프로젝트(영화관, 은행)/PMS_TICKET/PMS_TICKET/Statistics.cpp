#include"Statistics.h"

int Statistics::totalSum(Screen* pScreen)
{
	int sum_money = 0;
	Ticket **pSeatArray = pScreen->getTicketArray();
	
	
	for (int i = 0; i < pScreen->getRowMax();i++)
	{
		for (int j = 0; j < pScreen->getColMax();j++)
		{
			if (pSeatArray[i][j].getCheck() == SEAT_COMPLETION_MARK)
				sum_money = sum_money + pSeatArray[i][j].getPayAmount();

		}
	}
	return sum_money;
}

int Statistics::totalCount(Screen* pScreen)
{
	int count = 0;
	Ticket **pSeatArray = pScreen->getTicketArray();

	for (int i = 0; i < pScreen->getRowMax();i++)
	{
		for (int j = 0; j < pScreen->getColMax();j++)
		{
			if (pSeatArray[i][j].getCheck() == SEAT_COMPLETION_MARK)
				count++;

		}
	}
	return count;
}