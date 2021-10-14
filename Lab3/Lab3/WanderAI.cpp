#include "WanderAI.h"

WanderAI::WanderAI(sf::Vector2f t_pos) : NPC(t_pos)
{
}

void WanderAI::update(sf::Time& dt)
{
	// calculate target in front of ai
	sf::Vector2f target = sf::Vector2f{ 400.0f, -100.0f };
	m_velocity = target - m_position;
	m_velocity /= getLength(m_velocity); // normalize vector
	m_orientation = getNewOrientation(m_orientation, m_velocity);

	int random = rand() % 2;
	if (random == 0)
		random--;

	m_rotation += m_maxRotation * static_cast<float>(random);
	m_velocity.x = -sin(m_orientation) * m_speed;
	m_velocity.y = cos(m_orientation) * m_speed;

	m_position += m_velocity;

	wrapAround();

	m_body.setPosition(m_position);
	m_body.setRotation(m_rotation);
}
