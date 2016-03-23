#include "Log.h"

// --------------------------A. NS Running Log File ------------------------
std::ofstream LogFile::m_ofErrLog("Trace\\NS_ErrLog.txt");
std::ofstream LogFile::m_ofRunLog("Trace\\NS_RunLog.txt");
//std::ofstream LogFile::m_ofLocLog("Trace\\NS_LocationLog.txt");

// --------------------------B. Node and path Log File-----------------------
std::ofstream LogFile::m_ofLocPath("Trace\\NS_PathLocationLog.txt");
std::ofstream LogFile::m_ofLocBus("Trace\\NS_BusLocationLog.txt");
std::ofstream LogFile::m_ofInfoBus("Trace\\NS_BusInfoLog.txt");
std::ofstream LogFile::m_ofLocCar("Trace\\NS_CarLocationLog.txt");
std::ofstream LogFile::m_ofInfoCar("Trace\\NS_CarInfoLog.txt");
std::ofstream LogFile::m_ofResource("Trace\\NS_ResourcesLog.txt");
// 5. buffer allocation.
std::ofstream LogFile::m_ofBufferAllocation("Trace\\NS_BufferAllocationLog.txt");

// -----------------C. node movement process log ---------------
// 1. bus movement.
std::ofstream LogFile::m_ofMovementBus("Trace\\NS_BusMovementLog.txt");

// 2. car movement.
std::ofstream LogFile::m_ofMovementCar("Trace\\NS_CarMovementLog.txt");

// -----------------D. Contact process log. --------------------
// 1. Contact
std::ofstream LogFile::m_ofContact("Trace\\NS_BusAndCarContactLog.txt");

// -------------------E. Results -----------------------
std::ofstream LogFile::m_ofHitRate_LossRate_Results("Trace\\NS_ResultsAboutHitandLoss.txt");

// --------------------------------- Class ----------------------
LogFile * LogFile::pObjLog = new LogFile();

LogFile::LogFile()
{

}

LogFile::~LogFile()
{
	CloseFiles();
	if (NULL != pObjLog) {
		delete pObjLog;
		pObjLog = NULL;
	}
}

LogFile* LogFile::instance()
{
	if ( NULL != pObjLog )
	{
		return pObjLog;
	}
	return NULL;
}

void LogFile::CloseFiles()
{
	m_ofErrLog.close();
	m_ofRunLog.close();
	// m_ofForwardLog.close();
	//m_ofLocLog.close();
	
	m_ofLocPath.close();
	// 2. bus node
	m_ofLocBus.close();
	m_ofInfoBus.close();
	// 3. car node.
	m_ofLocCar.close();
	m_ofInfoCar.close();
	// 4. resources.
	m_ofResource.close();

	m_ofBufferAllocation.close();

	m_ofMovementBus.close();
	m_ofMovementCar.close();

	m_ofContact.close();

	m_ofHitRate_LossRate_Results.close();
}
