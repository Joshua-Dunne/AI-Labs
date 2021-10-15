#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	Player() = delete;
	Player(sf::Vector2f t_pos);

	void update(sf::Time& dt);
	void render(sf::RenderWindow& t_window);

	sf::Vector2f m_position;

private:
	void handleInput(sf::Time& dt);
	void wrapAround();
	void capVelocity();

	sf::Texture m_bodyTex;
	sf::Sprite m_body;
	
	sf::Vector2f m_heading;
	sf::Vector2f m_velocity;

	float m_rotation = 0.0f;
	float m_speed = 5.0f;
	float m_rotationSpeed = 2.0f;

	const sf::Vector2f c_MAX_VELOCITY{ 8.0f, 8.0f };
};

#endif