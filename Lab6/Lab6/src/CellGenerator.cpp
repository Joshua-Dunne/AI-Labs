#include "../include/CellGenerator.h"

CellGenerator::CellGenerator() : m_graph(2500)
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

	// Now that the Data has been filled, generate the nodes.txt
	generateNodesFile();
	generateArcsFile();

	m_graph.breadthFirst(m_graph.nodeIndex(m_start));
}

/// <summary>
/// Check to see if a file exists already.
/// </summary>
/// <param name="fileName">Path to file</param>
/// <returns>If the file already exists on the path</returns>
bool CellGenerator::fileExists(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

/// <summary>
/// Generate a file called "nodes.txt" based on the generated Node data.
/// </summary>
void CellGenerator::generateNodesFile()
{
	std::string saveFileName{ "assets/generated/nodes.txt" };

	if (!fileExists(saveFileName.c_str()))
	{ // if the file doesn't exist, create it and fill it with our data
	  // if it already exists, we don't need to run this code again

		std::fstream saveToFile;

		saveToFile.open(saveFileName, std::fstream::out);

		if (saveToFile.is_open()) // make sure the file has opened successfully
		{
			for (int yPos = 0; yPos < c_MAX_Y; yPos++)
			{
				for (int xPos = 0; xPos < c_MAX_X; xPos++)
				{
					saveToFile << m_data[yPos][xPos]->m_name <<
						" " << m_data[yPos][xPos]->m_x <<
						" " << m_data[yPos][xPos]->m_y << std::endl;

				}
			}

		}

		saveToFile.close();
	}
}

/// <summary>
/// Generate a file called "arcs.txt".
/// </summary>
void CellGenerator::generateArcsFile()
{
	// We don't need to check if the file is already real here
	// since there's information we need to process as well

	std::string saveFileName{ "assets/generated/arcs.txt" };
	std::fstream saveToFile;
	saveToFile.open(saveFileName, std::fstream::out);

	if (saveToFile.is_open())
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


						/*
						Calculating the cost:
						Since each node is 50x50 (size of our walls), the cost will be 50 if it's next to the node.
						The cost will be the square root of the combined sizes, which is sqrt(100).
						This is because if we take the values to be 1,
						Each node that is next to our first node will have a cost of 1,
						where as each diagonal will have a cost of sqrt(1+1).
						So we will have the nodes next to have 50, and diagonal be sqrt(50 + 50).
						*/

						int cost;

						// 0,2,6,8 are Diagonal, so we need to apply the correct cost
						if (direction == 0 || direction % 2 == 0)
						{
							cost = static_cast<int>(sqrt(100));
							m_graph.addArc(m_data[row][col]->m_name, m_data[n_row][n_col]->m_name, 100);
						}
						else // 1,3,5,7 are next to the node, so give them the correct cost
						{
							cost = 50;
							m_graph.addArc(m_data[row][col]->m_name, m_data[n_row][n_col]->m_name, 50);
						}


						// Now that it's been added to the Graph, output it to our file
						saveToFile << m_data[row][col]->m_name <<
							" " << m_data[n_row][n_col]->m_name <<
							" " << cost << std::endl;
					}
				}
			}
		}
	}
	saveToFile.close(); // now that we're done, close the file
}