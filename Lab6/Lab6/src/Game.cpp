#include "../include/Game.h"

Game::Game() :	m_window(sf::VideoMode(800u, 800u), "Lab6")
{
	//m_window.setFramerateLimit(60u);
	cellGen.populateData();

	font.loadFromFile("assets/fonts/bell.ttf");

	num.setFont(font);
	num.setCharacterSize(12u);
	num.setFillColor(sf::Color::White);
	
}

Game::~Game()
{
}

/// <summary>
/// Run the main Game loop
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	while (m_window.isOpen())
	{
		processInput();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		render();
	}
}

/// <summary>
/// Processes inputs from Events
/// </summary>
void Game::processInput()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::N)
			{
				toggleNumbers = !toggleNumbers;
			}
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			// Left Click to set Start Goal
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				int cellCount = 0;
				bool finished = false;

				for (int yPos = 0; yPos < 50; yPos++)
				{
					for (int xPos = 0; xPos < 50; xPos++)
					{
						if (event.mouseButton.x >= cellGen.m_data[yPos][xPos]->m_x
							&& event.mouseButton.x <= cellGen.m_data[yPos][xPos]->m_x + cellGen.m_cellSize)
						{
							if (event.mouseButton.y >= cellGen.m_data[yPos][xPos]->m_y
								&& event.mouseButton.y <= cellGen.m_data[yPos][xPos]->m_y + cellGen.m_cellSize)
							{
								finished = true;
								cellGen.setStart(cellCount);
								cellGen.resetData();
								break;
							}
						}

						cellCount++;
					}

					if (finished)
						break;
				}
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				int cellCount = 0;
				bool finished = false;

				for (int yPos = 0; yPos < 50; yPos++)
				{
					for (int xPos = 0; xPos < 50; xPos++)
					{
						if (event.mouseButton.x >= cellGen.m_data[yPos][xPos]->m_x
							&& event.mouseButton.x <= cellGen.m_data[yPos][xPos]->m_x + cellGen.m_cellSize)
						{
							if (event.mouseButton.y >= cellGen.m_data[yPos][xPos]->m_y
								&& event.mouseButton.y <= cellGen.m_data[yPos][xPos]->m_y + cellGen.m_cellSize)
							{
								if (cellGen.m_data[yPos][xPos]->m_name != 999)
								{ // cannot set start or goal to an unpassable node
									finished = true;
									cellGen.setGoal(cellCount);
									cellGen.resetData();
									break;
								}
							}
						}

						cellCount++;
					}

					if (finished)
						break;
				}
			}

			if (event.mouseButton.button == sf::Mouse::Middle)
			{
				int cellCount = 0;
				bool finished = false;

				for (int yPos = 0; yPos < 50; yPos++)
				{
					for (int xPos = 0; xPos < 50; xPos++)
					{
						if (event.mouseButton.x >= cellGen.m_data[yPos][xPos]->m_x
							&& event.mouseButton.x <= cellGen.m_data[yPos][xPos]->m_x + cellGen.m_cellSize)
						{
							if (event.mouseButton.y >= cellGen.m_data[yPos][xPos]->m_y
								&& event.mouseButton.y <= cellGen.m_data[yPos][xPos]->m_y + cellGen.m_cellSize)
							{
								if (cellCount != cellGen.m_start && cellCount != cellGen.m_goal)
								{ // only allow something to be set as unpassable if it isn't the start or the goal
									finished = true;
									cellGen.m_graph.nodeIndex(cellCount)->m_data.m_passable = !cellGen.m_graph.nodeIndex(cellCount)->m_data.m_passable;
									cellGen.m_graph.nodeIndex(cellCount)->m_data.m_name = 999;
									cellGen.resetData();
									break;
								}	
							}
						}

						cellCount++;
					}

					if (finished)
						break;
				}
			}
		}
	}
}

void Game::update(sf::Time& dt)
{
	// Update elements
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements
	sf::VertexArray lines(sf::Lines, 2);

	sf::RectangleShape node;
	node.setSize(sf::Vector2f{ static_cast<float>(cellGen.m_cellSize), static_cast<float>(cellGen.m_cellSize) });
	node.setOrigin(sf::Vector2f{ cellGen.m_cellSize / 2.0f, cellGen.m_cellSize / 2.0f });
	int cellCount = 0;

	for (int yPos = 0; yPos < 50; yPos++)
	{
		for (int xPos = 0; xPos < 50; xPos++)
		{
			node.setPosition(static_cast<float>(cellGen.m_data[yPos][xPos]->m_x + (cellGen.m_cellSize / 2.0f)),
							 static_cast<float>(cellGen.m_data[yPos][xPos]->m_y + (cellGen.m_cellSize / 2.0f)));
			if (toggleNumbers)
			{
				num.setPosition(node.getPosition() - sf::Vector2f{ (cellGen.m_cellSize / 2.0f), (cellGen.m_cellSize / 2.0f) });
				num.setString(std::to_string(cellGen.m_data[yPos][xPos]->m_name));
			}

			node.setFillColor(sf::Color::Blue);			

			for (size_t pathIt = 0; pathIt < cellGen.path.size(); pathIt++)
			{
				if (cellGen.path[pathIt] == cellGen.m_data[yPos][xPos]->m_id)
				{
					node.setFillColor(sf::Color::Yellow);
				}
			}

			if (cellCount == cellGen.m_start)
				node.setFillColor(sf::Color::Red);
			else if (cellCount == cellGen.m_goal)
				node.setFillColor(sf::Color::Green);

			// now that the color has been set, we'll change the transparency based on the ID
			if (cellCount != cellGen.m_start && cellCount != cellGen.m_goal)
			{// don't change transparency if it's the start of end
				if (cellGen.m_data[yPos][xPos]->m_passable)
					node.setFillColor(node.getFillColor() - sf::Color::Color(0, 0, 0, cellGen.m_data[yPos][xPos]->m_name * 5));
				else
					node.setFillColor(sf::Color::Black);
			}

			cellCount++;

			// now we will setup the flow field lines for each node
			lines.append(sf::Vertex(node.getPosition(), sf::Color::Black));
			lines.append(sf::Vertex(node.getPosition() + cellGen.m_data[yPos][xPos]->m_dir * 16.0f, sf::Color::White));

			m_window.draw(node);
			m_window.draw(num);
			m_window.draw(lines);

			lines.clear();
		}
	}

	m_window.display();
}
