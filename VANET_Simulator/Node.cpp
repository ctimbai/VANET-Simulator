#include "Node.h"



//-----------------------------------------------------------------
// CNode::CNode(double dLoc_x /* = 0.0 */, double dLoc_y /* = 0.0 */, double dVelocity /* = 0.0 */)
// {
// 	m_dLoc_X = dLoc_x;
// 	m_dLoc_Y = dLoc_y;
// 	m_dVelocity = dVelocity;
// }

// ------------------ A. location and velocity--------------------
void CNode::SetLocation(double dLoc_x, double dLoc_y)
{
	m_dLoc_X = dLoc_x;
	m_dLoc_Y = dLoc_y;
}
void CNode::SetLoc_X( double dLoc_x )
{
	m_dLoc_X = dLoc_x;
}

void CNode::SetLoc_Y( double dLoc_y )
{
	m_dLoc_Y = dLoc_y;
}
double CNode::GetLoc_X()
{
	return m_dLoc_X;
}

double CNode::GetLoc_Y()
{
	return m_dLoc_Y;
}

void CNode::SetVelocity(double dVelocity)
{
	assert( 0.0 <= dVelocity );
	if ( 0.0 > dVelocity )
	{
		cerr << "Error: the dVelocity must be positive or 0.0.\n";
		//!!!!!!!!!Log
		
		//LogFile::instance()->m_ofErrLog << "Error: the dVelocity must be positive or 0.0.\n";
		return;
	}

	m_dVelocity = dVelocity;
}

double CNode::GetVelocity()
{
	return m_dVelocity * NS_SPEED_RATIO;
}

double CNode::GetTrueVelocity()
{
	return m_dVelocity;
}

// --------------------B.Mobility ------------------------
bool CNode::Get_isStartMove()
{
	return m_bStartMove;
}

void CNode::Set_isStartMove(bool bBeginMove)
{
	m_bStartMove = bBeginMove;
}


// ===================== Bus node==============================

// ------------------ A. Path and Direction -------------------
// get a path;
Path* CBusNode::GetAPath()
{
	return m_pBusPath;
}

//set the path.
void CBusNode::SetAPath(Path *p)
{
	m_pBusPath = p;
}

//set the current direction.
void CBusNode::SetBusCurDirection(double bCurDir)
{
	m_dBusCurDirection = bCurDir;
}

//get the current direction.
double CBusNode::GetBusCurDirection()
{
	return m_dBusCurDirection;
}

// reset the bus direction rely on the next point of path.
void CBusNode::Reset_Direction_rely_on_path(double dLocB_x, double dLocB_y, double dLoc_x, double dLoc_y)
{
	double dCurDirection = NSMath::ArcTanTwoPoint(dLocB_x, dLocB_y, dLoc_x, dLoc_y);
	SetBusCurDirection(dCurDirection);
}

// 根据bus的位置确定其所在路段的开始节点
Point* CBusNode::Get_PathBeginPoint_Of_Bus_Location(double dLoc_x, Path *pPath)
{
	assert (NULL != pPath);
	if (NULL == pPath) {
		return NULL;
	}

	std::vector<Point *> point = pPath->m_vecPath;
	std::vector<Point *>::iterator it = point.begin();
	std::vector<Point *>::iterator itR = point.begin();

	for (; it != point.end();) {
		double dlocx = (*it)->m_dLoc_X;

		if (dLoc_x < dlocx) {

			double dlocRx = (*itR)->m_dLoc_X;
			double dlocRy = (*itR)->m_dLoc_Y;

			Point *pRet = new Point(dlocRx, dlocRy);

			return pRet;
		}
		else
			itR = it;
		++ it;
	}	
	return NULL;
}

