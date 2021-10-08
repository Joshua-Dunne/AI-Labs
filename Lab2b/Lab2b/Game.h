#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "NPC.h"

class Game
{
public:
	Game();
	~Game();
private:
	sf::RenderWindow m_window;
	sf::Clock m_updateClock;

	Player* m_player;
	NPC* m_npc;

public:
	void run();
	void processInput();
	void update(sf::Time& dt);
	void render();
};

#endif