#ifndef _BASE_DEF_H_
#define _BASE_DEF_H_

#include "BaseControl.h"

// ================== Nodes' movement Def ===============

enum // movement models
{
	RWALK,		//Car 
	PATHBASED,  //Bus
	RWP,
	RDM
};

// =================== Topology Def ==================

// Node's position in the topology area.
enum 
{
	LEFT_BOUNDARY,
	TOP_BOUNDARY,
	RIGHT_BOUNDARY,
	BOTTOM_BOUNDARY,
	LEFT_BOTTOM_POINT,
	LEFT_TOP_POINT,
	RIGHT_TOP_POINT,
	RIGHT_BOTTOM_POINT,
	INSIDE_TOPO,
	OUTSIDE_TOPO
};

// typedef enum 
// {
// 	LEFT_BOTTOM_POINT,
// 	LEFT_TOP_POINT,
// 	RIGHT_TOP_POINT,
// 	RIGHT_BOTTOM_POINT,
// }TA;



// ===================== BufferAllocation case settings==============

enum
{
	Knapsack_allocation_by_DynamicProgram,
	In_ascending_order_of_size_by_Greedy,		  
	In_ascending_order_of_formula_by_Greedy,
	Random_allocation,
	In_descending_order_of_size_by_Greedy,
	In_descending_order_of_formula_by_Greedy,
	Heuristic_allocation
};

// ===================== Resource settings ========================

// defines the type of resource(list)
#define RES_NUM 10

//#define BUS_STOP 10

#define MAXN 100
#define MAXC 1000


#define randomInt(x) (rand()%x)

// Zipf分布的参数
const double dPZipf = 0.66;


// ===================== Simulator Running settings ================

const double PI = 3.1415926;

// NS running states.
enum
{
	NS_RUNS_OVER,
	NS_RUNS_NOT_OVER
};


// ===================== Other Basic defines ====================

// parameters' types of a function
#define  _in  // in param
#define  _out // out param

// Delete a Ptr-Object operation.
#define SAFELY_DELETE_PTR( pX )	\
{								\
	if (NULL != pX)				\
{							\
	delete pX;				\
	pX = NULL;				\
	}							\
	}


#endif//_BASE_DEF_H_