#include "../include/Game.h"

Game::Game() :	m_window(sf::VideoMode(3200u, 2400u), "Lab1")
{
	//m_window.setFramerateLimit(60u);
	cellGen.populateData();
	
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

	sf::RectangleShape node;
	node.setSize(sf::Vector2f{ 50.0f, 50.0f });
	node.setOrigin(sf::Vector2f{ 25.0f, 25.0f });
	int cellCount = 0;

	for (int yPos = 0; yPos < 50; yPos++)
	{
		for (int xPos = 0; xPos < 50; xPos++)
		{
			node.setPosition(static_cast<float>(cellGen.m_data[yPos][xPos]->m_x), 
							 static_cast<float>(cellGen.m_data[yPos][xPos]->m_y));

			cellCount++;

			if (cellCount == cellGen.m_start)
				node.setFillColor(sf::Color::Red);
			else if (cellCount == cellGen.m_goal)
				node.setFillColor(sf::Color::Green);
			else
				node.setFillColor(sf::Color::Blue);

			m_window.draw(node);
		}
	}

	m_window.display();
}