// 根据bus的位置确定其所在路段的终止节点
Point *CBusNode::Get_PathEndPoint_Of_Bus_Location(double dLoc_x, Path *pPath)
{
	assert (NULL != pPath);
	if (NULL == pPath) {
		return NULL;
	}

	std::vector<Point *> point = pPath->m_vecPath;
	std::vector<Point *>::iterator it = point.begin();
	
	for (; it != point.end(); ++ it) {
		double dlocx = (*it)->m_dLoc_X;
		double dlocy = (*it)->m_dLoc_Y;

		Point *pRet = new Point(dlocx, dlocy);

		if (dLoc_x < dlocx) {
			return pRet;
		}
	}	
	return NULL;
}

// -------------------B. Resource. ------------------------------------

// 	// buffer the  resources.
// 	void SetTheResources(std::vector<Resource> R);
// 
// 	// Get the resources of the buffer.
// 	std::vector<Resource>* GetTheResources_ofBuffer();

// 在bus中找是否有car所请求的资源
bool CBusNode::FindCarRequestRes_IfAtBus(char type)
{
	//BUS_RESOURCE * pAllRes = get_BusContainer_Resource();
	for (BUS_RESOURCE_ITER it = m_pVecResource.begin(); it != m_pVecResource.end(); ++ it) {
		if (type == ((*it)->GetResType())) {
			return true;
		}
	}
	return false;
}

// 根据资源类型得到所对应的的资源.
Resource * CBusNode::GetResource_viaResType(char type)
{
	//BUS_RESOURCE * pAllRes = get_BusContainer_Resource();
	for (BUS_RESOURCE_ITER it = m_pVecResource.begin(); it != m_pVecResource.end(); ++ it) {
		if (type == ((*it)->GetResType())) {
			return *it;
		}
	}
	// 报错，没有资源.
	return NULL;	
}

// 得到公交车缓存的资源.
BUS_RESOURCE * CBusNode::get_BusContainer_Resource()
{
	return &m_pVecResource;
}

// 设置公交车缓存的资源.
void CBusNode::SetBusAllocationResource(BUS_RESOURCE pBusRes)
{
	m_pVecResource = pBusRes;
}

// 将bus的资源设为空.
void CBusNode::ResetBusBufferToEmpty()
{
	for (BUS_RESOURCE_ITER it = m_pVecResource.begin(); it != m_pVecResource.end(); ++ it) {
		(*it)->SetResID(0);
		(*it)->SetResType(' ');
		(*it)->SetResPop(0.0);
		(*it)->SetResSize(0);
		(*it)->SetResTime(0.0);
	}
}

// -----------------------C. Contact ------------------------

// 得到bus的传输范围
double CBusNode::GetBusTransRange()
{
	return m_dBusTransRange;
}

void CBusNode::SetBusId(int id)
{
	m_nBusID = id;
}

int CBusNode::GetBusId()
{
	return m_nBusID;
}

void CBusNode::SetBusRecordCount(unsigned int nC)
{
	nCount_Record_Bus = nC;
}

void CBusNode::SetBusRecordCount_IN()
{
	nCount_Record_Bus ++;
}

unsigned int CBusNode::GetBusRecordCount()
{
	return nCount_Record_Bus;
}

//=================================Car Node.================================

// get current direction.
double CCarNode::GetCurDirection_RWALK()
{
	return m_dCarCurDirection;
}

// Set current direction.
void CCarNode::SetCurDirection_RWALK(double dCarCurDirection)
{
	m_dCarCurDirection = dCarCurDirection;
}

// 重置方向用一个确定的值.
// Reset the Direction with an determined value of radian Angle.
void CCarNode::Reset_Direction_RWALK(double dRadianValue)
{
	assert( 0<= dRadianValue && dRadianValue <= 2*PI );
	m_dCarCurDirection = dRadianValue;
}

// Reset the Direction randomly with an radian Angle in [dLowerBound, dUpperBound).
void CCarNode::Reset_Direction_random_RWALK( double dLowerBound, double dUpperBound )
{
	m_dCarCurDirection = Create_a_new_random_Direction(dLowerBound, dUpperBound);
}

