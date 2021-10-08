#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <iostream>

class NPC
{
public:
	NPC() = delete;
	NPC(sf::Vector2f t_pos);

	void update(sf::Time& dt);
	void render(sf::RenderWindow& t_window);

private:
	void wrapAround();
	void capVelocity();

	sf::Texture m_bodyTex;
	sf::Sprite m_body;

	sf::Vector2f m_heading;
	sf::Vector2f m_velocity;
	float m_speed = 5.0f;

	const sf::Vector2f c_MAX_VELOCITY{ 8.0f, 8.0f };
};

#endif