#include <map>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

//using namespace std;



//#include "BaseDef.h"
#include "BufferAllocation.h"



/*
// 0-1 knapsack allocation(Dynamic Programming)
std::vector<char> BufferAllocation::Buffer_01knacp_Allocation(std::vector<Resource> R)
{
	for (int i = 0; i <= RES_NUM; ++i) {
		for (int j = 0; j <= BUS_BUFFER; ++j) {
			mValue[i][j] = i == 0 ? 0 : mValue[i - 1][j];
			if (i > 0 && (j >= R[i-1].GetResSize()))
				mValue[i][j] = mValue[i - 1][j - R[i-1].GetResSize()] + R[i-1].GetResPop();
		}
	}
	double MaxPopValue = mValue[RES_NUM][BUS_BUFFER]; // calculate the resource with the max popularity.
	//return MaxPopValue;
	std::cout << "背包中最终所容纳的最大价值：" << MaxPopValue << std::endl;

	// get the satisfied item and output
	int j = BUS_BUFFER;
	// using the vector to hold the satisfied item.
	std::vector<char> vecChar;
	std::vector<char>::iterator it;
	for(int i = RES_NUM; i > 0; --i){
		if(mValue[i][j] > mValue[i-1][j]){
			vecChar.push_back(R[i-1].GetResType());
			//++ nCount;
			j = j - R[i-1].GetResSize();
		}
	}
	sort(vecChar.begin(), vecChar.end());
	return vecChar;
}
*/

std::vector<Resource *> BufferAllocation::Buffer_01knacp_Allocation(std::vector<Resource *> R)
{
	//int value[MAXN], weight[MAXN];
	double mValue[MAXN][MAXC] = {0};

	for (int i = 0; i <= RES_NUM; ++i) {
		for (int j = 0; j <= BUS_BUFFER; ++j) {
			mValue[i][j] = i == 0 ? 0 : mValue[i - 1][j];
			if (i > 0 && j >= R[i-1]->GetResSize())
				mValue[i][j] = mValue[i - 1][j - R[i-1]->GetResSize()] + R[i-1]->GetResPop();
		}
	}
	double MaxPopValue = mValue[RES_NUM][BUS_BUFFER]; // calculate the resource with the max popularity.
	//return MaxPopValue;
	//std::cout << "背包中最终所容纳的最大价值：" << MaxPopValue << std::endl;

	// get the satisfied item and output
	int j = BUS_BUFFER;
	// using the vector to hold the satisfied item.
	std::vector<Resource *> vecResRet;
	std::vector<char>::iterator it;
	for(int i = RES_NUM; i > 0; --i){
		if(mValue[i][j] > mValue[i-1][j]){
			vecResRet.push_back(R[i-1]);
			//++ nCount;
			j = j - R[i-1]->GetResSize();
		}
	}
	//sort(vecChar.begin(), vecChar.end());
	return vecResRet;
}

/*
//In_descending_order_of_size_by_Greedy,
std::vector<char> BufferAllocation::Buffer_IdosbG_Allocation(std::vector<Resource> R)
{
	std::vector<unsigned int> vecSize;
	std::vector<unsigned int>::iterator itS;
	std::vector<unsigned int> vecResort;
	std::vector<unsigned int>::iterator itRt;
	std::vector<char> vecRet;
	std::vector<Resource>::iterator itR;
	for (itR = R.begin(); itR != R.end(); ++ itR)
		vecSize.push_back((*itR).GetResSize());
	NSMath::BubbleSort_Int(vecSize);
	int nCount = 0;
	for (itS = vecSize.begin(); itS != vecSize.end(); ++ itS) {
		nCount += *itS;
		if(nCount <= BUS_BUFFER) {
			vecResort.push_back(*itS);
		}
	}

	itR = R.begin();
	itRt = vecResort.begin();
	for(; itRt != vecResort.end(); ++ itRt){
		for (; itR != R.end(); ++ itR) {
			if ((*itRt == ((*itR).GetResSize())) && CompareVector((*itR).GetResType(), vecRet)) {
				vecRet.push_back((*itR).GetResType());
				break;
			}
		}
	}
	return vecRet;
}
*/



