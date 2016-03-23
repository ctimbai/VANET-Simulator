#ifndef _BUFFER_ALLOCATION_H_
#define _BUFFER_ALLOCATION_H_

#include "BaseDef.h"
#include "Resource.h"
#include "NSMath.h"
#include "RdmCtr.h"
#include "BaseControl.h"

#include <vector>
#include <ctime>

class BufferAllocation 
{

public:
	BufferAllocation() {}
	~BufferAllocation(){}


public:
	// 0-1 knapsack allocation(Dynamic Programming)
	std::vector<char> Buffer_01knacp_Allocation(std::vector<Resource> R);
	std::vector<Resource *> Buffer_01knacp_Allocation(std::vector<Resource *> R);

	//In_descending_order_of_size_by_Greedy,
	std::vector<char> Buffer_IdosbG_Allocation(std::vector<Resource> R);
	std::vector<Resource *> Buffer_IdosbG_Allocation(std::vector<Resource *> R);

	//In_ascending_order_of_size_by_Greedy,
	std::vector<char> Buffer_IaosbG_Allocation(std::vector<Resource> R);
	std::vector<Resource *> Buffer_IaosbG_Allocation(std::vector<Resource *> R);

	//In_descending_order_of_formula_by_Greedy,
	std::vector<char> Buffer_IdofbG_Allocation(std::vector<Resource> R);
	std::vector<Resource *> Buffer_IdofbG_Allocation(std::vector<Resource *> R);

	//In_ascending_order_of_formula_by_Greedy,
	std::vector<char> Buffer_IaofbG_Allocation(std::vector<Resource> R);
	std::vector<Resource *> Buffer_IaofbG_Allocation(std::vector<Resource *> R);

	//Random_allocation,
	std::vector<char> Buffer_Random_Allocation(std::vector<Resource> R);
	std::vector<Resource *> Buffer_Random_Allocation(std::vector<Resource *> R, RdmCtr *pObjRC);
	// heuristic allocation

public:
	bool CompareVector(char type, std::vector<char> v);

	
//	std::vector<Resource *> Get_All_Resource(int resNum);

// private:
// 	RdmCtr *m_pObjRC;

};
#endif//_BUFFER_ALLOCATION_H_