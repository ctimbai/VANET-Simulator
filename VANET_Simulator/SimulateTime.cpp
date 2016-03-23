//#include "stdafx.h"
#include "SimulateTime.h"
#include "BaseDef.h"


double SimulateTime::m_dCurrentTime = 0.0; // Initial time

const int SimulateTime::m_scnNS_TimeStep_ms = NS_STEP_TICK_MS; // !!! Time ticks forward, ms

const double gcdTimeStep = ( (double)(NS_STEP_TICK_MS)*0.001 ) * (double)NS_SPEED_RATIO;
SimulateTime::SimulateTime()
{
}

void SimulateTime::TimeStepForward(void)
{
	// LogicalTime steps forward  dStep_second ms, every step.
	m_dCurrentTime += gcdTimeStep;
}


double SimulateTime::Get_CurrentTime(void)
{
	return m_dCurrentTime;
}

int SimulateTime::GetTimeStep_ms( void )
{
	return (m_scnNS_TimeStep_ms*NS_SPEED_RATIO);
}

void SimulateTime::Reset_NS_time( void )
{
	m_dCurrentTime = 0.0;
}