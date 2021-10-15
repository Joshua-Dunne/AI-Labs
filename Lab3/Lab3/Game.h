#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "SeekAI.h"
#include "ArriveAI.h"
#include "PersueAI.h"
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
	SeekAI* m_seekAI;
	ArriveAI* m_arriveAI;
	ArriveAI* m_slowArriveAI;
	PersueAI* m_persueAI;
	WanderAI* m_wanderAI;

	sf::Texture* m_tex;

public:
	void run();
	void processInput();
	void update(sf::Time& dt);
	void render();
};

#endif