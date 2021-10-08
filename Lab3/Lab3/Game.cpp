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
	m_basicAI = new BasicAI(sf::Vector2f{ 600.0f, 300.0f });

	m_basicAI->initialize(m_tex);
}

Game::~Game()
{
	delete(m_player);
	delete(m_basicAI);
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
				if (m_basicAI->active())
					m_basicAI->setActive(false);
				else
					m_basicAI->setActive(true);
			}
			
		}
	}
}

void Game::update(sf::Time& dt)
{
	// Update elements
	m_player->update(dt);
	m_basicAI->update(dt);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements
	m_player->render(m_window);
	m_basicAI->render(m_window);

	m_window.display();
}
