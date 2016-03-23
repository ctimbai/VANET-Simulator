#ifndef _NS_RUNNER_H_
#define _NS_RUNNER_H_

#include <map>
#include <vector>
#include <iostream>
#include <string>


#include "BaseControl.h"
#include "BaseDef.h"
#include "Topology.h"
#include "movement.h"
#include "Resource.h"
#include "Path.h"
#include "Node.h"
#include "SimulateTime.h"
#include "Contact.h"
#include "BufferAllocation.h"
#include "Log.h"


typedef std::vector<Path *> BUSPATH;
typedef std::vector<Path *>::iterator BUSPATH_ITER;

typedef std::vector<Resource *> RESOURCE;
typedef std::vector<Resource *>::iterator RESOURCE_ITER;

typedef std::map<int, CBusNode*> BUS_CONTAINER;
typedef std::map<int, CBusNode*>::iterator BUS_CONTAINER_ITER;

typedef std::map<int, CCarNode*> CAR_CONTAINER;
typedef std::map<int, CCarNode*>::iterator CAR_CONTAINER_ITER;

typedef std::vector<char> CAR_RESOURCE;
typedef std::vector<char>::iterator CAR_RESOURCE_ITER;

class NSRunner 
{
public:
	NSRunner();
	~NSRunner();

public:
// --------------------------------A. Topology----------------------------------------
public:
	// 1. Set the topology.
	void SetTheTopology( double dTopoWidth, double dTopoHeight);

private:
	Topology* m_pObjTopo;


// --------------------------------B. Bus Node----------------------------------------
public:
	// 1. Path

	// create a bus's path.
	void Create_a_Bus_Path(int type);

	// create all buses' path.
	void Create_Bus_Path(int nBusPath);

	// Create BUS_PATH path at random.
	void Create_Bus_Path_at_Random(int nBusPath);


	// 2. Bus

	// get all bus paths' begin point.
	std::vector<Point *> Get_All_Bus_Path_BeginPoint(int nBusPath);

	// Create bus at every path at their begin point.
	void Create_Bus_At_Path_BeginPoint(std::vector<Point *> pPoint);

	// Create bus at path begin point.
	void Create_Bus_At_All_Path_BeginPoint();

	// set all buses' Velocity.
	void Set_All_Buses_Velocity(double dV);

	// 判断bus是否到达path终点，如果没有，则向前移动一步
	bool Judge_Whether_a_bus_Arrival_Path_End(CBusNode *pBus);

	// 所有bus向前移动一步，并判断是否达到终点.
	bool Judge_Whether_All_buses_Arrival_Path_End();

	// 置所有bus为初识状态.
	void Reset_Bus_To_Begin();


public:
	// Get the bus Container.
	/*static */BUS_CONTAINER * Get_pContainer_of_all_Buses();

	static CBusNode* Get_pBusNode_ByBusID(int nBus_ID);

	static int Get_BusID_viaPNode(CBusNode * pBusNode);

	

	// Get Bus node via bus_id.
	//static 

private:
	//Path*					m_pBusPath;
	static BUSPATH			m_vecBusPath;
	static int				m_snBus_ID;
	static BUS_CONTAINER	m_mapBuses;

// --------------------------------C. Car Node----------------------------------------
public:
	// 1. Create cars at random location.
	void Create_Cars_At_Random_Location(int nCarNum, double dMinLoc_X, double dMaxLoc_X, double dMinLoc_Y, double dMaxLoc_Y);

	//2. Reset cars to begin.
	void Reset_Cars_To_Begin();


public:
	/*static */CAR_CONTAINER* Get_pContainer_of_all_Cars();

	static CCarNode* Get_pCarNode_ByCarID(int nCar_ID);

	static int Get_CarID_viaPNode(CCarNode * pCarNode);

	// set all Cars' Velocity.
	void Set_All_Cars_Velocity(double dV);

private:
	static int				m_snCar_ID;
	static CAR_CONTAINER	m_mapCars;

// --------------------------------D. Resources ----------------------------------------
public:
	// 1. Create all Resource rely on the RES_NUM.
	void Create_All_Resources(int nResNum);


