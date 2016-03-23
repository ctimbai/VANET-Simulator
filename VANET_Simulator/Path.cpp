//#include "stdafx.h"

#include "Path.h"

#include <cassert>
#include <iostream>
using namespace std;
// void Path::SetBeginPoint(Point &p) // set the point of begin;
// {
// // 	m_dBeginPoint->SetLoc_X(p.GetLoc_X());
// // 	m_dBeginPoint->SetLoc_Y(p.GetLoc_Y());
// }

Point* Path::GetBeginPoint()
{
	return m_dBeginPoint;
}

Point* Path::GetEndPoint()
{
	return m_dEndPoint;
}

void Path::SetBeginPoint(Point* pBp)
{
	m_dBeginPoint = pBp;
}

void Path::SetBeginPoint(double dx, double dy)
{
	m_dBeginPoint = new Point(dx, dy);
}

void Path::SetEndPoint(double dx, double dy)
{
	m_dEndPoint = new Point(dx, dy);
}

bool Path::isBeyondTheTopo(double dX, double dY) // Judge a path whether beyond the range of topo;
{
	assert(dX <= TOPO_MAX_X && dX >= TOPO_MIN_X);
	assert(dY <= TOPO_MAX_Y && dY >= TOPO_MIN_Y);
	if(dX < TOPO_MIN_X || dX > TOPO_MAX_X || dY < TOPO_MIN_Y || dY > TOPO_MAX_Y) {
		//!!!!出错！
		return false;
	}

	return true;
}

bool Path::isInRadiiOfPoint(double dX, double dY/*, Point * pre*/)
{
	assert(dX <= TOPO_MAX_X && dX >= TOPO_MIN_X);
	assert(dY <= TOPO_MAX_Y && dY >= TOPO_MIN_Y);
	if(dX < TOPO_MIN_X || dX > TOPO_MAX_X || dY < TOPO_MIN_Y || dY > TOPO_MAX_Y) {
		//!!!!出错！
		return false;
	}

	// 	if (dX < pre->m_dLoc_X || dY < pre->m_dLoc_Y)
	// 		return false;

	// 	if ((dX - pre->m_dLoc_X) > BUS_RADII || (dY - pre->m_dLoc_Y) > BUS_RADII ) {
	// 		return false;
	// 	}

	return true;
}

void Path::BubbleSort(std::vector<Point *> &pfp)
{
	int nLen = (int)pfp.size();
	for ( int j = nLen - 1; j >0; j-- )
	{
		for ( int i = 0; i < j; i++ )
		{
			if ( pfp[i]->m_dLoc_X > pfp[i+1]->m_dLoc_X )
			{
				Point * dT = pfp[i];
				pfp[i] = pfp[i+1];
				pfp[i+1] = dT;
			}
		}
	}
}

void Path::GetAPath_By_APoint(int type) // get a path by a point;
{
	unsigned int nNumStop = 1;
	SetPathBeginPoint_FromFourAngle(type);

	m_vecPath.push_back(GetBeginPoint());
	// 	Point *pNext = GetNextPointRandom_viaAPoint();
	// 	PATHPOINT.push_back(pNext);
	// 	nNumStop ++;

	//产生10个bus stop
	Point *pT = new Point();
	while(nNumStop <= BUS_STOP) {
		Point *pNext = GetNextPointRandom_viaAPoint();
		pT = pNext;
		m_vecPath.push_back(pT);
		nNumStop ++;
	}
	this->BubbleSort(m_vecPath);
}



//随机产生一条路径
void Path::Create_A_Path_At_Random(RdmCtr *pObjRC)
{
	// 计数bus stop.
	unsigned int nNumStop = 0;

	//产生10个bus stop
	Point *pT = new Point();
	while(nNumStop < BUS_STOP) {
		Point *pNext = Get_A_Point_At_Random(pObjRC);
		pT = pNext;
		m_vecPath.push_back(pT);
		nNumStop ++;
	}

	// 将这些点从大到小排序
	this->BubbleSort(m_vecPath);

	// 设置排序后的开始节点
	PATHPOINT_ITER itB = m_vecPath.begin();
	double dx = (*itB)->m_dLoc_X;
	double dy = (*itB)->m_dLoc_Y;
	this->SetBeginPoint(dx, dy);

	// 设置排序后的终止节点.
	PATHPOINT_ITER itE = m_vecPath.end() - 1;
	double dEx = (*itE)->m_dLoc_X;
	double dEy = (*itE)->m_dLoc_Y;
	this->SetEndPoint(dEx, dEy);
}

