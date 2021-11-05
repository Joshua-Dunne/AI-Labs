#ifndef CELL_GEN_H
#define CELL_GEN_H

#include "NodeData.h"
#include "Graph.h"
#include "GraphNode.h"
#include "NodeData.h"
#include "NodeComparerTwo.h"
#include "Wall.h"
#include <vector>
#include <fstream>
#include <sstream>

class CellGenerator
{
	static const int c_MAX_X = 32; // 800 / 25 (Screen Width / Wall Size)
	static const int c_MAX_Y = 24; // 600 / 25 (Screen Height / Wall Size)

	Graph<NodeData, int> m_graph;
	NodeData m_data[c_MAX_Y][c_MAX_X]; // 32x24 grid of nodes
	std::vector<Wall*> m_walls;
	std::vector<sf::Vector2i> m_unpassable;

	bool fileExists(const char* fileName);
	void checkPassable();
	void generateNodesFile();
	void generateArcsFile();

public:
	CellGenerator();

	void setObstacles(std::vector<Wall*>& t_walls);
	void populateData();
	inline Graph<NodeData, int>& getGraph() { return m_graph; };
	void renderUpassable(sf::RenderWindow &t_window);
};

#endif