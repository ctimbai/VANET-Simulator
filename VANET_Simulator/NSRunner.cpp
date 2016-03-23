#include "NSRunner.h"


extern char ResourceList[RES_NUM + 1] = "ABCDEFGHIJ";


// -------------------------------------------------------------------------
NSRunner::NSRunner()
{
	m_pObjTopo		= new Topology();
	m_pObjRC		= new RdmCtr();
	m_pObjMovement	= new Movement();
	m_pObjContact	= new Contact();
	m_pObjBA		= new BufferAllocation();

	m_nNS_tickCnt = 0;
}


NSRunner::~NSRunner()
{
	LogFile::instance()->m_ofRunLog << "The NS_Runner is destroyed now!\n";

	SAFELY_DELETE_PTR( m_pObjRC );
	SAFELY_DELETE_PTR( m_pObjBA );
	SAFELY_DELETE_PTR( m_pObjContact );
	SAFELY_DELETE_PTR( m_pObjMovement );
	SAFELY_DELETE_PTR( m_pObjTopo );
	//SAFELY_DELETE_PTR()

	m_snBus_ID = 0;
	m_snCar_ID = 0;

	m_nNS_tickCnt = 0;
}

// -------------------------------- The static member. -------------------------------

int NSRunner::m_nNS_LastTime = 100;


int NSRunner::m_snBus_ID = 1;
std::map<int, CBusNode *> NSRunner::m_mapBuses;

int NSRunner::m_snCar_ID = 1;
std::map<int, CCarNode *> NSRunner::m_mapCars;

std::vector<Path *> NSRunner::m_vecBusPath;

std::vector<Resource *> NSRunner::m_mapResources;

std::vector<char> NSRunner::m_vecCarResources;


// --------------------------------A. Topology----------------------------------------

// 1. Set the topology.
void NSRunner::SetTheTopology( double dTopoWidth, double dTopoHeight)
{
	assert(0 < dTopoHeight && 0 < dTopoWidth);
	if (0 > dTopoHeight || 0 > dTopoWidth) {
		// 错误！！
		return;
	}

	m_pObjTopo->Set_Topo_Height(dTopoHeight);
	m_pObjTopo->Set_Topo_Width(dTopoWidth);
}

// --------------------------------B. Bus Node----------------------------------------

// create a bus's path.
void NSRunner::Create_a_Bus_Path(int type)
{
	Path *p = new Path();
	p->GetAPath_By_APoint(type);
// 	std::vector<Point *> point = Path::PATHPOINT;
// 	return point;
	m_vecBusPath.push_back(p);
}

// create all buses' path.
void NSRunner::Create_Bus_Path(int nBusPath)
{
	assert( 0 < nBusPath);
	if ( 0 > nBusPath){
		// 出错
		return;
	}
	// 表示bus路线的起点位置
	int type;
	for (int i = 0; i < nBusPath; ++ i) {
		//输入公交车的路线的起点位置，人为控制.
		cin >> type;
		Create_a_Bus_Path(type);
	}
}

// Create BUS_PATH path at random.
void NSRunner::Create_Bus_Path_at_Random(int nBusPath)
{
	for(int i = 0; i < nBusPath; ++ i) {
		Path *pBusPath = new Path();
		pBusPath->Create_A_Path_At_Random(m_pObjRC);

		// 记录bus路径的位置点
		Record_Bus_Path_Location(pBusPath, i + 1);

		m_vecBusPath.push_back(pBusPath);
	}
}

/*
// get all bus paths' begin point.
std::vector<Point *> NSRunner::Get_All_Bus_Path_BeginPoint(int nBusPath)
{
	std::vector<Point *> pointRet;
	for (BUSPATH_ITER it = m_vecBusPath.begin(); it != m_vecBusPath.end(); ++ it) {
		pointRet.push_back((*it)->GetBeginPoint());
	}
}

*/
// Create bus at every path at their begin point.
void NSRunner::Create_Bus_At_Path_BeginPoint(std::vector<Point *> pPoint)
{
	double dLocx = 0.0;
	double dLocy = 0.0;
	//int busID = 1;

	std::vector<Point *>::iterator it;
	for (it = pPoint.begin(); it != pPoint.end(); ++ it) {
		dLocx = (*it)->m_dLoc_X;
		dLocy = (*it)->m_dLoc_Y;

		// 1. create bus node.
		CBusNode * pObjBus_at_Path = new CBusNode(dLocx, dLocy);
		m_mapBuses.insert(make_pair(m_snBus_ID, pObjBus_at_Path));

		// 2.log
		// 记得补上。

		// 3. busID ++
		m_snBus_ID ++;
	}
}

// Create bus at path begin point.
void NSRunner::Create_Bus_At_All_Path_BeginPoint()
{
	for ( BUSPATH_ITER it = m_vecBusPath.begin(); it != m_vecBusPath.end(); ++ it) {
		Point *pB = (*it)->GetBeginPoint();
		double dLocX = pB->m_dLoc_X;
		double dLocY = pB->m_dLoc_Y;
		
		// 1. 创建节点
		CBusNode *pObjBus_at_Path = new CBusNode(dLocX, dLocY);

		pObjBus_at_Path->SetBusId(m_snBus_ID);
		m_mapBuses.insert(make_pair(m_snBus_ID, pObjBus_at_Path));
		

		// 2. log
		// 记得补上
		//std::cout << " Bus [" << m_snBus_ID << "] ( " << dLocX << ", " << dLocY << " ) is created.\n";
		LogFile::instance()->m_ofRunLog << " Bus [" << m_snBus_ID << "] ( " << dLocX << ", " << dLocY << " ) is created.\n";
		LogFile::instance()->m_ofLocBus << "-Bus:\t" << m_snBus_ID << " ( " << dLocX << ", " << dLocY << " ) \n";

		
		// 4. 设置bus path
		pObjBus_at_Path->SetAPath(*it);

		// 5. 记录bus path
		Path *p = pObjBus_at_Path->GetAPath();

		std::vector<Point *> vecPath = p->m_vecPath;
		std::vector<Point *>::iterator itP;

		LogFile::instance()->m_ofLocBus << "-BusPath:\t" << m_snBus_ID << "\n";

		//std::cout << "-BusPath:\n";
		for (itP = vecPath.begin(); itP != vecPath.end(); ++ itP) {
			LogFile::instance()->m_ofLocBus << "--> ( " << (*itP)->m_dLoc_X << ", " << (*itP)->m_dLoc_Y << " )";
			//std::cout << "--> ( " << (*itP)->m_dLoc_X << ", " << (*itP)->m_dLoc_Y << " )";
		}

		//std::cout << "\n";
		LogFile::instance()->m_ofLocBus << "\n";

		// 3. busID ++
		m_snBus_ID ++;
	}
}


