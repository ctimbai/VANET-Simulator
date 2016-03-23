#ifndef _NS_MATH_H_
#define _NS_MATH_H_

#include "BaseDef.h"
#include "Resource.h"
#include <cmath>
#include <vector>

class NSMath 
{
public:
	NSMath();
	~NSMath() { }

public:
	//Get the Euclid distance between two points:(x1,y1),(x2,y2).
	static double EuclidDistance(_in double x1, _in double y1, _in double x2, _in double y2);

	// 计算两个点之间的夹角
	static double ArcTanTwoPoint(_in double x1, _in double y1, _in double x2, _in double y2);

	/*
	Sort the numbers increasingly in the bubble method.
	*/
	static void BubbleSort1_Double( _out std::vector<double> &vecD );
	static void BubbleSort_Double( _out std::vector<double> &vecD );
	static void BubbleSort_Int( _out std::vector<int> &vecInt );
	static void BubbleSort1_Int( _out std::vector<int> &vecInt );

	// Sort with sort.
	static bool CmpResWithSize_FromLittleToBig(Resource *res1,Resource *res2);
	static bool CmpResWithSize_FromBigToLittle(Resource *res1,Resource *res2);

	static bool CmpResWithFomu_FromLittleToBig(Resource *res1,Resource *res2);
	static bool CmpResWithFomu_FromBigToLittle(Resource *res1,Resource *res2);



};
#endif//_NS_MATH_H_