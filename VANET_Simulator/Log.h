#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <fstream>

//--------------- Define the class of Log --------------------
class LogFile 
{
private:
	LogFile();
	~LogFile();
	LogFile(const LogFile& );

public:
	static LogFile* instance();

private:

	static LogFile* pObjLog;

	void CloseFiles();
public:
	//--------------- A. NS running process Log---------------

	//1 Error log file, record the errors and warnings
	static std::ofstream m_ofErrLog;

	//2 Running log file, record the running results and hints.
	static std::ofstream m_ofRunLog;

	//3 Forwarding log file, record the forwarding actions.
	//static std::ofstream m_ofForwardLog;

	//4 Location Log file, record the node's moving actions and locations.
	//static std::ofstream m_ofLocLog;


	// ----------------B. Node and Path Location Log ------------------
	// 1. bus path
	static std::ofstream m_ofLocPath;

	// 2. bus node
	static std::ofstream m_ofLocBus;
	static std::ofstream m_ofInfoBus;

	// 3. car node.
	static std::ofstream m_ofLocCar;

	// . car info
	static std::ofstream m_ofInfoCar;

	// 4. resources.
	static std::ofstream m_ofResource;

	// 5. buffer allocation.
	static std::ofstream m_ofBufferAllocation;

	//......

	// -----------------C. node movement process log ---------------
	// 1. bus movement.
	static std::ofstream m_ofMovementBus;

	// 2. car movement.
	static std::ofstream m_ofMovementCar;


	// -----------------D. Contact process log. --------------------
	// 1. Contact
	static std::ofstream m_ofContact;

	// ------------------E. results.-----------------------------
	static std::ofstream m_ofHitRate_LossRate_Results;


	//--------------- B. Message propagation process Log-------

	//1 Trace the state of bus at time t.
	static std::ofstream m_ofTraceBusLog;

	//2 Trace the state of car at time t.
	static std::ofstream m_ofTraceCarLog;

	//3 Record the Delivery Ratio of all buses.
	static std::ofstream m_ofBusDeliveryRatioLog;

	//4 Record the Receive Ratio of all Cars.
	static std::ofstream m_ofCarReceiveRatioLog;

	//......

	//------------------- B. The ultimate results Log-------------------

	//1 Record the ultimate 

	//2 Trace and record the Delay of the bus.
	static std::ofstream m_ofBusDelay;

	//3 Trace and record the Delay of the car.
	static std::ofstream m_ofCarDelay;
};

#endif//_LOG_H_