// 判断bus是否到达path终点，如果没有，则向前移动一步,如果达到终点，则将其速度置为0.
bool NSRunner::Judge_Whether_a_bus_Arrival_Path_End(CBusNode *pBus)
{
	assert (NULL != pBus);
	if (NULL == pBus) {
		//!!!!错误
	}

	Point * pEndPoint = pBus->GetAPath()->GetEndPoint();

	double dEx = pEndPoint->m_dLoc_X;
	double dEy = pEndPoint->m_dLoc_Y;

	double dx = pBus->GetLoc_X();
	double dy = pBus->GetLoc_Y();

	if (dx >= dEx ) 
		return true;
	else
		return false;
}



// Get the bus Container.
BUS_CONTAINER* NSRunner::Get_pContainer_of_all_Buses()
{
	return &m_mapBuses;
}

CBusNode* NSRunner::Get_pBusNode_ByBusID(int nBus_ID)
{
	assert( nBus_ID >= 0 );
	if ( nBus_ID < 0 )
	{
		//		LogFile::instance()->m_ofErrLog << "In CMNode* RunController::Get_pMN_viaMNID, the nCar_ID < 0.\n";
		return NULL;
	}

	// MN_map< MN_ID, CMNode*>
	BUS_CONTAINER_ITER map_it = m_mapBuses.begin();
	for ( ; map_it != m_mapBuses.end(); ++ map_it )
	{
		if ( nBus_ID == map_it->first )
		{
			return map_it->second;
		}
	}

	return NULL;
}

int NSRunner::Get_BusID_viaPNode(CBusNode * pBusNode)
{
	assert( NULL != pBusNode );
	if ( NULL == pBusNode  )
	{
		//		LogFile::instance()->m_ofErrLog << "In RunController::Get_MNID_viaPNode, NULL == pCarNode.\n";
		return -1;
	}

	// MN_map< MN_ID, CMNode*>
	BUS_CONTAINER_ITER map_it = m_mapBuses.begin();
	for ( ; map_it != m_mapBuses.end(); ++ map_it )
	{
		if ( pBusNode == map_it->second )
		{
			return map_it->first;
		}
	}

	//	LogFile::instance()->m_ofErrLog << "In RunController::Get_MNID_viaPNode, Can't find the MN_ID.\n";
	return -1;
}
// set all buses' Velocity.
void NSRunner::Set_All_Buses_Velocity(double dV)
{
	assert( dV > 0 );

	BUS_CONTAINER * pAllBus = Get_pContainer_of_all_Buses();
	for (BUS_CONTAINER_ITER it = pAllBus->begin(); it != pAllBus->end(); ++ it) {
		it->second->SetVelocity(dV);
	}
}

//2. Reset cars to begin.
void NSRunner::Reset_Cars_To_Begin()
{
// 	CAR_CONTAINER *pAllCars = Get_pContainer_of_all_Cars();
// 	for (CAR_CONTAINER_ITER it = pAllCars->begin(); it != pAllCars->end(); ++ it) {
// 		CCarNode *pCars = it->second;
// 
// 		pCars->SetCarRequestResSize(0);
// 		pCars->SetCarRequestTime(0.0);
// 		pCars->SetContactNum_toNum(0);
// 		pCars->SetCarResTime(0.0);
// 		pCars->SetSuccess(false);
// 		pCars->SetCarReceiveTime(0.0);
// 		pCars->Set_isStartMove(false);
// 		pCars->SetCarisOutofTime(false);
// 
// 		pCars->SetBusID_toEmpty();
// 	}
	for (CAR_CONTAINER_ITER it = m_mapCars.begin(); it != m_mapCars.end(); ) {
		m_mapCars.erase(it ++);
	}
	m_snCar_ID = 0;

}

// 置所有bus为初识状态.
void NSRunner::Reset_Bus_To_Begin()
{
// 	BUS_CONTAINER *pAllBus = Get_pContainer_of_all_Buses();
// 	//bool flag = true;
// 	for (BUS_CONTAINER_ITER it = pAllBus->begin(); it != pAllBus->end(); ++ it) {
// 		CBusNode *pBus = it->second;
// 		if (flag) {
// 			pBus->ResetBusBufferToEmpty();
// 			flag = false;
// 		}
// 		
// 		pBus->Set_isStartMove(false);
// 		pBus->SetVelocity(0.0);
// 		//SAFELY_DELETE_PTR(pBus);
// 	}

	for (BUS_CONTAINER_ITER it = m_mapBuses.begin(); it != m_mapBuses.end(); ) {
		m_mapBuses.erase(it ++);
	}
	m_snBus_ID = 0;
}

// --------------------------------C. Car Node----------------------------------------

