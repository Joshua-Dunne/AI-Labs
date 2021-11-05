#pragma once
#include  <string>

// ---------------------------------------------------------------------
//  Name:           NodeData
//  Description:    A simple struct to encapsulate all the node data.
//                  Add or remove fields as required.               
// ---------------------------------------------------------------------
struct NodeData
{
	int m_name;
	int m_cost;
	int m_distance;
	int m_x;
	int m_y;
	bool m_passable = true;
};