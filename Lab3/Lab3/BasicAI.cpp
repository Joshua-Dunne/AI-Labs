#include "BasicAI.h"

BasicAI::BasicAI(sf::Vector2f t_pos) : NPC(t_pos)
{
}

void BasicAI::update(sf::Time& dt)
{
	if (m_isActive)
	{
		// Update Basic AI
		m_velocity += (m_heading * m_speed) * dt.asSeconds();

		capVelocity();

		m_position += m_velocity;

		m_body.setPosition(m_position);

		wrapAround();
	}
	
}