// 1. Create cars at random location.
void NSRunner::Create_Cars_At_Random_Location(int nCarNum, double dMinLoc_X, double dMaxLoc_X, double dMinLoc_Y, double dMaxLoc_Y)
{
	assert( 0 < nCarNum );
	if ( 0 >= nCarNum )
	{
// 		cerr << "Error: the node number can not be negative.\n";
// 		LogFile::instance()->m_ofErrLog << "Error: the node number can not be negative.\n";
		return;
	}
	assert( dMaxLoc_X >= 0 && dMaxLoc_Y >= 0 );
	assert( dMaxLoc_X >= dMinLoc_X );
	assert( dMaxLoc_Y >= dMinLoc_Y );
	if ( dMaxLoc_X < 0 || dMaxLoc_Y < 0 || dMaxLoc_X < dMinLoc_X || dMaxLoc_Y < dMinLoc_Y )
	{
// 		cerr << "Error: the Car's location is not suitable.\n";
// 		LogFile::instance()->m_ofErrLog << "Error: the Car's location is not suitable.\n";
		return;
	}

	// Get nCarNum car at random locations.
	vector<double> vecLocX;
	vector<double> vecLocY;

	double dLocX = 0;
	double dLocY = 0;

	for (int i = 0; i < nCarNum; i ++) {
		dLocX = m_pObjRC->GetRdmRealNum(dMinLoc_X, dMaxLoc_X);
		vecLocX.push_back(dLocX);
		dLocY = m_pObjRC->GetRdmRealNum(dMinLoc_Y, dMaxLoc_Y);
		vecLocY.push_back(dLocY);

		//std::cout << " 哈 " << dLocX   << " " << dLocY << std::endl;
	}

	// 0 Sort the node. !!!!!!!necessary？？？
	//NSMath::BubbleSort(vecLocX);
	//NSMath::BubbleSort(vecLocY);

	for (int i = 0; i < nCarNum; i ++) {
		double dLoc_X = vecLocX[i];
		double dLoc_Y = vecLocY[i];

		// 1 Create node.
		CCarNode *pObjCar_AtRdmLoc = new CCarNode(dLoc_X, dLoc_Y);
		
		pObjCar_AtRdmLoc->SetCarID(m_snCar_ID);

		m_mapCars.insert(make_pair(m_snCar_ID, pObjCar_AtRdmLoc));

		// 2 Log.
		//LogFile::instance()->m_ofRunLog << " Car [" << m_snCar_ID << "] ( " << dLoc_X << ", " << dLoc_Y << " ) is created.\n";
		//LogFile::instance()->m_ofLocCar << "-Car\t" << m_snCar_ID << "\t-X\t" << dLoc_X << "\t-Y\t" << dLoc_Y << "\n";
	
		//std::cout << " Car [" << m_snCar_ID << "] ( " << dLoc_X << ", " << dLoc_Y << " ) is created.\n";

		// 3 
		m_snCar_ID ++;
	}
}

CAR_CONTAINER* NSRunner::Get_pContainer_of_all_Cars()
{
	return &m_mapCars;
}

CCarNode* NSRunner::Get_pCarNode_ByCarID(int nCar_ID)
{
	assert( nCar_ID >= 0 );
	if ( nCar_ID < 0 )
	{
//		LogFile::instance()->m_ofErrLog << "In CMNode* RunController::Get_pMN_viaMNID, the nCar_ID < 0.\n";
		return NULL;
	}

	// MN_map< MN_ID, CMNode*>
	CAR_CONTAINER_ITER map_it = m_mapCars.begin();
	for ( ; map_it != m_mapCars.end(); ++ map_it )
	{
		if ( nCar_ID == map_it->first )
		{
			return map_it->second;
		}
	}

	return NULL;
}

int NSRunner::Get_CarID_viaPNode(CCarNode * pCarNode)
{
	assert( NULL != pCarNode );
	if ( NULL == pCarNode  )
	{
//		LogFile::instance()->m_ofErrLog << "In RunController::Get_MNID_viaPNode, NULL == pCarNode.\n";
		return -1;
	}

	// MN_map< MN_ID, CMNode*>
	CAR_CONTAINER_ITER map_it = m_mapCars.begin();
	for ( ; map_it != m_mapCars.end(); ++ map_it )
	{
		if ( pCarNode == map_it->second )
		{
			return map_it->first;
		}
	}

//	LogFile::instance()->m_ofErrLog << "In RunController::Get_MNID_viaPNode, Can't find the MN_ID.\n";
	return -1;
}

// set all Cars' Velocity.
void NSRunner::Set_All_Cars_Velocity(double dV)
{
	assert ( dV > 0 );

	CAR_CONTAINER * pAllCars = Get_pContainer_of_all_Cars();
	for (CAR_CONTAINER_ITER it = pAllCars->begin(); it != pAllCars->end(); ++ it) {
		it->second->SetVelocity(dV);
	}
}

// --------------------------------F. Mobility ----------------------------------------

// 1. Let all node Forward a step(Bus and car).
void NSRunner::Let_All_Node_Forward_a_Step(int nMobility)
{
	
}


// 所有bus向前移动一步，并判断是否达到终点.
bool NSRunner::Judge_Whether_All_buses_Arrival_Path_End()
{
	const int cnNSTimeSlot_ms = SimulateTime::GetTimeStep_ms();

	BUS_CONTAINER * pAllBus = Get_pContainer_of_all_Buses();
	
	//判断所有bus的速度是否为0.
	for ( BUS_CONTAINER_ITER it = pAllBus->begin(); it != pAllBus->end(); ++ it) {
		CBusNode *pBus = it->second;
		double d = pBus->GetVelocity();
		if (d != 0.0) {
			return false;
		}	
	}

	// 所有bus到达终点，时间为：。。。
	return true;
}

