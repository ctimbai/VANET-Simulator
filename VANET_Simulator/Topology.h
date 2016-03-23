#ifndef _TOPOLOGY_H_
#define _TOPOLOGY_H_

class Topology
{
public:
	Topology( double dTopo_start_loc_x = 0.0, double dTopo_start_loc_y = 0.0, double dSquare_Width = 500.0, double dSquare_Height = 500.0 );

public:
	void Set_Topo_Width( double dTopoWidth );
	void Set_Topo_Height( double dTopoHeight );

	static double Get_Topo_Width();
	static double Get_Topo_Height();

	static double Get_Topo_start_loc_x();
	static double Get_Topo_start_loc_y();

private:
	static double m_dTopo_start_loc_x;
	static double m_dTopo_start_loc_y;
	static double m_dSquare_Width;
	static double m_dSquare_Height;
};


#endif