/*
std::vector<Point *>* Path::Get_a_Path()
{
	unsigned int nNumStop = 1;
	std::vector<Point *> *pathpoint;

	pathpoint->push_back(GetBeginPoint());
	// 	Point *pNext = GetNextPointRandom_viaAPoint();
	// 	PATHPOINT.push_back(pNext);
	// 	nNumStop ++;

	//产生10个bus stop
	Point *pT = new Point();
	while(nNumStop <= BUS_STOP) {
		Point *pNext = GetNextPointRandom_viaAPoint();
		pT = pNext;
		pathpoint->push_back(pT);
		nNumStop ++;
	}
	this->BubbleSort(pathpoint);

	return pathpoint;
}
*/
// Get begin point of the path.
// Point* Path::GetBeginPointOfPath(std::vector<Point *> *p)
// {
// 
// }

//随机产生一个点
Point* Path::Get_A_Point_At_Random(RdmCtr *pObjRC)
{
	double  dLocX = 0.0;
	double  dLocY = 0.0;

	bool flag = true;
	//int i = 1;
	while(flag) {
		dLocX = pObjRC->GetRdmRealNum(TOPO_MIN_X, TOPO_MAX_X);
		dLocY = pObjRC->GetRdmRealNum(TOPO_MIN_Y, TOPO_MAX_Y);
		if (isBeyondTheTopo(dLocX, dLocY)) {
			flag = false;
		}
		//	++ i;
	}

	Point * p = new Point();
	p->m_dLoc_X = dLocX;
	p->m_dLoc_Y = dLocY;

	return p;
}

Point* Path::GetNextPointRandom_viaAPoint(/*Point *pPrePoint*/)
{
	//RdmCtr *rtr = new RdmCtr();
	double  dLocX = 0.0;
	double  dLocY = 0.0;

	bool flag = true;
	//int i = 1;
	while(flag) {
		//	rtr->SetRandomSeed(i);
		dLocX = rtr->GetRdmRealNum(TOPO_MIN_X, TOPO_MAX_X);
		dLocY = rtr->GetRdmRealNum(TOPO_MAX_X, TOPO_MAX_Y);
		if (isBeyondTheTopo(dLocX, dLocY)) {
			flag = false;
		}
		//	++ i;
	}

	Point * p = new Point();
	p->m_dLoc_X = dLocX;
	p->m_dLoc_Y = dLocY;

	// 	delete rtr;
	// 	rtr = NULL;
	return p;
}

//Get begin point of path from four angle of topology.
void Path::SetPathBeginPoint_FromFourAngle(int type)
{
	assert( type >= 0);
	if (type < 0) {
		//!!!!错误！
		return;
	}

	if (type == LEFT_BOTTOM_POINT) {
		SetBeginPoint(0.0, 0.0);
	}

	if (type == LEFT_TOP_POINT) {
		SetBeginPoint(0.0,500.0);
	}
}

// void Path::OutPutPathPoint()
// {
// 	for (PATHPOINT_ITER = PATHPOINT.begin(); PATHPOINT_ITER != PATHPOINT.end(); ++ PATHPOINT_ITER){
// 		cout << (*PATHPOINT_ITER)->m_dLoc_X << " " << (*PATHPOINT_ITER)->m_dLoc_Y << endl;
// 	}
// }

/*
// 通过一个点得到下一个点
Point * Path::GetNextPoint_viaAPoint(Point *p)
{
	assert ( NULL != p );
	if ( NULL == p ) {
		// !!!出错！
		return NULL;
	}

	for( PATHPOINT_ITER it = PATHPOINT.begin(); it != PATHPOINT.end(); ++ it) {
		if ( p == it )
			return ++ it;
	}

	return NULL;
}
*/
// 计算两个点之间的长度.
double CalculateTwoPointLength(Point *p1, Point *p2)
{
	assert (NULL != p1 && NULL != p2);
	if ( NULL == p1 || NULL == p2){
		//出错！！
		return -1.0;
	}
	double dlocX1 = p1->m_dLoc_X;
	double dlocY1 = p1->m_dLoc_Y;

	double dlocX2 = p2->m_dLoc_X;
	double dlocY2 = p2->m_dLoc_Y;
	
	double dLengthTwoPoint = NSMath::EuclidDistance(dlocX1, dlocY1, dlocX2, dlocY2);

	return dLengthTwoPoint;
}

// 计算两个点之间的夹角.
double CalculateTwoPointAngle(Point *p1, Point *p2)
{
	assert (NULL != p1 && NULL != p2);
	if ( NULL == p1 || NULL == p2){
		//出错！！
		return -1.0;
	}

	double dlocX1 = p1->m_dLoc_X;
	double dlocY1 = p1->m_dLoc_Y;

	double dlocX2 = p2->m_dLoc_X;
	double dlocY2 = p2->m_dLoc_Y;

	double twoPointAngle = NSMath::ArcTanTwoPoint(dlocX1, dlocY1, dlocX2, dlocY2);

	return twoPointAngle;
}


// 根据一个点得到该点所在路段的起始点
Point * Path::GetBeginPointOfAPoint(double dLoc_x, double dLoc_y)
{
	return NULL;
}