// 2. Let all buses forward a step.(by path).
void NSRunner::Let_All_Buses_Forward_a_Step()
{
	const int cnNSTimeSlot_ms = SimulateTime::GetTimeStep_ms();
	
	

	BUS_CONTAINER * pAllBus = Get_pContainer_of_all_Buses();
	for ( BUS_CONTAINER_ITER it = pAllBus->begin(); it != pAllBus->end(); ++ it) {
		CBusNode *pBus = it->second;

		//pBus->SetBusRecordCount_IN();
		//unsigned int nBrc = pBus->GetBusRecordCount();

		// 假如到达终点，就将速度设为0.
		if( true == Judge_Whether_a_bus_Arrival_Path_End(pBus) ) {
			pBus->SetVelocity(0.0);
			pBus->Set_isStartMove(false);
		}

		else {
			Path *pBuspath = pBus->GetAPath();

			double dLocx = pBus->GetLoc_X();
			double dLocy = pBus->GetLoc_Y();

			//std::cout << "Bus位置：\n" << " ( " << dLocx << ", " << dLocy << " ) \n";

			//得到该bus所在路段上的初始节点
			Point *pBPoint = pBus->Get_PathBeginPoint_Of_Bus_Location(dLocx, pBuspath);
			double dLocB_x = pBPoint->m_dLoc_X;
			double dLocB_y = pBPoint->m_dLoc_Y;

			//std::cout << "Bus在路径上的初始位置：\n" << " ( " << dLocB_x << ", " << dLocB_y << " ) \n";

			// 得到该bus所在路段上的终止节点
			Point *pEPoint = pBus->Get_PathEndPoint_Of_Bus_Location(dLocx, pBuspath);
			double dLocE_x = pEPoint->m_dLoc_X;
			double dLocE_y = pEPoint->m_dLoc_Y;

			//std::cout << "Bus在路径上的终止位置：\n" << " ( " << dLocE_x << ", " << dLocE_y << " ) \n";

			//LogFile::instance()->m_ofRunLog << "***********************\n";
			// 计算bus当前方向.
			if(dLocx == dLocB_x) { 
				pBus->Reset_Direction_rely_on_path(dLocB_x,dLocB_y, dLocE_x, dLocE_y);
			}
			// 		else {
			// 			pBus->Reset_Direction_rely_on_path(dLocB_x, dLocB_y, dLocx, dLocy);
			// 		}

			double dCurDirection = pBus->GetBusCurDirection();

			// 		if (dLocE_y < dLocB_y) {
			// 			dCurDirection = 0 - dCurDirection;
			// 		}

			//std::cout << "bus当前方向：\n" << dCurDirection << "\n";

			// 计算bus所在这个路段的长度
			//double dCurPathLength = NSMath::EuclidDistance(dLocB_x, dLocB_y, dLocE_x, dLocE_y);

			m_pObjMovement->Bus_move_a_step_rely_on_curDirection(pBus, dCurDirection, cnNSTimeSlot_ms,/* nBrc, */pBPoint, pEPoint);
		}
		
	}
}

// 3. Let all cars forward a step.
void NSRunner::Let_All_Cars_Forward_a_Step(int nMobility)
{
	const int cnNSTimeSlot_ms = SimulateTime::GetTimeStep_ms();

	CAR_CONTAINER * pAllCars = Get_pContainer_of_all_Cars();

	for (CAR_CONTAINER_ITER it = pAllCars->begin(); it != pAllCars->end(); ++ it) {
		CCarNode * pCar = it->second;

		if ( RWALK == nMobility ) {
			// 1) Before let the MN begins moving, initialize the direction for the first time.
			//if ( false == pCar->Get_isStartMove() )
			//{
				pCar->Reset_Direction_random_RWALK(-2*PI, 2*PI);
			//}
			m_pObjMovement->Car_move_forward_overTimeSlot_RWALK(pCar, cnNSTimeSlot_ms);
		}
	}
}

// --------------------------------G. Contact. ----------------------------------------

// 1. Let all node check transmission chance.
void NSRunner::Let_All_Node_Check_Transmission_Chance(int nCase)
{
	double dCurTime = SimulateTime::Get_CurrentTime();

	// 得到全部的bus和car
	BUS_CONTAINER * pAllBuses = Get_pContainer_of_all_Buses();
	CAR_CONTAINER * pAllCars = Get_pContainer_of_all_Cars();
	
	for (BUS_CONTAINER_ITER itB = pAllBuses->begin(); itB != pAllBuses->end(); ++ itB) {
		CBusNode *pBus = itB->second;

		for (CAR_CONTAINER_ITER itC = pAllCars->begin(); itC != pAllCars->end(); ++ itC ) {
			CCarNode *pCar = itC->second;

			//检查bus是否到达终点
			//!!!!!!!!!!!!!!

			m_pObjContact->Transmission_Between_Tow_Vehicles(pBus, pCar, dCurTime,nCase);
		}
	}

// 	for (BUS_CONTAINER_ITER itB = pAllBuses->begin(); itB != pAllBuses->end();) {
// 		pAllBuses->erase(itB ++);
// 	}
// 
// 	for (CAR_CONTAINER_ITER itC = pAllCars->begin(); itC != pAllCars->end();) {
// 		pAllCars->erase(itC ++);
// 	}
	//SAFELY_DELETE_PTR(pAllBuses);
	//SAFELY_DELETE_PTR(pAllCars);
}


// 2. Let all node check contact rely on severav buffer allocation case.
void NSRunner::Let_All_Node_Check_Contact_rely_on_Buffer_Allocation(int nCase)
{
	Set_Bus_Buffer_rely_on_Buffer_Allocation(nCase);

	Let_All_Node_Check_Transmission_Chance(nCase);
}

// --------------------------------D. Resources ----------------------------------------

// 1. Create all Resource rely on the RES_NUM.
void NSRunner::Create_All_Resources(int nResNum)
{
	//创建RES_NUM个资源

	// 按照资源列表的下标排名
	for (int i = 1; i <= nResNum; i ++) {
		Resource * RS = new Resource();

		// 设置资源的ID
		RS->SetResID(i);

		// 设置资源的类型
		char cResType = ResourceList[i - 1];
		RS->SetResType(cResType);

		// 根据Zipf定律算出资源的流行度
		double dResPop = nResNum / pow(i, dPZipf);
		RS->SetResPop(dResPop);

		// 随机生成数据包的大小（packet）(0,10)
		unsigned int nSize = m_pObjRC->GetRdmIntNum(1, 10);
		RS->SetResSize(nSize);

		// 随机产生数据包的延迟时间(10s, 20s) !!!!可调
		double dTime = m_pObjRC->GetRdmRealNum(100.0, 200.0);
		RS->SetResTime(dTime);

		m_mapResources.push_back(RS);
	}

	// 记录所有产生的资源
	Record_All_Resources_Begin();
}

// 2. 创建所有car的请求资源类型.
void NSRunner::Create_All_Car_Request_Resources(int nCarNum)
{
	for (int i = 0; i < nCarNum; ++ i) {
		// 在10个资源中随机产生1个
		unsigned int index = m_pObjRC->GetRdmIntNumNotEqual(0, RES_NUM-1);
		char cResType = ResourceList[index];
		m_vecCarResources.push_back(cResType);
	}
}

