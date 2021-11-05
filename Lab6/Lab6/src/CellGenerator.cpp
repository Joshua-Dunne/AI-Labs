#include "CellGenerator.h"

CellGenerator::CellGenerator() : m_graph(768)
{
}

/// <summary>
/// Give the Wall data to the CellGenerator.
/// This is done so it can tell if a Cell can be passed through or not.
/// </summary>
/// <param name="t_walls">A reference to all the walls</param>
void CellGenerator::setObstacles(std::vector<Wall*>& t_walls)
{
	m_walls = t_walls;
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
/// Populate our Data array, getting the X/Y positions of each Node, and a name.
/// </summary>
void CellGenerator::populateData()
{
	int currCell = 0;
	
	for (int yPos = 0; yPos < c_MAX_Y; yPos++)
	{
		for (int xPos = 0; xPos < c_MAX_X; xPos++)
		{
			m_data[yPos][xPos].m_x = xPos * 25;
			m_data[yPos][xPos].m_y = yPos * 25;
			m_data[yPos][xPos].m_name = currCell;
			
			m_graph.addNode(m_data[yPos][xPos], currCell);

			currCell++;
		}
	}

	// Now that the Data has been filled, generate the nodes.txt
	generateNodesFile();

	// Before we can generate the Arcs, we need to figure out which nodes are impassable
	checkPassable();

	generateArcsFile();




}

void CellGenerator::renderUpassable(sf::RenderWindow& t_window)
{
#ifdef _DEBUG

	for (auto unPassPos : m_unpassable)
	{
		sf::RectangleShape unpass;
		unpass.setSize(sf::Vector2f(25, 25));
		//unpass.setOrigin(unpass.getGlobalBounds().width / 2, unpass.getGlobalBounds().height / 2);
		unpass.setPosition(static_cast<sf::Vector2f>(unPassPos));
		unpass.setFillColor(sf::Color{255,255,0,105});
		unpass.setOutlineColor(sf::Color{ 255,0,0,105 });
		unpass.setOutlineThickness(2);
		t_window.draw(unpass);
	}

#endif // _DEBUG
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
					saveToFile << m_data[yPos][xPos].m_name <<
						   " " << m_data[yPos][xPos].m_x <<
						   " " << m_data[yPos][xPos].m_y << std::endl;

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
						Since each node is 25x25 (size of our walls), the cost will be 25 if it's next to the node.
						The cost will be the square root of the combined sizes, which is sqrt(50).
						This is because if we take the values to be 1,
						Each node that is next to our first node will have a cost of 1,
						where as each diagonal will have a cost of sqrt(1+1).
						So we will have the nodes next to have 25, and diagonal be sqrt(25+25).
						*/

						int cost;

						// 0,2,6,8 are Diagonal, so we need to apply the correct cost
						if (direction == 0 || direction % 2 == 0)
						{
							cost = static_cast<int>(sqrt(50));
							m_graph.addArc(m_data[row][col].m_name, m_data[n_row][n_col].m_name, 50);
						}
						else // 1,3,5,7 are next to the node, so give them the correct cost
						{
							cost = 25;
							m_graph.addArc(m_data[row][col].m_name, m_data[n_row][n_col].m_name, 25);
						}


						// Now that it's been added to the Graph, output it to our file
						saveToFile << m_data[row][col].m_name <<
							" " << m_data[n_row][n_col].m_name <<
							" " << cost << std::endl;
					}
				}
			}
		}
	}
	saveToFile.close(); // now that we're done, close the file
}

/// <summary>
/// Using the vector of Wall data, check if a cell is applicable to be used for our path finding.
/// </summary>
void CellGenerator::checkPassable()
{
	//floor(spriteX / cell width) + (floor(spriteY / cell height) * number of columns)
	for (auto wall : m_walls)
	{
		float calc = floor((wall->getPosition().x - 12.5f) / 25) + (floor(((wall->getPosition().y - 12.5f) / 25)) * c_MAX_X);
		m_graph.nodeIndex(calc)->m_data.m_passable = false;
		m_unpassable.push_back(sf::Vector2i{ m_graph.nodeIndex(calc)->m_data.m_x, m_graph.nodeIndex(calc)->m_data.m_y });

		calc = (floor((wall->getPosition().x + 12.5f) / 25) + (floor(((wall->getPosition().y - 12.5f) / 25)) * c_MAX_X));
		m_graph.nodeIndex(calc)->m_data.m_passable = false;
		m_unpassable.push_back(sf::Vector2i{ m_graph.nodeIndex(calc)->m_data.m_x, m_graph.nodeIndex(calc)->m_data.m_y });

		calc = (floor((wall->getPosition().x - 12.5f) / 25) + (floor(((wall->getPosition().y + 12.5f) / 25)) * c_MAX_X));
		m_graph.nodeIndex(calc)->m_data.m_passable = false;
		m_unpassable.push_back(sf::Vector2i{ m_graph.nodeIndex(calc)->m_data.m_x, m_graph.nodeIndex(calc)->m_data.m_y });
		
		calc = (floor((wall->getPosition().x + 12.5f) / 25) + (floor(((wall->getPosition().y + 12.5f) / 25)) * c_MAX_X));
		m_graph.nodeIndex(calc)->m_data.m_passable = false;
		m_unpassable.push_back(sf::Vector2i{ m_graph.nodeIndex(calc)->m_data.m_x, m_graph.nodeIndex(calc)->m_data.m_y });
	}
	// Using a reference to our Wall Sprite,
	// Check to see if it overlaps a Node.
	// If it does, mark it as unpassable (It can't be used during A*)
}
