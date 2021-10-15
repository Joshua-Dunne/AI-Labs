#include "Game.h"

Game::Game() :	m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Lab1")
{
	//m_window.setFramerateLimit(60u);

	m_tex = new sf::Texture;
	
	if (!m_tex->loadFromFile("resources/sprites/npc.png"))
	{
		throw std::exception("Error loading NPC sprite!");
	}

	m_player = new Player(sf::Vector2f{ 200.0f, 300.0f });
	//m_basicAI = new BasicAI(sf::Vector2f{ 600.0f, 300.0f });
	m_seekAI = new SeekAI(sf::Vector2f{ 600.0f, 300.0f });

	//m_basicAI->initialize(m_tex);
	m_seekAI->initialize(m_tex);
}

Game::~Game()
{
	delete(m_player);
	//delete(m_basicAI);
	//delete (m_wanderAI);
	delete(m_seekAI);
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
			if (event.key.code == sf::Keyboard::Num7)
			{
				if (m_seekAI->active())
					m_seekAI->setActive(false);
				else
					m_seekAI->setActive(true);
			}
			
		}
	}
}

void Game::update(sf::Time& dt)
{
	// Update elements
	m_player->update(dt);

	m_seekAI->m_target = m_player->m_position;
	m_seekAI->update(dt);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements
	m_player->render(m_window);
	m_seekAI->render(m_window);

	m_window.display();
}