// 按照资源大小从小到大排序
std::vector<Resource *> BufferAllocation::Buffer_IdosbG_Allocation(std::vector<Resource *> R)
{
	std::vector<Resource *>::iterator itR;

	std::vector<unsigned int> vecSize;
	std::vector<unsigned int>::iterator itS;

	std::vector<Resource *> vecRet;
	std::vector<Resource *>::iterator itRet;


	// 对资源进行排序
	sort( R.begin(), R.end(), NSMath::CmpResWithSize_FromBigToLittle);

	unsigned int nCount = 0;

	for (itR = R.begin(); itR != R.end(); ++ itR) {
		unsigned int nSize = (*itR)->GetResSize();
		nCount += nSize;
		if (nCount <= BUS_BUFFER) {
			vecRet.push_back(*itR);
		}
	}

	return vecRet;
}

/*

//In_ascending_order_of_size_by_Greedy,
std::vector<char> BufferAllocation::Buffer_IaosbG_Allocation(std::vector<Resource> R)
{
	std::vector<unsigned int> vecSize;
	std::vector<unsigned int>::iterator itS;
	std::vector<unsigned int> vecResort;
	std::vector<unsigned int>::iterator itRt;
	std::vector<char> vecRet;
	std::vector<Resource>::iterator itR;
	for (itR = R.begin(); itR != R.end(); ++ itR)
		vecSize.push_back((*itR).GetResSize());
	NSMath::BubbleSort1_Int(vecSize);
	unsigned int nCount = 0;
	for (itS = vecSize.begin(); itS != vecSize.end(); ++ itS) {
		if(nCount >= BUS_BUFFER)
			break;
		vecResort.push_back(*itS);
		nCount += *itS;
	}
	itR = R.begin();
	itRt = vecResort.begin();
	for(; itRt != vecResort.end(); ++ itRt){
		for (; itR != R.end(); ++ itR) {
			if ((*itRt == ((*itR).GetResSize())) && CompareVector((*itR).GetResType(), vecRet)) {
				vecRet.push_back((*itR).GetResType());
				break;
			}
		}
	}
	return vecRet;
}
*/
// 按照资源大小从小到大排序
std::vector<Resource *> BufferAllocation::Buffer_IaosbG_Allocation(std::vector<Resource *> R)
{
	std::vector<Resource *>::iterator itR;

	std::vector<unsigned int> vecSize;
	std::vector<unsigned int>::iterator itS;

	std::vector<Resource *> vecRet;
	std::vector<Resource *>::iterator itRet;


	// 对资源进行排序
	sort(R.begin(), R.end(), NSMath::CmpResWithSize_FromLittleToBig);

	unsigned int nCount = 0;

	for (itR = R.begin(); itR != R.end(); ++ itR) {
		unsigned int nSize = (*itR)->GetResSize();
		nCount += nSize;
		if (nCount <= BUS_BUFFER) {
			vecRet.push_back(*itR);
		}
	}

	return vecRet;
}