// Return an Random Radian Angle in [dLowerBound, dUpperBound).
double CCarNode::Create_a_new_random_Direction(double dLowerBound, double dUpperBound)
{
	assert(dLowerBound <= dUpperBound);

	double dNewDirection = m_pObjRC->GetRdmRealNum(dLowerBound, dUpperBound);
	return dNewDirection;
}

// --------------------D.Contact ---------------------

void CCarNode::SetBusID_toEmpty()
{
	m_vecBusID.clear();
// 		for (std::vector<int>::iterator it = m_vecBusID.begin(); it != m_vecBusID.end();) {
// 			m_vecBusID.erase(it ++);
// 		}
}

void CCarNode::SetBusID(int id)
{
	m_vecBusID.push_back(id);
}


// 得到Car的传输范围
double CCarNode::GetCarTransRange()
{
	return m_dCarTransRange;
}

// 得到Car的延迟容忍度
bool CCarNode::isCarOutofTime()
{
	return m_isOutofTime;
}

// 设置Car是否超时的信息
void CCarNode::SetCarisOutofTime(bool isOutOftime)
{
	m_isOutofTime = isOutOftime;
}

// 设置Car所请求资源的大小值
void CCarNode::SetCarRequestResSize(unsigned int nSize)
{
	m_nSize = nSize;
}

// 得到资源的大小
unsigned int CCarNode::GetCarResSize()
{
	return m_nSize;
}

// 设置Car所请求的资源
void CCarNode::SetCarRequestResourceType(char cType)
{
	m_cType = cType;
}

// 得到car所请求的资源
char CCarNode::GetCarRequestResourceType()
{
	return m_cType;
}

// 设置相遇的次数
void CCarNode::SetContactNum()
{
	m_nNumContant_WithBus ++;
}

void CCarNode::SetContactNum_toNum(int nNum)
{
	m_nNumContant_WithBus = nNum;
}

// 得到相遇的次数
unsigned int CCarNode::GetContactNum()
{
	return m_nNumContant_WithBus;
}

// 得到第一次与bus相遇的标志
// bool CCarNode::GetFirstContactWithBus()
// {
// 	return m_isFirstContactBus;
// }
// 
// 设置第一次与bus相遇的标志
// void CCarNode::SetFirstContactWithBus(bool isFirst)
// {
// 	m_isFirstContactBus = isFirst;
// }

// 得到取数据成功的标志
bool CCarNode::GetSuccess()
{
	return m_isSuccess_to_GetTheFullResource;
}

// 设置取数据成功的标志
void CCarNode::SetSuccess(bool isSuccess)
{
	m_isSuccess_to_GetTheFullResource = isSuccess;
}

// 设置car请求资源的时间
void CCarNode::SetCarRequestTime(double dRTime)
{
	m_dRequestTime = dRTime;
}

// 得到car请求资源的时间
double CCarNode::GetCarRequestTime()
{
	return m_dRequestTime;
}

// 设置car接受资源的时间
void CCarNode::SetCarReceiveTime(double dRTime)
{
	m_dReceiveTime = dRTime;
}

// 得到car接受资源的时间
double CCarNode::GetCarReceiveTime()
{
	return m_dReceiveTime;
}

// 设置资源的时间
void CCarNode::SetCarResTime(double dTime)
{
	m_dTime = dTime;
}

// 得到资源的时间
double CCarNode::GetCarResTime()
{
	return m_dTime;
}

int CCarNode::GetCarID()
{
	return m_nCarID;
}

void CCarNode::SetCarID(int id)
{
	m_nCarID = id;
}

void CCarNode::SetCarRecordCount(unsigned int nC)
{
	nCount_Record_Car = nC;
}

unsigned int CCarNode::GetCarRecordCount()
{
	return nCount_Record_Car;
}

void CCarNode::SetCarRecordCount_IN()
{
	nCount_Record_Car ++;
}