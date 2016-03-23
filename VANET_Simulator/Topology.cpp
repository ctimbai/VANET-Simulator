#include "Topology.h"
#include <cassert>

double Topology::m_dTopo_start_loc_x = 0.0;
double Topology::m_dTopo_start_loc_y = 0.0;
double Topology::m_dSquare_Width = 0.0;
double Topology::m_dSquare_Height = 0.0;

Topology::Topology( double dTopo_start_loc_x/*== 0.0*/, double dTopo_start_loc_y/*== 0.0*/, double dSquare_Width /*== 500.0*/, double dSquare_Height /*== 500.0*/ )
{
	assert( 0<dSquare_Height && 0<dSquare_Width );

	m_dTopo_start_loc_x = dTopo_start_loc_x;
	m_dTopo_start_loc_y = dTopo_start_loc_y;
	m_dSquare_Width = dSquare_Width;
	m_dSquare_Height = dSquare_Height;
}


void Topology::Set_Topo_Width( double dTopoWidth )
{
	assert( 0<dTopoWidth );
	m_dSquare_Width = dTopoWidth;
}

void Topology::Set_Topo_Height( double dTopoHeight )
{
	assert( 0<dTopoHeight );
	m_dSquare_Height = dTopoHeight;
}

double Topology::Get_Topo_Width()
{
	return m_dSquare_Width;
}

double Topology::Get_Topo_Height()
{
	return m_dSquare_Height;
}

double Topology::Get_Topo_start_loc_x()
{
	return m_dTopo_start_loc_x;
}

double Topology::Get_Topo_start_loc_y()
{
	return m_dTopo_start_loc_y;
}