RESOURCE*	NSRunner::Get_pContainer_of_all_Resources()
{
	return &m_mapResources;
}

// --------------------------------E. Buffer Allocation---------------------------------

// 1. Get the resources rely on several buffer allocation.
std::vector<Resource *> NSRunner::Get_Buffer_Allocation(int nCase)
{
	std::vector<Resource *> vecResRet;

	if (nCase == Knapsack_allocation_by_DynamicProgram) {
		vecResRet = m_pObjBA->Buffer_01knacp_Allocation(m_mapResources);
	}

	if (nCase == In_ascending_order_of_size_by_Greedy) {
		vecResRet = m_pObjBA->Buffer_IaosbG_Allocation(m_mapResources);
	}

	if (nCase == In_descending_order_of_size_by_Greedy) {
		vecResRet = m_pObjBA->Buffer_IdosbG_Allocation(m_mapResources);
	}

	if (nCase == In_ascending_order_of_formula_by_Greedy) {
		vecResRet = m_pObjBA->Buffer_IaofbG_Allocation(m_mapResources);
	}

	if (nCase == In_descending_order_of_formula_by_Greedy) {
		vecResRet = m_pObjBA->Buffer_IdofbG_Allocation(m_mapResources);
	}

	if (nCase == Random_allocation) {
		vecResRet = m_pObjBA->Buffer_Random_Allocation(m_mapResources, m_pObjRC);
	}

	return vecResRet;
}


// 2. Set all buses' buffer by getting resources from buffer allocation.
void NSRunner::Set_Allocation_Resources_Buffer_in_Bus(std::vector<Resource *> pR, int nCase)
{
	BUS_CONTAINER * pAllBus = Get_pContainer_of_all_Buses();
	bool flag = true;

	for (BUS_CONTAINER_ITER it = pAllBus->begin(); it != pAllBus->end(); ++ it) {
		CBusNode *pBus = it->second;

		//所有bus所存的资源都是一样
		pBus->SetBusAllocationResource(pR);

		// Log: !!!!!!!!!!!!!!!!!!!!!!!!!!

		// 1 得到bus的缓存
		std::vector<Resource *> *pBusR = pBus->get_BusContainer_Resource();
		
		// 2 记录bus的缓存
		if (flag) {
			Record_Bus_Buffer(pBusR, nCase);
			flag = false;
		}
		
		
	}


}

// 3. Set all cars' buffer by random style.
void NSRunner::Create_Cars_Resource_at_Random()
{
	CAR_CONTAINER *pAllCar = Get_pContainer_of_all_Cars();

	CAR_RESOURCE *pAllCarResource = Get_pContainer_of_all_Car_Resources();

	CAR_RESOURCE_ITER itR = pAllCarResource->begin();

	for (CAR_CONTAINER_ITER it = pAllCar->begin(); it != pAllCar->end(); ++ it) {
		CCarNode *pCar = it->second;

		// 每辆car所存的资源都是随机从10种资源中获取
		// 本初合理的做法是应该按照资源的流行度来获取，流行度越高的越有可能被取到
		// 那么其随机产生的概率就越大
		// 所以，如何按照资源的流行程度产生按流行度大小分布的随机数，需要好好考虑
		// 本初暂时按照产生任意随机的数字来考虑

		// 在10个资源中随机产生1个
		//unsigned int index = m_pObjRC->GetRdmIntNumNotEqual(0, RES_NUM-1);
		//char cResType = ResourceList[index];

		//std::cout << cResType << "\n";

		char cResType = *itR;
		pCar->SetCarRequestResourceType(cResType);

		// Log. !!!!!!!!!!!!!!!!!!!!!!
		// 1. 得到car的请求资源类型

		char crt = pCar->GetCarRequestResourceType();

		// 2. 记录
		LogFile::instance()->m_ofInfoCar << "\tCarID:\t" << pCar->GetCarID() << "\tCarResType:\t" << crt << "\n";
		
		// 3 ++ itR
		++ itR;
	}
}

CAR_RESOURCE* NSRunner::Get_pContainer_of_all_Car_Resources()
{
	return &m_vecCarResources;
}


// 4. Set All Buses' buffer rely on bus buffer allocation.
void NSRunner::Set_Bus_Buffer_rely_on_Buffer_Allocation(int nCase)
{
	std::vector<Resource *> vecResRet;

	if (nCase == Knapsack_allocation_by_DynamicProgram) {
		vecResRet = m_pObjBA->Buffer_01knacp_Allocation(m_mapResources);
	}

	if (nCase == In_ascending_order_of_size_by_Greedy) {
		vecResRet = m_pObjBA->Buffer_IaosbG_Allocation(m_mapResources);
	}

	if (nCase == In_descending_order_of_size_by_Greedy) {
		vecResRet = m_pObjBA->Buffer_IdosbG_Allocation(m_mapResources);
	}

	if (nCase == In_ascending_order_of_formula_by_Greedy) {
		vecResRet = m_pObjBA->Buffer_IaofbG_Allocation(m_mapResources);
	}

	if (nCase == In_descending_order_of_formula_by_Greedy) {
		vecResRet = m_pObjBA->Buffer_IdofbG_Allocation(m_mapResources);
	}

	if (nCase == Random_allocation) {
		vecResRet = m_pObjBA->Buffer_Random_Allocation(m_mapResources, m_pObjRC);
	}

	// 记录缓存方案得到的结果
	Record_Buffer_Allocation_Results(vecResRet, nCase);

	Set_Allocation_Resources_Buffer_in_Bus(vecResRet, nCase);
}

// --------------------------------H. SpeedUp -------------------------------------------


void NSRunner::SetNSLastRunTime(int nsLastTime)
{	
	m_nNS_LastTime = nsLastTime;
}

int NSRunner::GetNSLastRunTime()
{
	return m_nNS_LastTime;
}

