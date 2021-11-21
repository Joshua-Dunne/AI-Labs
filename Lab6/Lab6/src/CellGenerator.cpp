#include "../include/CellGenerator.h"

CellGenerator::CellGenerator() : m_graph(2500)
{
}

/// <summary>
/// Populate our Data array, getting the X/Y positions of each Node, and a name.
/// </summary>
void CellGenerator::populateData()
{
	generateNodes();
	generateArcs();
	resetData();
}

/// <summary>
/// Generate Nodes from data
/// </summary>
void CellGenerator::generateNodes()
{
	int currCell = 0;

	for (int yPos = 0; yPos < c_MAX_Y; yPos++)
	{
		for (int xPos = 0; xPos < c_MAX_X; xPos++)
		{
			m_data[yPos][xPos] = new NodeData();
			m_data[yPos][xPos]->m_x = xPos * m_cellSize;
			m_data[yPos][xPos]->m_y = yPos * m_cellSize;
			m_data[yPos][xPos]->m_name = currCell;
			m_graph.addNode(*m_data[yPos][xPos], currCell);
			currCell++;
		}
	}
}

/// <summary>
/// Generate all Arcs
/// </summary>
void CellGenerator::generateArcs()
{
	for (int row = 0; row < c_MAX_Y; row++)
	{
		for (int col = 0; col < c_MAX_X; col++)
		{
			for (int direction = 0; direction < 9; direction++) {
				if (direction == 4) continue; // Skip 4, this is ourself.

				int n_row = row + ((direction % 3) - 1); // Neighbor row
				int n_col = col + ((direction / 3) - 1); // Neighbor column

				// Check the bounds:
				if (n_row >= 0 && n_row < c_MAX_Y && n_col >= 0 && n_col < c_MAX_X) {

					float cost;

					// 0,2,6,8 are Diagonal, so we need to apply the correct cost
					if (direction == 0 || direction % 2 == 0)
					{
						cost = sqrt(2);
						m_graph.addArc(m_data[row][col]->m_name, m_data[n_row][n_col]->m_name, cost);
					}
					else // 1,3,5,7 are next to the node, so give them the correct cost
					{
						cost = 1.0f;
						m_graph.addArc(m_data[row][col]->m_name, m_data[n_row][n_col]->m_name, cost);
					}
				}
			}
		}
	}
}

void CellGenerator::resetData()
{
	// Now that the Data has been filled, generate all necessary Nodes and Arcs
	path.clear();

	int currCell = 0;

	for (int yPos = 0; yPos < c_MAX_Y; yPos++)
	{
		for (int xPos = 0; xPos < c_MAX_X; xPos++)
		{
			m_data[yPos][xPos]->m_x = xPos * m_cellSize;
			m_data[yPos][xPos]->m_y = yPos * m_cellSize;
			m_data[yPos][xPos]->m_name = currCell;
			currCell++;
		}
	}

	m_graph.breadthFirst(m_graph.nodeIndex(m_goal));

	currCell = 0;

	for (int yPos = 0; yPos < c_MAX_Y; yPos++)
	{
		for (int xPos = 0; xPos < c_MAX_X; xPos++)
		{
			m_data[yPos][xPos] = &m_graph.nodeIndex(currCell)->m_data;
			currCell++;
		}
	}

	m_graph.iteration(m_graph.nodeIndex(m_start), m_graph.nodeIndex(m_goal), path);

	currCell = 0;

	m_graph.flowField();

	for (int yPos = 0; yPos < c_MAX_Y; yPos++)
	{
		for (int xPos = 0; xPos < c_MAX_X; xPos++)
		{
			m_data[yPos][xPos]->m_dir = m_graph.nodeIndex(currCell)->m_data.m_dir;
			currCell++;
		}
	}
}
