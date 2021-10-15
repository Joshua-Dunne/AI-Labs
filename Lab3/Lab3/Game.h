#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "BasicAI.h"
#include "SeekAI.h"
#include "WanderAI.h"
#include "globals.h"

class Game
{
public:
	Game();
	~Game();
private:
	sf::RenderWindow m_window;
	sf::Clock m_updateClock;

	Player* m_player;
	//BasicAI* m_basicAI;
	//WanderAI* m_wanderAI;
	SeekAI* m_seekAI;

	sf::Texture* m_tex;

public:
	void run();
	void processInput();
	void update(sf::Time& dt);
	void render();
};

#endif