int NSRunner::NS_Runs_for_a_tick()
{
	// 时间向前走一步，知道NS模拟结束
	SimulateTime::TimeStepForward();
	m_nNS_tickCnt ++;
	
	// 得到当前的时间
	double dCurrentTime = SimulateTime::Get_CurrentTime();

	// 打印当前时间
	if (0 == m_nNS_tickCnt % 1000 ) {
		std::cout << "\nCurrentTime: " << dCurrentTime << endl;
		m_nNS_tickCnt = 0;
	}
	
	if ( dCurrentTime >= this->GetNSLastRunTime() ) {
		LogFile::instance()->m_ofRunLog << "\t----------------- When thread exits, the CurrentTime: [" << dCurrentTime << "].\n";
		LogFile::instance()->m_ofRunLog << "\n------------- ^_^ The NS stops run now.\n\n";
		//LogFile::instance()->m_ofForwardLog << "\n------------- ^_^ The NS stops run now.\n\n";
		LogFile::instance()->m_ofRunLog << "---------------- The time_step rounds are: [" << m_nNS_tickCnt << "].\n";
		cout << "\n------------- ^_^ The NS stops run now.\n\n";
		//LogFile::instance()->Fract_I_Log << "------------------ over ------------------------\n";
		//LogFile::instance()->Fract_R_Log << "------------------ over ------------------------\n";
		return NS_RUNS_OVER;
	}

	return NS_RUNS_NOT_OVER;
}



// --------------------------------I. Record and Log some information ----------------------

// record bus path location
void NSRunner::Record_Bus_Path_Location(Path *pBusPath, int ith)
{
	assert(NULL != pBusPath);

	std::vector<Point *> vecAbusPath;
	std::vector<Point *>::iterator it;

	vecAbusPath = pBusPath->m_vecPath;

	// 记录公交车路线的位置点.
	LogFile::instance()->m_ofLocPath << "-PathID\t" << ith << "\n";  

	std::cout << "第 " << ith << " 条路径：" << endl;

	for (it = vecAbusPath.begin(); it != vecAbusPath.end(); ++ it) {
	
		std::cout << "\t--> ( " << (*it)->m_dLoc_X << "," << (*it)->m_dLoc_Y << " )";

		LogFile::instance()->m_ofLocPath
			<< "\t--> ( " << (*it)->m_dLoc_X << "," << (*it)->m_dLoc_Y << " )";
	}
	std::cout << std::endl;

	LogFile::instance()->m_ofLocPath << "\n";

	// 记录在另外一个文件.
	//WriteFromFile_path()
}

// 记录所有产生的资源
void NSRunner::Record_All_Resources_Begin()
{
	LogFile::instance()->m_ofResource << "All of Resources:\n";

	std::cout << "All of Resources:\n";

	for (RESOURCE_ITER it = m_mapResources.begin(); it != m_mapResources.end(); ++ it) {
		LogFile::instance()->m_ofResource 
			<< "\t-ResID:\t" << (*it)->GetResID()
			<< "\t-ResType:\t" << (*it)->GetResType()
			<< "\t-ResSize:\t" << (*it)->GetResSize()
			<< "\t-ResPop:\t" << (*it)->GetResPop()
			<< "\t-ResTime:\t" << (*it)->GetResTime() << "\n\n";

		std::cout << "\t-ResID:\t" << (*it)->GetResID()
			<< "\t-ResType:\t" << (*it)->GetResType()
			<< "\t-ResSize:\t" << (*it)->GetResSize()
			<< "\t-ResPop:\t" << (*it)->GetResPop()
			<< "\t-ResTime:\t" << (*it)->GetResTime() << "\n\n";
	}
}

// 记录缓存方案产生的结果.
void NSRunner::Record_Buffer_Allocation_Results(std::vector<Resource *> vecResRet, int nCase)
{
	LogFile::instance()->m_ofBufferAllocation << "---------------------------------------------------------------------------\n";
	if (nCase == Knapsack_allocation_by_DynamicProgram) {
		LogFile::instance()->m_ofBufferAllocation << "Buffer allocation results:\t" << "Knapsack_allocation_by_DynamicProgram:" << "\n";
	}

	if (nCase == In_ascending_order_of_size_by_Greedy) {
		LogFile::instance()->m_ofBufferAllocation << "Buffer allocation results:\t" << "In_ascending_order_of_size_by_Greedy:" << "\n";
	}

	if (nCase == In_descending_order_of_size_by_Greedy) {
		LogFile::instance()->m_ofBufferAllocation << "Buffer allocation results:\t" << "In_descending_order_of_size_by_Greedy:" << "\n";
	}

	if (nCase == In_ascending_order_of_formula_by_Greedy) {
		LogFile::instance()->m_ofBufferAllocation << "Buffer allocation results:\t" << "In_ascending_order_of_formula_by_Greedy:" << "\n";
	}

	if (nCase == In_descending_order_of_formula_by_Greedy) {
		LogFile::instance()->m_ofBufferAllocation << "Buffer allocation results:\t" << "In_descending_order_of_formula_by_Greedy:" << "\n";
	}

	if (nCase == Random_allocation) {
		LogFile::instance()->m_ofBufferAllocation << "Buffer allocation results:\t" << "Random_allocation" << "\n";
	}
	
	//std::cout << "缓存方案：\n";
	
	for (std::vector<Resource *>::iterator it = vecResRet.begin(); it != vecResRet.end(); ++ it) {
		LogFile::instance()->m_ofBufferAllocation
			<< "\t-ResID:\t" << (*it)->GetResID()
			<< "\t-ResType:\t" << (*it)->GetResType()
			<< "\t-ResSize:\t" << (*it)->GetResSize()
			<< "\t-ResPop:\t" << (*it)->GetResPop()
			<< "\t-ResTime:\t" << (*it)->GetResTime() << "\n\n";

// 		std::cout << "\t-ResID:\t" << (*it)->GetResID()
// 			<< "\t-ResType:\t" << (*it)->GetResType()
// 			<< "\t-ResSize:\t" << (*it)->GetResSize()
// 			<< "\t-ResPop:\t" << (*it)->GetResPop()
// 			<< "\t-ResTime:\t" << (*it)->GetResTime() << "\n\n";
	}
}

