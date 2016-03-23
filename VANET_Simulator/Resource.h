#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <vector>

class Resource
{
public:
	Resource(int id = 0, char type = ' ', unsigned int nsize = 0, double pop = 0.0, double dtime = 0.0):\
			m_cResType(type),
			m_nResID(id),
			m_dPopOfRes(pop),
			m_nResSize(nsize),
			m_dTimeOfDT(dtime) {}

	~Resource() { }

public:
	// Set
	void SetResType(char resType);
	void SetResID(int resId);
	void SetResPop(double resPop);
	void SetResSize(unsigned int resSize);
	void SetResTime(double resTime);
	// Get
	char GetResType();
	int GetResID();
	double GetResPop();
	unsigned int GetResSize();
	double GetResTime();
public:
	// get all resources' popularity.
	std::vector<double> GetAllResPop();

	// 得到符合Zipf分布的流行度
	double GetZipfResPop();

	
	//得到全部资源
	std::vector<Resource *> GetAResource();

	// get all resources' size(packets)
	std::vector<unsigned int> GetAllResSize();


private:
	char			m_cResType;  //The type of the resource.(show it with A.B.C..)
	int				m_nResID;    //Uniform ID of the Resource.
	double			m_dPopOfRes; //The Popularity of the Resource.
	unsigned int	m_nResSize;  //The size of the resource(show it with packets)
	double			m_dTimeOfDT; //The time of the delay tolerant towards users.
};
#endif//_RESOURCE_H_