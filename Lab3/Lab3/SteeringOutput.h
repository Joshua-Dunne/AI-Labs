#ifndef STEERING_H
#define STEERING_H

#include <SFML/Graphics.hpp>

struct SteeringOutput
{
	sf::Vector2f linear;
	sf::Vector2f angular = sf::Vector2f{ 0.0f,0.0f };
	float rotation = 0.0f;
};

#endif