#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "CellGenerator.h"
#include "NPC.h"

class Game
{
public:
	Game();
	~Game();
private:
	sf::RenderWindow m_window;
	sf::Clock m_updateClock;

public:
	void run();
	void processInput();
	void update(sf::Time& dt);
	void render();

	CellGenerator cellGen;

	sf::Font font;
	sf::Text num;
	sf::Text instructions;

	bool toggleNumbers = false;
	bool toggleVectors = false;
	bool placingMovers = false;

	std::vector<NPC*> m_movers;
};

#endif