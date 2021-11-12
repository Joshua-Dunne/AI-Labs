#pragma once
#include  <string>
#include <SFML/Graphics.hpp>

// ---------------------------------------------------------------------
//  Name:           NodeData
//  Description:    A simple struct to encapsulate all the node data.
//                  Add or remove fields as required.               
// ---------------------------------------------------------------------
struct NodeData
{
	int m_name;
	int m_id;
	float m_x;
	float m_y;
	sf::Vector2f m_dir;
	bool m_passable = true;
};