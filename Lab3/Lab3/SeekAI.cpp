#include "SeekAI.h"

SeekAI::SeekAI(sf::Vector2f t_pos) : NPC(t_pos)
{
	m_name.setFont(m_font);
	m_name.setString("Seek");
}

void SeekAI::update(sf::Time& dt)
{
	SteeringOutput steering = getSteering();
	m_position = m_position + steering.linear;
	m_rotation = steering.rotation;

	m_body.setPosition(m_position);
	m_body.setRotation(m_rotation);
	m_name.setPosition(m_position - sf::Vector2f{m_name.getGlobalBounds().width / 2.0f, 75.0f});
}

SteeringOutput SeekAI::getSteering()
{
	SteeringOutput steering;
	steering.linear = m_target - m_position;
	steering.linear = normalize(steering.linear);
	steering.rotation = getRotation(steering.linear);
	steering.linear *= maxAcceleration;
	steering.angular = sf::Vector2f{ 0.0, 0.0f }; //ignored
	return steering;
}
