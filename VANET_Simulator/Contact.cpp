#include "Contact.h"

// 判断两个节点是否在传输范围内
bool Contact::Judge_Two_Point_Whether_Within_Transmission_Range(CBusNode *pBus, CCarNode *pCar)
{
	double dBusTransR = pBus->GetBusTransRange();
	//double dCarTransR = pCar->GetCarTransRange();
	//double dTransRange = dBusTransR + dCarTransR;

	double dBusLocX = pBus->GetLoc_X();
	double dBusLocY = pBus->GetLoc_Y();

	double dCarLocX = pCar->GetLoc_X();
	double dCarLocY = pCar->GetLoc_Y();

	return The_Two_Point_Meet_each_Other_with_TR(dBusLocX, dBusLocY, dCarLocX, dCarLocY, dBusTransR);
}


// 两个节点相遇
bool Contact::The_Two_Point_Meet_each_Other_with_TR( double x1, double y1, double x2, double y2, double dTr)
{
	//double dTr1 = dTr * 0.1;

	double dDist = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
	if ( dDist <= dTr )
	{
		return true;
	}
	else	
		return false;
}

// 两个节点相遇
bool Contact::The_Two_Point_Meet_each_Other( double x1, double y1, double x2, double y2)
{
	double dDist = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
	if ( dDist <= m_dBusCarTransRange )
	{
		return true;
	}
	else	
		return false;
}


// 两辆车之间的交互
void Contact::Transmission_Between_Tow_Vehicles(CBusNode* pBus, CCarNode *pCar, double dCurTime, int nCase)
{
	assert(NULL != pBus);
	assert(NULL != pCar);
	assert(dCurTime > 0);
	
	double dJudgeOutTime = 0.0;

	// 判断两辆车是否在传输范围内
	if (Judge_Two_Point_Whether_Within_Transmission_Range(pBus, pCar)) {

		//std::cout << "bingo" << std::endl;

		
		
		
		// 判断当前这辆车是否超出了其延迟容忍度或取资源成功
		if ( false == pCar->isCarOutofTime() && false == pCar->GetSuccess()) {
			//得到Car所请求的资源类型
			char type = pCar->GetCarRequestResourceType();
			//在bus中寻找是否有该资源, 如果有，则继续.
			if (pBus->FindCarRequestRes_IfAtBus(type)) {

				//设置相遇的次数. + 1
				pCar->SetContactNum();
				
				int busID = pBus->GetBusId();
				pCar->SetBusID(busID);

				// 记录bus和car的相遇情况
				//Record_Bus_Car_Contact_Situation(pBus, pCar, nCase);

				// 如果相遇次数为第一次
				if (1 == pCar->GetContactNum()) {
					//设置car请求资源的时间为当前时间
					pCar->SetCarRequestTime(dCurTime);
					// 根据该类型找到所对应的资源
					Resource *pRes = pBus->GetResource_viaResType(type);
					// 获取该资源的大小和时间.
					unsigned int nSize = pRes->GetResSize();
					double dTime = pRes->GetResTime();
					//将该资源的时间和大小赋给car
					pCar->SetCarRequestResSize(nSize);
					pCar->SetCarResTime(dTime);

					//相遇次数是否和大小相等，是则说明取资源成功.
					if (pCar->GetContactNum() == pCar->GetCarResSize()) {
						//设置资源成功获取的标志
						pCar->SetSuccess(true);

						std::cout << "取资源成功！\n";
						//设置接受时间
						pCar->SetCarReceiveTime(dCurTime);

						// 记录bus和car的相遇情况
						Record_Bus_Car_Contact_Situation(pBus, pCar,nCase, dJudgeOutTime);
					}
				}
				// 假如不是第一次相遇
				else {
					//计算是否超时
					double dCarRTime = pCar->GetCarRequestTime();
					double dDelayTime = pCar->GetCarResTime();
					dJudgeOutTime = dCurTime - dCarRTime;
					//判断是否超时
					if (dJudgeOutTime > dDelayTime) {
						//设置超时和获取资源失败
						pCar->SetCarisOutofTime(true);
						pCar->SetSuccess(false);

						std::cout << "超时\n";

						// 记录bus和car的相遇情况
						Record_Bus_Car_Contact_Situation(pBus, pCar, nCase, dJudgeOutTime);
					}
					else {
						//相遇次数是否和大小相等，是则说明取资源成功.
						if (pCar->GetContactNum() == pCar->GetCarResSize()) {
						//设置资源成功获取的标志
						pCar->SetSuccess(true);

						std::cout << "取资源成功！\n";
						//设置接受时间
						pCar->SetCarReceiveTime(dCurTime);

						// 记录bus和car的相遇情况
						Record_Bus_Car_Contact_Situation(pBus, pCar,nCase, dJudgeOutTime);
						}
					}
				}
			}
		}
	}
}

// 记录bus和car的相遇情况
void Contact::Record_Bus_Car_Contact_Situation(CBusNode *pBus, CCarNode *pCar, int nCase, double dJudgeTime)
{
	int carID = pCar->GetCarID();
	std::vector<int> vecID = pCar->m_vecBusID;

	char cType = pCar->GetCarRequestResourceType();

	Resource *pRes = pBus->GetResource_viaResType(cType);

	unsigned int nSize = pRes->GetResSize();
	double dPop = pRes->GetResPop();
	double dTime = pRes->GetResTime();

	int dContact = pCar->GetContactNum();
	bool isOutTime = pCar->isCarOutofTime();
	bool isSuccess = pCar->GetSuccess();

	double dRequestTime = pCar->GetCarRequestTime();
	double dReceiveTime = pCar->GetCarReceiveTime();

	//std::cout << "hello11111111111111\n"; 
	

	LogFile::instance()->m_ofContact
		<< nCase << "\t";
	LogFile::instance()->m_ofContact << " ( ";
	for (std::vector<int>::iterator it = vecID.begin(); it != vecID.end(); ++ it) {
		LogFile::instance()->m_ofContact << *it << " ";
	}
	LogFile::instance()->m_ofContact << " ) \t"
		<< carID << "\t"
		<< cType << "\t"
		<< nSize << "\t"
		<< dPop << "\t"
		<< dTime << "\t"
		<< dContact << "\t"
		<< isOutTime << "\t"
		<< isSuccess << "\t"
		<< dRequestTime << "\t"
		<< dReceiveTime << "\t"
		<< dJudgeTime << "\n\n";
}