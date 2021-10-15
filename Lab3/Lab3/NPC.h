#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SteeringOutput.h"
#include "globals.h"

class NPC
{
public:
	NPC() = delete;
	NPC(sf::Vector2f t_pos);

	virtual void update(sf::Time& dt) = 0;
	void render(sf::RenderWindow& t_window);
	void initialize(sf::Texture* t_tex);
	inline void setActive(bool t_active) { m_isActive = t_active; };
	inline bool active() { return m_isActive; };

	sf::Text m_name;

protected:
	void wrapAround();
	void capVelocity();
	float getNewOrientation(float t_current, sf::Vector2f t_velocity);
	float getLength(sf::Vector2f t_velocity) { return sqrt((t_velocity.x * t_velocity.x) + (t_velocity.y * t_velocity.y)); };
	sf::Vector2f normalize(sf::Vector2f t_vector) { return t_vector / getLength(t_vector); };
	float getRotation(sf::Vector2f t_heading) {return atan2(t_heading.y, t_heading.x) * 180.0f / 3.14159f;}
	

	sf::Texture* m_bodyTex;
	sf::Sprite m_body;

	bool m_isActive = true;

	sf::Vector2f m_position;
	sf::Vector2f m_heading;
	sf::Vector2f m_velocity;

	float m_rotation = 0.0f;
	float m_speed = 2.0f;
	float m_rotationSpeed = 2.0f;

	const sf::Vector2f c_MAX_VELOCITY{ 8.0f, 8.0f };

	sf::Font m_font;
};

#endif