#include "RdmCtr.h"
#include "Resource.h"

//-------------------------------------------------

// Resource::Resource()
// {
// 	m_cResType = '0';
// 	m_dPopOfRes = 0.0;
// 	m_nResID = 0;
// 	m_nResSize = 0;
// 	m_dTimeOfDT = 0.0;
// }

// Set
void Resource::SetResType(char resType)
{
	m_cResType = resType;
}

void Resource::SetResID(int resId)
{
	m_nResID = resId;
}

void Resource::SetResPop(double resPop)
{
	m_dPopOfRes = resPop;
}

void Resource::SetResSize(unsigned int resSize)
{
	m_nResSize = resSize;
}

void Resource::SetResTime(double resTime)
{
	m_dTimeOfDT = resTime;
}

// Get
char Resource::GetResType()
{
	return m_cResType;
}

int Resource::GetResID()
{
	return m_nResID;
}

double Resource::GetResPop()
{
	return m_dPopOfRes;
}

unsigned int Resource::GetResSize()
{
	return m_nResSize;
}

double Resource::GetResTime()
{
	return m_dTimeOfDT;
}

//----------------------------------------------------------
// get all resources' popularity.
// std::vector<double> Resource::GetAllResPop()
// {
// 	std::vector<double> vecdRes; // !!!!!注意：局部变量
// 	vecdRes = RdmCtr::GetRdmRealNumToOne(0,1,RES_NUM);
// 	return vecdRes;
// }

/*
// get all resources' size(packets)
std::vector<unsigned int> Resource::GetAllResSize()
{
	std::vector<unsigned int> vecnRes;
	vecnRes = ->GetRdmIntNum(0,10);
	RETCODE vecnRes;
}
*/

// 得到符合Zipf分布的流行度
// double Resource::GetZipfResPop()
// {
// 
// 	double dPR = 
// }

// 得到一个资源
// Resource * Resource::GetAResource()
// {
// 	double dResPop = 0.0;
// 	unsigned int nResSize = 0;
// 	char cResType = '';
// 
// 
// }
// 
// 得到全部资源
// std::vector<Resource *> Resource::GetAResource()
// {
// 	
// }