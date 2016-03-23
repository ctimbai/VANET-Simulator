#ifndef _BASE_CTR_H_
#define _BASE_CTR_H_

//=================== NS Testing case switches ==============

const bool IS_SENSOR_NETWORK_TEST_OPEN				= false;
const bool IS_VANET_V2I_V2V_TEST_OPEN				= false;
const bool IS_VANET_BUS_CAR_OFFLOADING_TEST_OPEN	= true;

//=================== NS LogFile switches ===================

const bool IS_COUT_OPEN			= false;
const bool IS_RUNLOG_OPEN		= false;
const bool IS_FWLOG_OPEN		= false;
const bool IS_LOCLOG_OPEN		= false;

// =================== Node's settings ======================

// --------------------A. Bus ---------------
// 1. Buses' number.
const int BUS_NUM = 10;

// 2. Buses' velocity.
const double BUS_VEL = 5.0;  // e.g: V = 5m/s

// 3. Buses's Transmission range.
const double BUS_TR = 5.0;

// 4. Bus's Buffer Capacity.(packet)
const int BUS_BUFFER = 25;  // e.g: buffer = 50 packets

// 5. Bus's the radius of point.
const double BUS_RADII = 10.0;

// 6. the number of Bus's path stops.
const unsigned int BUS_STOP = 20;

// 7. the number of bus path
const unsigned int BUS_PATH = 10;

// --------------------B. Car -----------------
// 1. Cars' number.
const int CAR_NUM = 500;

// 2. Cars' velocity.
const double CAR_VEL = 10.0;  // e.g: V = 10m/s

// 3. Cars's Transmission range.
const double CAR_TR = 3.0;

// =================== NS Running Settings.==================

// The unit of time-slot: Time ticks step, ms
const int NS_STEP_TICK_MS = 10; // e.g: 10ms

// simulator's speed ratio.
const unsigned int NS_SPEED_RATIO = 1;

// =================== Topology settings. ===================
const double TOPO_MIN_X = 0.0;
const double TOPO_MIN_Y = 0.0;
const double TOPO_WIDTH = 600.0;
const double TOPO_HEIGHT = 600.0;

// Topology params;
const double TOPO_MAX_X = TOPO_MIN_X + TOPO_WIDTH;
const double TOPO_MAX_Y = TOPO_MIN_Y + TOPO_HEIGHT;



#endif//_BASE_CTR_H_