// 记录公交车的缓存
void NSRunner::Record_Bus_Buffer(std::vector<Resource *> *pBusR, int nCase)
{

	assert (NULL != pBusR);
	assert (nCase >= 0);
	if (NULL == pBusR) {
		return;
	}

	LogFile::instance()->m_ofInfoBus << "----------------------------------------------Bus Buffer-------------------------------------------\n\n";
	
	if (nCase == Knapsack_allocation_by_DynamicProgram) {
		LogFile::instance()->m_ofInfoBus << "\t" << "Knapsack_allocation_by_DynamicProgram:" << "\n\n";
	}

	if (nCase == In_ascending_order_of_size_by_Greedy) {
		LogFile::instance()->m_ofInfoBus << "\t" << "In_ascending_order_of_size_by_Greedy:" << "\n";
	}

	if (nCase == In_descending_order_of_size_by_Greedy) {
		LogFile::instance()->m_ofInfoBus << "\t" << "In_descending_order_of_size_by_Greedy:" << "\n";
	}

	if (nCase == In_ascending_order_of_formula_by_Greedy) {
		LogFile::instance()->m_ofInfoBus << "\t" << "In_ascending_order_of_formula_by_Greedy:" << "\n";
	}

	if (nCase == In_descending_order_of_formula_by_Greedy) {
		LogFile::instance()->m_ofInfoBus << "\t" << "In_descending_order_of_formula_by_Greedy:" << "\n";
	}

	if (nCase == Random_allocation) {
		LogFile::instance()->m_ofInfoBus << "\t" << "Random_allocation" << "\n";
	}

	for (std::vector<Resource *>::iterator it = pBusR->begin(); it != pBusR->end(); ++ it) {
		LogFile::instance()->m_ofInfoBus
			<< "\t-ResID:\t" << (*it)->GetResID()
			<< "\t-ResType:\t" << (*it)->GetResType()
			<< "\t-ResSize:\t" << (*it)->GetResSize()
			<< "\t-ResPop:\t" << (*it)->GetResPop()
			<< "\t-ResTime:\t" << (*it)->GetResTime() << "\n\n";

// 		std::cout << "\t-ResID:\t" << (*it)->GetResID()
// 			<< "\t-ResType:\t" << (*it)->GetResType()
// 			<< "\t-ResSize:\t" << (*it)->GetResSize()
// 			<< "\t-ResPop:\t" << (*it)->GetResPop()
// 			<< "\t-ResTime:\t" << (*it)->GetResTime() << "\n\n";
	}
}

// 记录每种方案中的pd/s值和所对应的hit rate和loss rate.
void NSRunner::Record_pdf_Results(int nCase)
{
	double dAvg_pds = 0.0;
	double dAvg_pds_all = 0.0;
	unsigned int nCount = 0;

	BUS_CONTAINER *pAllBus = Get_pContainer_of_all_Buses();
	BUS_CONTAINER_ITER it = pAllBus->begin();
	CBusNode *pBus = it->second;

	std::vector<Resource *> vecBusRes = pBus->m_pVecResource;

	if (nCase == Knapsack_allocation_by_DynamicProgram) {
		LogFile::instance()->m_ofHitRate_LossRate_Results << "Case:\t" << "Knapsack_allocation_by_DynamicProgram:\t";
	}

	if (nCase == In_ascending_order_of_size_by_Greedy) {
		LogFile::instance()->m_ofHitRate_LossRate_Results << "Case:\t" << "In_ascending_order_of_size_by_Greedy:\t";
	}

	if (nCase == In_descending_order_of_size_by_Greedy) {
		LogFile::instance()->m_ofHitRate_LossRate_Results << "Case:\t" << "In_descending_order_of_size_by_Greedy:\t";
	}

	if (nCase == In_ascending_order_of_formula_by_Greedy) {
		LogFile::instance()->m_ofHitRate_LossRate_Results << "Case:\t" << "In_ascending_order_of_formula_by_Greedy:\t";
	}

	if (nCase == In_descending_order_of_formula_by_Greedy) {
		LogFile::instance()->m_ofHitRate_LossRate_Results << "Case:\t" << "In_descending_order_of_formula_by_Greedy:\t";
	}

	if (nCase == Random_allocation) {
		LogFile::instance()->m_ofHitRate_LossRate_Results << "Case:\t" << "Random_allocation:\t";
	}
	
	for (std::vector<Resource *>::iterator it = vecBusRes.begin(); it != vecBusRes.end(); ++ it) {
		nCount ++;
		double dP = (*it)->GetResPop();
		double dD = (*it)->GetResTime();
		unsigned int dS = (*it)->GetResSize();
		dAvg_pds = (dP * dD) / (double)dS;
		dAvg_pds_all += dAvg_pds;
	}
	dAvg_pds_all /= (double)nCount;

	LogFile::instance()->m_ofHitRate_LossRate_Results << "pd/s:\t" << dAvg_pds_all;
}

void NSRunner::Record_TestCase_Results()
{
	unsigned int nHitRate = 0;
	unsigned int nLossRate = 0;
	
	double dHit = 0.0;
	double dLoss = 0.0;

	CAR_CONTAINER* pAllCars = Get_pContainer_of_all_Cars();

	for (CAR_CONTAINER_ITER it = pAllCars->begin(); it != pAllCars->end(); ++ it) {
		CCarNode *pCar = it->second;
		if (pCar->GetSuccess()) 
			++ nHitRate;
		if (pCar->isCarOutofTime())
			++ nLossRate;
	}

	dHit = (double)nHitRate / CAR_NUM;
	dLoss = (double)nLossRate / CAR_NUM;

	LogFile::instance()->m_ofHitRate_LossRate_Results << "\tHitRate:\t" << dHit << "\tLossRate:\t" << dLoss << "\n";
}

//记录其他的一些信息，比如模拟次数，模拟时间等.
void NSRunner::Record_Other_Information(int ntimes, int ntime)
{
	LogFile::instance()->m_ofHitRate_LossRate_Results << "Times:\t" << ntimes << "\tSimulationTime:\t" << ntime << "\t";
}

