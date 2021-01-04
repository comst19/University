#ifndef STATISTCIS_H

#include "Account.h"
#include "ATMachine.h"
#include <string>
using std::string;

#define STATISTCIS_H

class Statistics
{

public:
	int sum(Account* pArray, int size);
	int average(Account* pArray, int size);
	int max(Account* pArray, int size);
};

#endif