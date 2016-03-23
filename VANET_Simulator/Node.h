#ifndef _NODE_H_
#define _NODE_H_

//#include "Point.h"
#include "Path.h"
#include "Resource.h"
#include "NSMath.h"
#include "BaseControl.h"

#include <utility>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;


typedef vector< Resource* > BUS_RESOURCE;
typedef vector< Resource* >::iterator BUS_RESOURCE_ITER;

// =============== the base class of Node ==================
class CNode 
{
public:
	CNode(double dLoc_x = 0.0, double dLoc_y = 0.0, double dVelocity = 0.0, bool isStart = false):
		m_dLoc_X(dLoc_x), 
		m_dLoc_Y(dLoc_y),
		m_dVelocity(dVelocity), 
		m_bStartMove(isStart){}
	//	CNode(Point &p, double dVelocity = 0.0);
		virtual ~CNode() {}

	// ------------------ A. location and velocity. -------------
public:
	//	void SetLocation(Point &p);
	//	Point& GetPoint();

	void SetLocation(double dLoc_x, double dLoc_y);
	void SetLoc_X(double dLoc_x);
	void SetLoc_Y(double dloc_y);
	double GetLoc_X();
	double GetLoc_Y();

	void SetVelocity(double dVelocity);
	double GetVelocity();
	double GetTrueVelocity();

	// --------------------- B.mobility. ---------------------
public:
	bool Get_isStartMove();
	void Set_isStartMove(bool bBeginMove);


private:
	double	m_dLoc_X;     // X-axis
	double	m_dLoc_Y;     // Y-axis
	//	Point	m_dLoc_Point; // the point signing the location
	double	m_dVelocity;  //Velocity

private:
	bool	m_bStartMove; // the flag of starting move;
};

// ==================== Bus Node ==========================
class CBusNode: public CNode
{
public:
	//	CBusNode(Point &p, double dVelocity = 0.0);
	CBusNode(double dlocx = 0.0, double dlocy = 0.0, double dv = 0.0, bool isStart = false)
		:CNode(dlocx, dlocy, dv, isStart)
		, m_pBusPath( NULL )
		, m_dBusCurDirection( 0.0 )
		, m_dBusTransRange( BUS_TR )
		, m_nBusID (0)
		, nCount_Record_Bus(0){}

	//CBusNode()
	virtual ~CBusNode(){
		SAFELY_DELETE_PTR( m_pBusPath );
		m_dBusCurDirection = 0.0;

		Set_isStartMove(false);
	}

	// ------------------ A. Path and Direction -------------------
public:
	// get the bus's path.
	void Get_TheBus_path(CBusNode * pBusNode);
	// get a path;
	Path* GetAPath();

	//set the path.
	void SetAPath(Path *p);

	//set the current direction.
	void SetBusCurDirection(double bCurDir);

	//get the current direction.
	double GetBusCurDirection();

	// reset the bus direction rely on the next point of path.
	void Reset_Direction_rely_on_path(double dLocB_x, double dLocB_y, double dLoc_x, double dLoc_y );

	// 根据bus的位置确定其所在路段的开始节点
	Point *Get_PathBeginPoint_Of_Bus_Location(double dLoc_x, Path *pPath);

	// 根据bus的位置确定其所在路段的终止节点
	Point *Get_PathEndPoint_Of_Bus_Location(double dLoc_x, Path *pPath);
	
private:
	// every bus correspond to a path;	
	Path	*m_pBusPath;  

	// the curDrirection of bus.
	double	m_dBusCurDirection;

	// -------------------B. Resource. --------------
public:
	// buffer the  resources.
	void SetTheResources(std::vector<Resource> R);

	// Get the resources of the buffer.
	std::vector<Resource>* GetTheResources_ofBuffer();

	// 在bus中找是否有car所请求的资源
	bool FindCarRequestRes_IfAtBus(char type);

	// 得到公交车缓存的资源.
	BUS_RESOURCE * get_BusContainer_Resource();

	// 设置公交车缓存的资源.
	void SetBusAllocationResource(BUS_RESOURCE pBusRes);

	// 根据资源类型得到所对应的的资源.
	Resource * GetResource_viaResType(char type);

	// 将bus的资源设为空.
	void ResetBusBufferToEmpty();

public:
	BUS_RESOURCE	m_pVecResource; // 资源类型.

// -----------------------C. Contact ------------------------
public:
	//get the id of contact car.
//	int GetTheContactCar_ID();
//	int GetBusSelf_ID();

	// 得到bus的传输范围
	double GetBusTransRange();

	void SetBusId(int id);
	int GetBusId();

private:

	// the bus transmission range;
	double m_dBusTransRange;
	int m_nBusID;

public:
	void SetBusRecordCount(unsigned int nC);
	unsigned int GetBusRecordCount();
	void SetBusRecordCount_IN();

private:
	unsigned int nCount_Record_Bus;

};