/*
//In_descending_order_of_formula_by_Greedy,(pd/s)
std::vector<char> BufferAllocation::Buffer_IdofbG_Allocation(std::vector<Resource> R)
{
	std::map<char, double> mapFor;
	std::vector<char> vecRet;
	std::map<char, double>::iterator itM;
	std::vector<Resource>::iterator itR;
	for (itR = R.begin(); itR != R.end(); ++ itR) {
		double d_pds = (((*itR).GetResPop())*((*itR).GetResTime())) / (double)((*itR).GetResSize());
		mapFor.insert(make_pair((*itR).GetResType()), d_pds); //map<char, pd/s>
	}
	std::vector<double> vecD;
	std::vector<double>::iterator itD;
	for (itM = mapFor.begin(); itM != mapFor.end(); ++ itM) {
		vecD.push_back((*itM)->second);
	}
	NSMath::BubbleSort_Double(vecD);
	//get the type by pd/s
	std::vector<char> vecB;
	std::vector<char>::iterator itB;
	for(itD = vecD.begin(); itD != vecD.end(); ++ itD) {
		for (itM = mapFor.begin(); itM != mapFor.end(); ++ itM) {
			if (*itD == ((*itM)->second)){
				vecB.push_back((*itM)->first);
				break;
			}
		}
	}
	//get the size by type;
	std::vector<unsigned int> vecSize;
	std::vector<unsigned int>::iterator itS;
	for (itB = vecB.begin(); itB != vecB.end(); ++ itB) {
		for (itR = R.begin(); itR != R.end(); ++ itR) {
			if (*itB == ((*itR).GetResType())) {
				vecSize.push_back((*itR).GetResSize());
				break;
			}
		}
	}
	//from little to big on bus;
	unsigned int nCount = 0;
	std::vector<unsigned int> vecResort;
	std::vector<unsigned int>::iterator itRt;
	for (itS = vecSize.begin(); itS != vecSize.end(); ++ itS) {
		if(nCount >= BUS_BUFFER)
			break;
		vecResort.push_back(*itS);
		nCount += *itS;
	}

	for(itRt = vecResort.begin(); itRt != vecResort.end(); ++ itRt){
		for (itR = R.begin(); itR != R.end(); ++ itR) {
			if ((*itRt == ((*itR).GetResSize())) && CompareVector((*itR).GetResType(), vecRet)) {
				vecRet.push_back((*itR).GetResType());
				break;
			}
		}
	}
	return vecRet;
}
*/

//In_descending_order_of_formula_by_Greedy,(pd/s)
std::vector<Resource *> BufferAllocation::Buffer_IdofbG_Allocation(std::vector<Resource *> R)
{
	std::vector<Resource *>::iterator itR;

	std::vector<unsigned int> vecSize;
	std::vector<unsigned int>::iterator itS;

	std::vector<Resource *> vecRet;
	std::vector<Resource *>::iterator itRet;


	// 对资源进行从小到大排序
	sort(R.begin(), R.end(), NSMath::CmpResWithFomu_FromBigToLittle);

	unsigned int nCount = 0;

	for (itR = R.begin(); itR != R.end(); ++ itR) {
		unsigned int nSize = (*itR)->GetResSize();
		nCount += nSize;
		if (nCount <= BUS_BUFFER) {
			vecRet.push_back(*itR);
		}
	}
	return vecRet;
}


//In_ascending_order_of_formula_by_Greedy,
std::vector<Resource *> BufferAllocation::Buffer_IaofbG_Allocation(std::vector<Resource *> R)
{
	std::vector<Resource *>::iterator itR;

	std::vector<unsigned int> vecSize;
	std::vector<unsigned int>::iterator itS;

	std::vector<Resource *> vecRet;
	std::vector<Resource *>::iterator itRet;


	// 对资源进行从大到小排序
	sort(R.begin(), R.end(), NSMath::CmpResWithFomu_FromLittleToBig);

	int nCount = 0;

	for (itR = R.begin(); itR != R.end(); ++ itR) {
		unsigned int nSize = (*itR)->GetResSize();
		nCount += nSize;
		if (nCount <= BUS_BUFFER) {
			vecRet.push_back(*itR);
		}
	}
	return vecRet;
}

