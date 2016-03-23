#include "movement.h"


//unsigned int Movement::nCount_Record_Bus = 0;
//unsigned int Movement::nCount_Record_Car = 0;
// ---------------- 0. General Operations -----------------------------
// Judge the node current position.
int Movement::Get_Position_in_topo(double dLoc_x, double dLoc_y)
{
	double dTopoStartLoc_x = Topology::Get_Topo_start_loc_x();
	double dTopoStartLoc_y = Topology::Get_Topo_start_loc_y();
	double dTopo_max_x = dTopoStartLoc_x+Topology::Get_Topo_Width();
	double dTopo_max_y = dTopoStartLoc_y+Topology::Get_Topo_Height();

	// 1 in left_bottom_point
	if ( dLoc_x == dTopoStartLoc_x && dLoc_y == dTopoStartLoc_y )
		return LEFT_BOTTOM_POINT;

	// 2 in left_top_point
	else if ( dLoc_x == dTopoStartLoc_x && dLoc_y == dTopo_max_y )
		return LEFT_TOP_POINT;

	// 3 in right_top_point
	else if ( dLoc_x == dTopo_max_x && dLoc_y == dTopo_max_y )
		return RIGHT_TOP_POINT;

	// 4 in right_bottom_point
	else if ( dLoc_x == dTopo_max_x && dLoc_y == dTopoStartLoc_y )
		return RIGHT_BOTTOM_POINT;

	// 5 in bottom boundary
	else if ( (dLoc_x>dTopoStartLoc_x && dLoc_x<dTopo_max_x) && dLoc_y == dTopoStartLoc_y )
		return BOTTOM_BOUNDARY;

	// 6 in left boundary
	else if ( dLoc_x == dTopoStartLoc_x && (dLoc_y>dTopoStartLoc_y && dLoc_y<dTopo_max_y) )
		return LEFT_BOUNDARY;

	// 7 in top boundary
	else if ( (dLoc_x>dTopoStartLoc_x && dLoc_x<dTopo_max_x) && dLoc_y == dTopo_max_y )
		return TOP_BOUNDARY;

	// 8 in right boundary
	else if ( dLoc_x==dTopo_max_x && (dLoc_y>dTopoStartLoc_y && dLoc_y<dTopo_max_y) )
		return RIGHT_BOUNDARY;

	// 9 inside of the boundary
	else if ( (dLoc_x>dTopoStartLoc_x && dLoc_x<dTopo_max_x) && (dLoc_y>dTopoStartLoc_y && dLoc_y<dTopo_max_y) )
		return INSIDE_TOPO;

	// 10 out side of the boundary
	else
		return OUTSIDE_TOPO;
}

// -------------------1. Bus mobility(By Path) -------------------------------------------------

