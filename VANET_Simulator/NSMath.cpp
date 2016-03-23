#include "NSMath.h"
#include <cassert>


double NSMath::EuclidDistance( _in double x1, _in double y1, _in double x2, _in double y2 )
{
	double dDist = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
	return dDist;
}

// 计算两个点之间的夹角
double NSMath::ArcTanTwoPoint(_in double x1, _in double y1, _in double x2, _in double y2)
{
	double yM = (y2 - y1);
	double yD = (x2 - x1);

	double dArcTan = atan2(yM, yD);

	return dArcTan;
}

//BubbleSort (override)!!!
void NSMath::BubbleSort1_Double( _out std::vector<double> &vecD )
{
	int nLen = (int)vecD.size();
	for ( int j = nLen - 1; j >0; j-- )
	{
		for ( int i = 0; i < j; i++ )
		{
			if ( vecD[i] < vecD[i+1] )
			{
				double dT = vecD[i];
				vecD[i] = vecD[i+1];
				vecD[i+1] = dT;
			}
		}
	}
}

void NSMath::BubbleSort_Double( _out std::vector<double> &vecD )
{
	int nLen = (int)vecD.size();
	for ( int j = nLen - 1; j >0; j-- )
	{
		for ( int i = 0; i < j; i++ )
		{
			if ( vecD[i] > vecD[i+1] )
			{
				double dT = vecD[i];
				vecD[i] = vecD[i+1];
				vecD[i+1] = dT;
			}
		}
	}
}

//big->little
void NSMath::BubbleSort1_Int( _out std::vector<int> &vecInt )
{
	int nLen = (int)vecInt.size();
	for ( int j = nLen - 1; j >0; j-- )
	{
		for ( int i = 0; i < j; i++ )
		{
			if ( vecInt[i] < vecInt[i+1] )
			{
				int nT = vecInt[i];
				vecInt[i] = vecInt[i+1];
				vecInt[i+1] = nT;
			}
		}
	}
}
//little->big
void NSMath::BubbleSort_Int( _out std::vector<int> &vecInt )
{
	int nLen = (int)vecInt.size();
	for ( int j = nLen - 1; j >0; j-- )
	{
		for ( int i = 0; i < j; i++ )
		{
			if ( vecInt[i] > vecInt[i+1] )
			{
				int nT = vecInt[i];
				vecInt[i] = vecInt[i+1];
				vecInt[i+1] = nT;
			}
		}
	}
}

bool NSMath::CmpResWithSize_FromLittleToBig(Resource *res1, Resource *res2)
{
	return res1->GetResSize() < res2->GetResSize();
}


bool NSMath::CmpResWithSize_FromBigToLittle(Resource *res1, Resource *res2)
{
	return res1->GetResSize() > res2->GetResSize();
}

//按照公式推出的值从小到大排序
bool NSMath::CmpResWithFomu_FromLittleToBig(Resource *res1,Resource *res2)
{
	double dPop1 = res1->GetResPop();
	double dTime1 = res1->GetResTime();
	unsigned int nSize1 = res1->GetResSize();

	double pds1 = dPop1 * dTime1 / (double)nSize1;

	double dPop2 = res2->GetResPop();
	double dTime2 = res2->GetResTime();
	unsigned int nSize2 = res2->GetResSize();

	double pds2 = dPop2 * dTime2 / (double)nSize2;

	return pds1 > pds2;
}

//按照公式推出的值从大到小排序
bool NSMath::CmpResWithFomu_FromBigToLittle(Resource *res1,Resource *res2)
{
	double dPop1 = res1->GetResPop();
	double dTime1 = res1->GetResTime();
	unsigned int nSize1 = res1->GetResSize();

	double pds1 = dPop1 * dTime1 / (double)nSize1;

	double dPop2 = res2->GetResPop();
	double dTime2 = res2->GetResTime();
	unsigned int nSize2 = res2->GetResSize();

	double pds2 = dPop2 * dTime2 / (double)nSize2;

	return pds1 < pds2;
}