// ===================== Car Node ===========================
class CCarNode: public CNode
{
public:
	CCarNode(double dlocx = 0.0, double dlocy = 0.0, double dv = 0.0, bool isStart = false, double carCurDirection = 0.0, unsigned int nNum = 0, bool isSuccess = false, char type = ' ', unsigned int nsize = 0, double dTime = 0.0, double dReqT = 0.0, double dRecT = 0.0, bool isOutTime = false, double dCarTransR = CAR_TR, bool first = false, int id = 0)
		:CNode(dlocx, dlocy, dv, isStart)
		, m_dCarCurDirection(carCurDirection)
		, m_nNumContant_WithBus(nNum)
		, m_isSuccess_to_GetTheFullResource(isSuccess)
		, m_cType(type)
		, m_nSize(nsize)
		, m_dTime(dTime)
		, m_dRequestTime(dReqT)
		, m_dReceiveTime(dRecT)
		, m_isOutofTime(isOutTime)
		, m_dCarTransRange(dCarTransR)
		, nCount_Record_Car(0)
		, m_nCarID(id){
			m_pObjRC = new RdmCtr();
		}


	virtual ~CCarNode(){
		SAFELY_DELETE_PTR( m_pObjRC );
		m_dCarCurDirection = 0.0;
		Set_isStartMove(false);
	}



private:

// ------------------- A.Direction -------------------
public:
	// get next direction via random.
	double GetCurDirection_ByRandom();

	// get current direction.
	double GetCurDirection_RWALK();

	// Set current direction.
	void SetCurDirection_RWALK(double dCarCurDirection);

	// 重置方向用一个确定的值.
	// Reset the Direction with an determined value of radian Angle.
	void Reset_Direction_RWALK(double dRadianValue);

	// 重置当前方向 for RWALK.
	// Reset the Direction randomly with an radian Angle in [dLowerBound, dUpperBound).
	void Reset_Direction_random_RWALK( double dLowerBound, double dUpperBound );

private:
	double m_dCarCurDirection;

// --------------------B.Mobility -------------------
private:
private:
	// Return an Random Radian Angle in [dLowerBound, dUpperBound).
	double Create_a_new_random_Direction(double dLowerBound, double dUpperBound);


//---------------------C.Resources ---------------------
public:
// 	// Generate car's resource via random.(the request resource)
// 	void SetCarResource_ByRandom();
// 	
// 	//get car's resource(one resource)
// 	Resource* GetCarResource();
// 
// 	bool FindCarRequestRes_IfAtBus(char type);
// 
// private:
// 	Resource * CarResource;


// --------------------D.Contact ---------------------

public:
	std::vector<int> m_vecBusID;

	void SetBusID_toEmpty();
	void SetBusID(int id);

public:

	// 得到Car的传输范围
	double GetCarTransRange();

	// 得到Car的延迟容忍度(及是否超时，没有必要在接受数据)
	bool isCarOutofTime();

	// 设置Car是否超时的信息
	void SetCarisOutofTime(bool isOutOftime);
	
	// 设置Car所请求资源的大小值
	void SetCarRequestResSize(unsigned int nSize);

	// 得到资源的大小
	unsigned int GetCarResSize();

	// 设置Car所请求的资源
	void SetCarRequestResourceType(char cType);

	// 得到car所请求的资源
	char GetCarRequestResourceType();

	// 设置相遇的次数
	void SetContactNum();
	void SetContactNum_toNum(int nNum);

	// 得到相遇的次数
	unsigned int GetContactNum();

	// 得到第一次与bus相遇的标志
	bool GetFirstContactWithBus();

	// 设置第一次与bus相遇的标志
	void SetFirstContactWithBus(bool isFirst);

	// 得到取数据成功的标志
	bool GetSuccess();

	// 设置取数据成功的标志
	void SetSuccess(bool isSuccess);

	// 设置car请求资源的时间
	void SetCarRequestTime(double dRTime);

	// 得到car请求资源的时间
	double GetCarRequestTime();

	// 设置car接受资源的时间
	void SetCarReceiveTime(double dRTime);

	// 得到car接受资源的时间
	double GetCarReceiveTime();

	// 设置资源的时间
	void SetCarResTime(double dTime);
	
	// 得到资源的时间
	double GetCarResTime();

	int GetCarID();
	void SetCarID(int id);

private:

	int m_nCarID;
	// the car tansmission range.
	double m_dCarTransRange;
	
	// is success to get full resource for car?
	bool m_isSuccess_to_GetTheFullResource;

	// car request type of resource.
	char m_cType; 

	// size of the resource.
	unsigned int m_nSize;

	// time of the resource.
	double m_dTime;

	// judge whether out of time.
	bool m_isOutofTime;

	// the contact number with bus.
	unsigned int m_nNumContant_WithBus;

	// car 请求资源的时间
	double m_dRequestTime;

	// car 得到资源的时间
	double m_dReceiveTime;

	// 是否第一次与bus相遇
	//bool m_isFirstContactBus;

public:
	void SetCarRecordCount(unsigned int nC);
	unsigned int GetCarRecordCount();
	void SetCarRecordCount_IN();

private:
	unsigned int nCount_Record_Car;

private:
	RdmCtr		*m_pObjRC;


};

#endif