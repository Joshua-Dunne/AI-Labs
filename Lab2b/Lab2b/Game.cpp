#include "Game.h"

Game::Game() :	m_window(sf::VideoMode(800u, 600u), "Lab1")
{
	//m_window.setFramerateLimit(60u);
	
	m_player = new Player(sf::Vector2f{ 200.0f, 300.0f });
	m_npc = new NPC(sf::Vector2f{ 600.0f, 300.0f });
}

Game::~Game()
{
	delete(m_player);
	delete(m_npc);
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
	m_player->update(dt);
	m_npc->update(dt);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements
	m_player->render(m_window);
	m_npc->render(m_window);

	m_window.display();
}
