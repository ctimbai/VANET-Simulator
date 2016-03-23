//#include "stdafx.h"
#include <stdlib.h>

#include <cassert>
#include "RdmCtr.h"


// --------------------------------------
RdmCtr::RdmCtr(unsigned long s)
{
	srand((unsigned)time(NULL));
	if(s == 0)
		m_lSeed = (unsigned long)time(NULL);
	else
		m_lSeed = s;
}

unsigned int RdmCtr::GetRdmIntNum( unsigned int nMinNum, unsigned int nMaxNum)
{
	assert( nMaxNum >= nMinNum );
	if (nMaxNum < nMinNum)
		return -1;

	unsigned int nRet = Random(nMaxNum-nMinNum+1) + nMinNum;
	return nRet;
}

double RdmCtr::GetRdmRealNum( double dMinNum, double dMaxNum)
{
	assert( dMaxNum >= dMinNum );
	if (dMaxNum < dMinNum)
		return -1.0;

	double dLen = dMaxNum - dMinNum;
	double dRet = fRandom()*dLen + dMinNum;
	return dRet;
}

unsigned int RdmCtr::GetRdmIntNumNotEqual(unsigned int nMinNum, unsigned int nMaxNum)
{
	int max = nMaxNum - nMinNum + 1;
	int bigend = ((1 + max) * max) / 2;

	int x = rand()% bigend;
	//cout << x << endl;
	//int x = nR * bigend;
	//cout << x << endl;
	int sum = 0;
	for (int i = 0; i < max; i ++) {
		sum += (max - i);
		if (sum > x) 
			return i;
	}
	return -1;
}

// ---------------------------------------------------------------------------- :
// 产生[0 ~ n-1)整数
unsigned int RdmCtr::Random( unsigned long n )
{
	m_lSeed = multiplier * m_lSeed + adder;
	return (unsigned int)((m_lSeed) % n);
}

// 产生[0, 1)实数
double RdmCtr::fRandom()
{
	return Random(maxshort) / double(maxshort);
}
// :~