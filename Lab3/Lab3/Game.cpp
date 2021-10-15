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
	m_seekAI = new SeekAI(sf::Vector2f{ 600.0f, 300.0f });
	m_arriveAI = new ArriveAI(sf::Vector2f{ 600.0f, 300.0f });
	m_slowArriveAI = new ArriveAI(sf::Vector2f{ 600.0f, 400.0f });
	m_persueAI = new PersueAI(sf::Vector2f{ 700.0f, 400.0f });
	m_wanderAI = new WanderAI(sf::Vector2f{ 400.0f, 300.0f });

	m_seekAI->initialize(m_tex);

	m_tex = new sf::Texture;

	if (!m_tex->loadFromFile("resources/sprites/npc2.png"))
	{
		throw std::exception("Error loading NPC2 sprite!");
	}

	m_arriveAI->initialize(m_tex);

	m_tex = new sf::Texture;

	if (!m_tex->loadFromFile("resources/sprites/npc3.png"))
	{
		throw std::exception("Error loading NPC3 sprite!");
	}

	m_slowArriveAI->initialize(m_tex);
	m_slowArriveAI->m_maxSpeed = 0.25f;
	m_slowArriveAI->m_name.setString("Slow Arrive");

	m_tex = new sf::Texture;

	if (!m_tex->loadFromFile("resources/sprites/npc4.png"))
	{
		throw std::exception("Error loading NPC4 sprite!");
	}

	m_persueAI->initialize(m_tex);

	m_tex = new sf::Texture;

	if (!m_tex->loadFromFile("resources/sprites/npc5.png"))
	{
		throw std::exception("Error loading NPC5 sprite!");
	}

	m_wanderAI->initialize(m_tex);
}

Game::~Game()
{
	delete(m_player);
	delete(m_seekAI);
	delete(m_arriveAI);
	delete(m_slowArriveAI);
	delete(m_persueAI);
	delete(m_wanderAI);
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
			if (event.key.code == sf::Keyboard::Num1)
			{
				if (m_seekAI->active())
					m_seekAI->setActive(false);
				else
					m_seekAI->setActive(true);
			}

			if (event.key.code == sf::Keyboard::Num2)
			{
				if (m_arriveAI->active())
					m_arriveAI->setActive(false);
				else
					m_arriveAI->setActive(true);
			}

			if (event.key.code == sf::Keyboard::Num3)
			{
				if (m_slowArriveAI->active())
					m_slowArriveAI->setActive(false);
				else
					m_slowArriveAI->setActive(true);
			}

			if (event.key.code == sf::Keyboard::Num4)
			{
				if (m_persueAI->active())
					m_persueAI->setActive(false);
				else
					m_persueAI->setActive(true);
			}

			if (event.key.code == sf::Keyboard::Num5)
			{
				if (m_wanderAI->active())
					m_wanderAI->setActive(false);
				else
					m_wanderAI->setActive(true);
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
	
	m_arriveAI->m_target = m_player->m_position;
	m_arriveAI->update(dt);

	m_slowArriveAI->m_target = m_player->m_position;
	m_slowArriveAI->update(dt);

	m_persueAI->m_target = m_player->m_position;
	m_persueAI->m_targetVelocity = m_player->m_velocity;
	m_persueAI->update(dt);

	m_wanderAI->update(dt);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements
	m_player->render(m_window);
	m_seekAI->render(m_window);
	m_arriveAI->render(m_window);
	m_slowArriveAI->render(m_window);
	m_persueAI->render(m_window);
	m_wanderAI->render(m_window);

	m_window.display();
}