	// 2. 创建所有car的请求资源类型.
	void Create_All_Car_Request_Resources(int nCarNum);

	// 2.
public:
	static RESOURCE*	Get_pContainer_of_all_Resources();
	
	static CAR_RESOURCE* Get_pContainer_of_all_Car_Resources();

private:
	static RESOURCE		m_mapResources;
	static CAR_RESOURCE m_vecCarResources;

// --------------------------------E. Buffer Allocation---------------------------------
public:
	// 1. Get the resources rely on several buffer allocation.
	std::vector<Resource *> Get_Buffer_Allocation(int nCase);

	// 2. Set all buses' buffer by getting resources from buffer allocation.
	void Set_Allocation_Resources_Buffer_in_Bus(std::vector<Resource *> pR, int nCase);

	// 3. Set all cars' buffer by random style.
	void Create_Cars_Resource_at_Random();

	// 4. Set All Buses' buffer rely on bus buffer allocation.
	void Set_Bus_Buffer_rely_on_Buffer_Allocation(int nCase);


private:
	BufferAllocation	*m_pObjBA;

// --------------------------------F. Mobility ----------------------------------------
public:
	// 1. Let all node Forward a step(Bus and car).
	void Let_All_Node_Forward_a_Step(int nMobility);

	// 2. Let all buses forward a step.(by path).
	void Let_All_Buses_Forward_a_Step();

	// 3. Let all cars forward a step.
	void Let_All_Cars_Forward_a_Step(int nMobility);

private:
	Movement	*m_pObjMovement;

// --------------------------------G. Contact. ----------------------------------------
public:
	// 1. Let all node check transmission chance.
	void Let_All_Node_Check_Transmission_Chance(int nCase);

	// 2. Let all node check contact rely on several buffer allocation case.
	void Let_All_Node_Check_Contact_rely_on_Buffer_Allocation(int nCase);

private:
	Contact		*m_pObjContact;
	// all object.
	RdmCtr		*m_pObjRC;


// --------------------------------H. SpeedUp -------------------------------------------
public:
	int NS_Runs_for_a_tick();

	void SetNSLastRunTime(int nsLastTime);

	int GetNSLastRunTime();


private:
	unsigned int m_nNS_tickCnt;	
	
	static int m_nNS_LastTime;



// --------------------------------I. Record and Log some information ----------------------
public:

	// record bus path location
	void Record_Bus_Path_Location(Path *pBusPath, int ith);
	
	// 记录所有产生的资源
	void Record_All_Resources_Begin();

	// 记录缓存方案产生的结果.
	void Record_Buffer_Allocation_Results(std::vector<Resource *> vecResRet, int nCase);

	// 记录公交车的缓存
	void Record_Bus_Buffer(std::vector<Resource *> *pBusR,int nCase);



	// 记录每种方案中的pd/s值和所对应的hit rate和loss rate.
	void Record_pdf_Results(int nCase);
	void Record_TestCase_Results();

	//记录其他的一些信息，比如模拟次数，模拟时间等.
	void Record_Other_Information(int ntimes, int ntime);


// ----------------------------------J.Read and Write file operation.---------------------------
	// 1. path
	void ReadFromFile_path(ifstream &inFile, char *filename/*, std::vector<Path *> pPath*/);
	void WriteFromFile_path(ofstream &outFile, char *filename/*, std::vector<Path *> pPat*/);

	// 2. all resources.
	void ReadFromFile_resources(ifstream &inFile, char *filename/*, std::vector<Resource *> pRes*/);
	void WriteFromFile_resources(ofstream &outFile, char *filename/*, std::vector<Resource *> pRes*/);

	// 3. car resources.
	void ReadFromFile_carRes(ifstream &inFile, char *filename/*, std::vector<char> pCarRes*/);
	void WriteFromFile_carRes(ofstream &outFile, char *filename/*, std::vector<char> pCarRes*/);
};

#endif//_NS_RUNNER_H_