// Bus move a step depends on current direction.
void Movement::Bus_move_a_step_rely_on_curDirection(CBusNode *pBus, double dCurDirection, int nOverTime_ms,/* unsigned int nCrc,*/ Point *pCurPathBeginPoint, Point *pCurPathEndPoint)
{
	assert( NULL != pBus );
	assert( NULL != pCurPathBeginPoint);
	assert( NULL != pCurPathEndPoint);
	assert( 0 < nOverTime_ms );
	//assert( 0 < dCurDirection);

	if (NULL == pBus || NULL == pCurPathBeginPoint || NULL == pCurPathEndPoint || 0 >= nOverTime_ms) {
		return;
	}
	double dLoc_x = pBus->GetLoc_X();
	double dLoc_y = pBus->GetLoc_Y();
	double dVelocity = pBus->GetVelocity();

	//std::cout << "Bus当前位置和速度：\n" << " ( " << dLoc_x << ", " << dLoc_y << ", " << dVelocity << " ) \n";

	double dBeginLoc_x = pCurPathBeginPoint->m_dLoc_X;
	double dBeginLoc_y = pCurPathBeginPoint->m_dLoc_Y;

 	double dEndLoc_x = pCurPathEndPoint->m_dLoc_X;
 	double dEndLoc_y = pCurPathEndPoint->m_dLoc_Y;

	double dIncreLoc_x = 0.0;
	double dIncreLoc_y = 0.0;

	double dNewLoc_x = 0.0;
	double dNewLoc_y = 0.0;

	// Begin move.
	pBus->Set_isStartMove(true);

	dIncreLoc_x = cos( dCurDirection ) * ( dVelocity * (( (double)nOverTime_ms )*0.001) );
	dIncreLoc_y = sin( dCurDirection ) * ( dVelocity * (( (double)nOverTime_ms )*0.001) );
	dNewLoc_x = dLoc_x+dIncreLoc_x;
	dNewLoc_y = dLoc_y+dIncreLoc_y;


	
	double dNewLength = NSMath::EuclidDistance(dBeginLoc_x, dBeginLoc_y, dNewLoc_x, dNewLoc_y);
	double dCurLength = NSMath::EuclidDistance(dBeginLoc_x, dBeginLoc_y, dEndLoc_x, dEndLoc_y);
	
	//std::cout << "Bus新位置：\n" << " ( " << dNewLoc_x << ", " << dNewLoc_y << " ) \n";
	// 根据bus node 得到id.

	//int busID = NSRunner::Get_BusID_viaPNode(pBus);
	
	//nCount_Record_Bus ++;

	//假如bus移动的路段大于它所在的路段，则将它的节点设置为该路段的终止节点
	if (dNewLength > dCurLength){
		//if (0 == nCrc % 100) {
			//LogFile::instance()->m_ofMovementBus << "\n\n";
			//LogFile::instance()->m_ofMovementBus << "-Bus ";
			//LogFile::instance()->m_ofMovementBus << pBus->GetBusId() << " from ( " << dLoc_x << ", " << dLoc_y << " ) to ( " << dEndLoc_x << ", " << dEndLoc_y << " )\n";
		//	pBus->SetBusRecordCount(0);
		//}
		pBus->SetLocation(dEndLoc_x, dEndLoc_y);
	//	std::cout << "from ( " << dLoc_x << ", " << dLoc_y << " ) to ( " << dEndLoc_x << ", " << dEndLoc_y << " )" << std::endl;
	}
	else {
		//if ( 0 == nCrc % 100) {
		//	
			//LogFile::instance()->m_ofMovementBus << "-Bus ";
			//LogFile::instance()->m_ofMovementBus << pBus->GetBusId() << " from ( " << dLoc_x << ", " << dLoc_y << " ) to ( " << dNewLoc_x << ", " << dNewLoc_y << " )\n";
		//	pBus->SetBusRecordCount(0);
		//}
		pBus->SetLocation(dNewLoc_x, dNewLoc_y);
	//	std::cout << "from ( " << dLoc_x << ", " << dLoc_y << " ) to ( " << dNewLoc_x << ", " << dNewLoc_y << " )" << std::endl;
	}
}

// Bus move a step depends on current direction and current path.
// void Movement::Bus_move_a_step_rely_on_curDirection_path(CBusNode *pBus, double dCurDirection, int nOverTime_ms, double dCurPathLength)
// {
// 	assert( NULL != pBus );
// 	assert( 0 < nOverTime_ms );
// 
// 	double dLoc_x = pBus->GetLoc_X();
// 	double dLoc_y = pBus->GetLoc_Y();
// 	double dVelocity = pBus->GetVelocity();
// 
// 	double dBeginLoc_x = pCurPathBeginPoint->m_dLoc_X;
// 	double dBeginLoc_y = pCurPathBeginPoint->m_dLoc_Y;
// 
// 	// 	double dEndLoc_x = pCurPathEndPoint->m_dLoc_X;
// 	// 	double dEndLoc_y = pCurPathEndPoint->m_dLoc_Y;
// 
// 	double dIncreLoc_x = 0.0;
// 	double dIncreLoc_y = 0.0;
// 
// 	double dNewLoc_x = 0.0;
// 	double dNewLoc_y = 0.0;
// 
// 	// Begin move.
// 	pBus->Set_isStartMove(true);
// 
// 	dIncreLoc_x = cos(dCurDirection)
// 		dIncreLoc_x = cos( dCurDirection ) * ( dVelocity * (( (double)nOverTime_ms )*0.001) );
// 	dIncreLoc_y = sin( dCurDirection ) * ( dVelocity * (( (double)nOverTime_ms )*0.001) );
// 	dNewLoc_x = dLoc_x+dIncreLoc_x;
// 	dNewLoc_y = dLoc_y+dIncreLoc_y;
// 
// 	double dNewLength = NSMath::EuclidDistance(dBeginLoc_x, dBeginLoc_y, dNewLoc_x, dNewLoc_y);
// 	double dCurLength = NSMath::EuclidDistance(dBeginLoc_x, dBeginLoc_y, dEndLoc_x, dEndLoc_y);
// 
// 	if (dNewLength > dCurPathLength){
// 		pBus->SetLocation()
// 	}
// }

