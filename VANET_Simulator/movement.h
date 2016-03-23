#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "Node.h"
#include "Topology.h"
#include "NSMath.h"
#include "Log.h"
#include "BaseControl.h"
//#include "NSRunner.h"
#include "BaseDef.h"


#include <cassert>

class Movement 
{
public:
	Movement(double dmds = 0.0, double dmd = 0.0):m_dMoveDuration_Sec(dmds), m_dMoveDistance(dmd) {
		
	}

	~Movement() { }

// ---------------- 0. General Operations ----------------------
public:
	// Judge the node current position.
	int Get_Position_in_topo(double dLoc_x, double  dLoc_y);

	
private:
	// the duration for one moving.
	double m_dMoveDuration_Sec;
	double m_dMoveDistance;


	 

// -------------------1. Bus mobility(By Path) ------------------
public:
	// Bus move a step depends on current direction.
	void Bus_move_a_step_rely_on_curDirection(CBusNode *pBus, double dCurDirection, int nOverTime_ms,/* unsigned int nCrc, */Point *pCurPathBeginPoint, Point *pCurPathEndPoint);

	// Bus move a step depends on current direction and current path.
	void Bus_move_a_step_rely_on_curDirection_path(CBusNode *pBus, double dCurDirection, int nOverTime_ms, double dCurPathLength);

private:

// -------------------2. Car Mobility(RWALK) ------------------
public:

	//  Move a step forward over a certain interval.
	void Car_move_forward_overTimeSlot_RWALK( CCarNode* pCar, int nOverTime_ms );

	// Car move a step depends on current direction. for RWALK.
	void Car_move_a_step_rely_on_curDirection_RWALK(CCarNode *pCar, int nOverTime_ms);

	// Car move a step depends on current direction.
	void Car_move_a_step_rely_on_curDirection(CCarNode *pCar, double dCurDirection, int nOverTime_ms, unsigned int nC);
	
	// Adjust the car's coordinates, ensure them in the area of Topology.
	void Ensure_Car_within_Topo_range(double &dLoc_x, double &dLoc_y);
	
// ------------------------------------------------------------------
	// get the move duration.
	double Get_MoveDureation_Sec_RWALK();
	
	// Reset move duration.
	void Reset_MoveDuration_RAWALK();

	// 检查节点的当前位置并选择重置方向.
	// Check the MN's current position, maybe reset the direction depending on whether it reaches boundary or be bounced.
	void Check_Car_curPosition_maybe_reset_its_direction_RWALK( CCarNode* pCar );

private:

};
#endif//_MOVEMENT_H_