/*
//In_ascending_order_of_formula_by_Greedy,
std::vector<char> BufferAllocation::Buffer_IaofbG_Allocation(std::vector<Resource> R)
{
	std::map<char, double> mapFor;
	std::vector<char> vecRet;
	std::map<char, double>::iterator itM;
	std::vector<Resource>::iterator itR;
	for (itR = R.begin(); itR != R.end(); ++ itR) {
		double d_pds = (((*itR).GetResPop())*((*itR).GetResTime())) / (double)((*itR).GetResSize());
		mapFor.insert(make_pair((*itR).GetResType()), d_pds); //map<char, pd/s>
	}
	std::vector<double> vecD;
	std::vector<double>::iterator itD;
	for (itM = mapFor.begin(); itM != mapFor.end(); ++ itM) {
		vecD.push_back((*itM)->second);
	}
	NSMath::BubbleSort1_Double(vecD);
	//get the type by pd/s
	std::vector<char> vecB;
	std::vector<char>::iterator itB;
	for(itD = vecD.begin(); itD != vecD.end(); ++ itD) {
		for (itM = mapFor.begin(); itM != mapFor.end(); ++ itM) {
			if (*itD == ((*itM)->second)){
				vecB.push_back((*itM)->first);
				break;
			}
		}
	}
	//get the size by type;
	std::vector<unsigned int> vecSize;
	std::vector<unsigned int>::iterator itS;
	for (itB = vecB.begin(); itB != vecB.end(); ++ itB) {
		for (itR = R.begin(); itR != R.end(); ++ itR) {
			if (*itB == ((*itR).GetResType())) {
				vecSize.push_back((*itR).GetResSize());
				break;
			}
		}
	}
	//from little to big on bus;
	unsigned int nCount = 0;
	std::vector<unsigned int> vecResort;
	std::vector<unsigned int>::iterator itRt;
	for (itS = vecSize.begin(); itS != vecSize.end(); ++ itS) {
		if(nCount >= BUS_BUFFER)
			break;
		vecResort.push_back(*itS);
		nCount += *itS;
	}

	for(itRt = vecResort.begin(); itRt != vecResort.end(); ++ itRt){
		for (itR = R.begin(); itR != R.end(); ++ itR) {
			if ((*itRt == ((*itR).GetResSize())) && CompareVector((*itR).GetResType(), vecRet)) {
				vecRet.push_back((*itR).GetResType());
				break;
			}
		}
	}
	return vecRet;
}
*/

//Random_allocation,
/*
std::vector<char> BufferAllocation::Buffer_Random_Allocation(std::vector<Resource> R)
{
	
}
*/

std::vector<Resource *> BufferAllocation::Buffer_Random_Allocation(std::vector<Resource *> R, RdmCtr *pObjRC)
{
	std::vector<Resource *>::iterator itR;

	std::vector<unsigned int> vecSize;
	std::vector<unsigned int>::iterator itS;

	std::vector<Resource *> vecRet;
	std::vector<Resource *>::iterator itRet;


	std::vector<int> vecRandom;
	std::vector<int>::iterator itRand;


	// 对资源进行从大到小排序
	//sort(R.begin(), R.end(), CmpResWithSize_FromBigToLittle);
	int index = pObjRC->GetRdmIntNum(0, RES_NUM - 1);
	vecRandom.push_back(index);
	
	vecRet.push_back(R[index]);

	unsigned int nCount = R[index]->GetResSize();

	for (int i = 0; i < RES_NUM + 10; i ++) {

		//srand((int)time(0));

		index = pObjRC->GetRdmIntNum(0, RES_NUM - 1);

		itRand = find(vecRandom.begin(), vecRandom.end(), index);
		if (itRand != vecRandom.end()) { //找到了
			continue;
		}	
		else { //没有找到
			vecRandom.push_back(index);
			unsigned int nSize = R[index]->GetResSize();
			nCount += nSize;
			if (nCount <= BUS_BUFFER) {
				vecRet.push_back(R[index]); //!!!
			}
			else {
				break;
			}
		}
	}
	return vecRet;
}

bool BufferAllocation::CompareVector(char type, std::vector<char> v)
{
	std::vector<char>::iterator it;
	for (it = v.begin(); it != v.end(); ++ it)
		if (type == *it)
			return false;
	return true;
}


