#ifndef CELL_GEN_H
#define CELL_GEN_H

#include "NodeData.h"
#include "Graph.h"
#include "GraphNode.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

/// <summary>
/// A class to Generate Node Data for our Game
/// </summary>
class CellGenerator
{
	static const int c_MAX_X = 50; // 800 / 50 (Screen Width / Wall Size)
	static const int c_MAX_Y = 50; // 800 / 50 (Screen Height / Wall Size)

public:
	CellGenerator();
	void populateData();
	void generateNodes();
	void generateArcs();
	void resetData();

	void setStart(int t_start) { m_start = t_start; }
	void setGoal(int t_goal) { m_goal = t_goal; }

	int m_start = 400;
	int m_goal = 276;
	int m_cellSize = 16;

	Graph<NodeData, float> m_graph;
	NodeData* m_data[c_MAX_Y][c_MAX_X]; // 50x50 grid of nodes
	std::vector<int> path;

};

#endif