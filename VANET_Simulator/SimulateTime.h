#ifndef _SIMULATE_TIME_H_
#define _SIMULATE_TIME_H_


class SimulateTime
{
public:
	SimulateTime();
public:

	//时间步长按ms算
	static void TimeStepForward(void);
	static double Get_CurrentTime(void);
	static int GetTimeStep_ms(void);

	static void Reset_NS_time(void);

	//时间步长按s算.
	static void TimeStepForward_s();
	static void GetTimeStep_s();

private:
	static double m_dCurrentTime;
	static const int m_scnNS_TimeStep_ms;
};


#endif