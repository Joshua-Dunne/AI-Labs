#include "../include/CellGenerator.h"

CellGenerator::CellGenerator()
{
}

/// <summary>
/// Populate our Data array, getting the X/Y positions of each Node, and a name.
/// </summary>
void CellGenerator::populateData()
{
	int currCell = 0;
	
	for (int yPos = 0; yPos < c_MAX_Y; yPos++)
	{
		for (int xPos = 0; xPos < c_MAX_X; xPos++)
		{
			m_data[yPos][xPos] = new NodeData();
			m_data[yPos][xPos]->m_x = xPos * 50;
			m_data[yPos][xPos]->m_y = yPos * 50;
			m_data[yPos][xPos]->m_name = currCell;
			currCell++;
		}
	}
}
