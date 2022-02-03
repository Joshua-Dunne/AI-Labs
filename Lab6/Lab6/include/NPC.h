#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <iostream>

class NPC
{
public:
	NPC() = delete;
	NPC(sf::Vector2i t_pos);

	void update(sf::Time& dt);
	void render(sf::RenderWindow& t_window);

	sf::CircleShape m_body;

	// if the heading is something other than 0, set it
	// if it's exactly 0, then ignore it and keep the old heading
	inline void setHeading(sf::Vector2f t_heading) { (t_heading != sf::Vector2f{ 0.0f, 0.0f }) ? m_heading = t_heading : m_heading = m_heading; }

private:
	void wrapAround();
	void capVelocity();
	

	sf::Vector2f m_heading = sf::Vector2f{ 0.0f, 0.0f };
	sf::Vector2f m_velocity;
	float m_speed = 15.0f;

	const sf::Vector2f c_MAX_VELOCITY{ 0.75f, 0.75f };
};

#endif