// ----------------------------------J.Read and Write file operation.---------------------------
// 1. path
void NSRunner::ReadFromFile_path(ifstream &inFile, char *filename/*, std::vector<Path *> pPath*/)
{
	assert ( NULL != filename );
	if (NULL == filename) {
		return;
	}

	double dReadfromFile1 = 0.0;
	double dReadfromFile2 = 0.0;
	string s, s1,s2;
	int j = 0;
	int nCount = 0;

	Path *p = NULL;

	inFile.open(filename);
	if (!inFile) {
		return; //打开文件失败.
	}
	
	else{
		while(getline(inFile, s)) {
			if (1 == s.size()) {
				p = new Path();
			}
			else {
				nCount ++;
				for (unsigned int i = 0; i < s.size(); i ++) {
					if (s[i] == ',') {
						s1 = s.substr(j, i - j);
						s2 = s.substr(i + 1, s.size() - i);

						dReadfromFile1 = atof(s1.c_str());
						dReadfromFile2 = atof(s2.c_str());
						Point * x = new Point(dReadfromFile1, dReadfromFile2);
						p->m_vecPath.push_back(x);
						
						if (nCount == 1) {
							p->SetBeginPoint(dReadfromFile1, dReadfromFile2);
						}

						if (nCount == BUS_STOP) {
							p->SetEndPoint(dReadfromFile1, dReadfromFile2);
						}
						//j = i + 1;
						break;
					}
				}
			}
			if (nCount == BUS_STOP) {
				m_vecBusPath.push_back(p);
				nCount = 0;
			}

		}
	}
	
	//m_vecBusPath = pPath;

	inFile.close();
// 	for (vector< *>::iterator it = dVec.begin(); it != dVec.end(); ++ it) {
// 		cout << (*it)->dx << " " << (*it)->dy << "\n";
// 	}
}
void NSRunner::WriteFromFile_path(ofstream &outFile, char *filename/*, std::vector<Path *> pPath*/)
{
	assert(NULL != filename);
	if (NULL == filename) {
		return;
	}
	
	std::vector<Point *> pPoint;
	
	outFile.open(filename);
	if (!outFile) {
		return; //打开文件失败.
	}
	else {
		for (int i = 0; i < BUS_PATH; i ++) {
			pPoint = m_vecBusPath[i]->m_vecPath;
			outFile << i + 1 << "\n";
			for (std::vector<Point *>::iterator it = pPoint.begin(); it != pPoint.end(); ++ it) {
				outFile << (*it)->m_dLoc_X << "," << (*it)->m_dLoc_Y << "\n";
			}
		}
	}
	outFile.close();
}

// 2. all resources.
void NSRunner::ReadFromFile_resources(ifstream &inFile, char *filename/*, std::vector<Resource *> pRes*/)
{
	assert ( NULL != filename );
	if (NULL == filename) {
		return;
	}
	
	int nResId = 0;
	char cResType;
	unsigned int nResSize = 0;
	double dResPop = 0.0;
	double dResTime = 0.0;

	string s, s1;
	int j = 0;
	//int k = 0;
	int nCount = 0;

	inFile.open(filename);
	if (!inFile) {
		return; //打开文件失败.
	}

	else{
		while(getline(inFile, s)) {
			for (unsigned int i  = 0; i < s.size(); i ++) {
				if (s[i] == ' ') {
					nCount ++;
				//	k = i;
				}
				if (nCount == 1 && s[i] == ' ') {
					s1 = s.substr(j, i - j);
					j = i + 1;
					nResId = atoi(s1.c_str());
				}
				if (nCount == 2 && s[i] == ' ') {
					s1 = s.substr(j, i - j);
					j = i + 1;
					cResType = s1[0];
				}
				if (nCount == 3 && s[i] == ' ') {
					s1 = s.substr(j, i - j);
					j = i + 1;
					nResSize = atoi(s1.c_str());
				}
				if (nCount == 4 && s[i] == ' ') {
					s1 = s.substr(j, i - j);
					j = i + 1;
					dResPop = atof(s1.c_str());
				}
				if (nCount == 5 && s[i] == ' ') {
					s1 = s.substr(j, i - j);
					j  = i + 1;
					dResTime = atof(s1.c_str());
				}
			}
			Resource *pRes = new Resource(nResId, cResType, nResSize, dResPop, dResTime);
			m_mapResources.push_back(pRes);

			nCount = 0;
			j = 0;
		}
	}
	//m_vecBusPath = pPath;
	inFile.close();
}

void NSRunner::WriteFromFile_resources(ofstream &outFile, char *filename/*, std::vector<Resource *> pRes*/)
{
	assert(NULL != filename);
	if (NULL == filename) {
		return;
	}

	//std::vector<Point *> pPoint;

	outFile.open(filename);
	if (!outFile) {
		return; //打开文件失败.
	}
	else {
		for (std::vector<Resource *>::iterator it = m_mapResources.begin(); it != m_mapResources.end(); ++ it) 
			outFile << (*it)->GetResID() << " " << (*it)->GetResType() << " " << (*it)->GetResSize() << " " << (*it)->GetResPop() << " " << (*it)->GetResTime() << " \n";
	}
	outFile.close();
}


// 3. car resources.
void NSRunner::ReadFromFile_carRes(ifstream &inFile, char *filename/*, std::vector<char> pCarRes*/)
{
	assert ( NULL != filename );
	if (NULL == filename) {
		return;
	}

	char ctype;
	string s;

	inFile.open(filename);
	if (!inFile) {
		return; //打开文件失败.
	}

	else{
		while(getline(inFile, s)) {
			ctype = s[0];
			m_vecCarResources.push_back(ctype);
		}
	}
	//m_vecBusPath = pPath;
	inFile.close();
}

void NSRunner::WriteFromFile_carRes(ofstream &outFile, char *filename/*, std::vector<char> pCarRes*/)
{
	assert(NULL != filename);
	if (NULL == filename) {
		return;
	}

	//std::vector<Point *> pPoint;

	outFile.open(filename);
	if (!outFile) {
		return; //打开文件失败.
	}
	else {
		for (std::vector<char>::iterator it = m_vecCarResources.begin(); it != m_vecCarResources.end(); ++ it) 
			outFile << *it << "\n";
	}
	outFile.close();
}