// -------------------2. Car Mobility(RWALK) ------------------

//  Move a step forward over a certain interval. for RWALK.
void Movement::Car_move_forward_overTimeSlot_RWALK(CCarNode * pCar, int nOverTime_ms)
{
	assert( NULL != pCar );
	assert( nOverTime_ms > 0 );
	
	pCar->SetCarRecordCount_IN();
	unsigned int nC = pCar->GetCarRecordCount();

	double dCurXITA = pCar->GetCurDirection_RWALK();  // Current direction angle.

	Car_move_a_step_rely_on_curDirection( pCar, dCurXITA, nOverTime_ms, nC );
}

// Car move a step depends on current direction.
void Movement::Car_move_a_step_rely_on_curDirection_RWALK(CCarNode *pCar, int nOverTime_ms)
{
	
}

//  Move a step forward over a certain interval.
void Movement::Car_move_a_step_rely_on_curDirection(CCarNode *pCar, double dCurDirection, int nOverTime_ms, unsigned int nC)
{
	assert( NULL != pCar );
	//assert( dCurDirection > 0);
	assert( nOverTime_ms > 0 );

	double dLoc_x = pCar->GetLoc_X();
	double dLoc_y = pCar->GetLoc_Y();
	double dVelocity = pCar->GetVelocity();

	double dIncreLoc_x = 0.0;
	double dIncreLoc_y = 0.0;
	double dNewLoc_x = 0.0;
	double dNewLoc_y = 0.0;

	// Begin move.
	pCar->Set_isStartMove(true);
	dIncreLoc_x = cos( dCurDirection ) * ( dVelocity * (( (double)nOverTime_ms )*0.001) );
	dIncreLoc_y = sin( dCurDirection ) * ( dVelocity * (( (double)nOverTime_ms )*0.001) );
	dNewLoc_x = dLoc_x+dIncreLoc_x;
	dNewLoc_y = dLoc_y+dIncreLoc_y;
	Ensure_Car_within_Topo_range(dNewLoc_x, dNewLoc_y);
	pCar->SetLocation( dNewLoc_x, dNewLoc_y );

	// 根据Car node 得到ID
	//int carID = NSRunner::Get_CarID_viaPNode(pCar);
	//nCount_Record_Car ++;
	
	//if ( 0 == nC % 100 ) {
	//	LogFile::instance()->m_ofMovementCar << "-Car ";

	//	LogFile::instance()->m_ofMovementCar << "from ( " << dLoc_x << ", " << dLoc_y << " ) to ( " << dNewLoc_x << ", " << dNewLoc_y << " )\n";
	//}
	
	//pBus->SetLocation(dNewLoc_x, dNewLoc_y);
	//std::cout << "from ( " << dLoc_x << ", " << dLoc_y << " ) to ( " << dNewLoc_x << ", " << dNewLoc_y << " )" << std::endl;
	
}

// Adjust the car's coordinates, ensure them in the area of Topology.
void Movement::Ensure_Car_within_Topo_range(double &dLoc_x, double &dLoc_y)
{
	double dTopoStartLoc_x = Topology::Get_Topo_start_loc_x();
	double dTopoStartLoc_y = Topology::Get_Topo_start_loc_y();
	double dTopo_max_x = dTopoStartLoc_x+Topology::Get_Topo_Width();
	double dTopo_max_y = dTopoStartLoc_y+Topology::Get_Topo_Height();

	dLoc_x = dLoc_x<dTopoStartLoc_x ? dTopoStartLoc_x : dLoc_x;
	dLoc_y = dLoc_y<dTopoStartLoc_y ? dTopoStartLoc_y : dLoc_y;
	dLoc_x = dLoc_x>dTopo_max_x ? dTopo_max_x : dLoc_x;
	dLoc_y = dLoc_y>dTopo_max_y ? dTopo_max_y : dLoc_y;
}

// get the move duration.
double Movement::Get_MoveDureation_Sec_RWALK()
{
	return 0;
}

// Reset move duration.
void Movement::Reset_MoveDuration_RAWALK()
{

}

// 检查节点的当前位置并选择重置方向.
// Check the MN's current position, maybe reset the direction depending on whether it reaches boundary or be bounced.
void Movement::Check_Car_curPosition_maybe_reset_its_direction_RWALK(CCarNode *pCar )
{
	assert( NULL !=  pCar);

	double dLoc_x = pCar->GetLoc_X();
	double dLoc_y = pCar->GetLoc_Y();
	int nPosition = Get_Position_in_topo( dLoc_x, dLoc_y );
	
	double dBouncedXITA = 0.0; // maybe bounced or not.
	double dComingXITA = pCar->GetCurDirection_RWALK();

	// --------------------------- A. if MN is in the boundaries, bounce then step forward.
	if ( LEFT_BOTTOM_POINT == nPosition )
	{
		// Bounce by ignoring the coming angle, and reset the MN's direction: [0, PI/2).
		pCar->Reset_Direction_random_RWALK( 0, 0.5*PI );
	}
	else if ( LEFT_BOUNDARY == nPosition )
	{
		if ( 0.5*PI <= dComingXITA && dComingXITA <= PI )
		{
			// Bounce depend on the coming angel, and reset the MN's direction.
			dBouncedXITA = PI-dComingXITA;
			pCar->Reset_Direction_RWALK( dBouncedXITA );
		}
		else if ( PI <= dComingXITA && dComingXITA <= 1.5*PI )
		{
			// Bounce depend on the coming angel, and reset the MN's direction.
			dBouncedXITA = 3*PI-dComingXITA;
			pCar->Reset_Direction_RWALK( dBouncedXITA );
		}
	}
	else if ( LEFT_TOP_POINT == nPosition )
	{
		// Bounce by ignoring the coming angle, and reset the MN's direction: [0, PI/2).
		pCar->Reset_Direction_random_RWALK( 1.5*PI, 2*PI );
	}
	else if ( TOP_BOUNDARY == nPosition )
	{
		if ( 0 <= dComingXITA && dComingXITA <= PI )
		{
			// Bounce depend on the coming angel, and reset the MN's direction.
			dBouncedXITA = 2*PI-dComingXITA;
			pCar->Reset_Direction_RWALK( dBouncedXITA );
		}
	}
	else if ( RIGHT_TOP_POINT == nPosition )
	{
		// Bounce by ignoring the coming angle, and reset the MN's direction: [PI, 1.5*PI).
		pCar->Reset_Direction_random_RWALK( PI, 1.5*PI );
	}
	else if ( RIGHT_BOUNDARY == nPosition )
	{
		if ( 1.5*PI <= dComingXITA && dComingXITA <= 2*PI )
		{
			// Bounce depend on the coming angel, and reset the MN's direction.
			dBouncedXITA = 3*PI-dComingXITA;
			pCar->Reset_Direction_RWALK( dBouncedXITA );
		}
		else if ( 0 <= dComingXITA && dComingXITA <= 0.5*PI )
		{
			// Bounce depend on the coming angel, and reset the MN's direction.
			dBouncedXITA = PI-dComingXITA;
			pCar->Reset_Direction_RWALK( dBouncedXITA );
		}
	}
	else if ( RIGHT_BOTTOM_POINT == nPosition )
	{
		// Bounce by ignoring the coming angle, and reset the MN's direction: [PI, 1.5*PI).
		pCar->Reset_Direction_random_RWALK( 0.5*PI, PI );
	}
	else if ( BOTTOM_BOUNDARY == nPosition )
	{
		if ( PI <= dComingXITA && dComingXITA < 2*PI )
		{
			// Bounce depend on the coming angel, and reset the MN's direction.
			dBouncedXITA = 2*PI-dComingXITA;
			pCar->Reset_Direction_RWALK( dBouncedXITA );
		}
	}

	// --------------------------- B. if MN is not in the boundaries, only need step forward.
	else if ( INSIDE_TOPO == nPosition )
	{
		// No need to bounce, so the current direction will be not changed.
	}
}

