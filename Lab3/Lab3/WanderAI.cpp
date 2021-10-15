#include "WanderAI.h"

WanderAI::WanderAI(sf::Vector2f t_pos) : NPC(t_pos)
{
}

void WanderAI::update(sf::Time& dt)
{
	
}

SteeringOutput WanderAI::getSteering()
{
	SteeringOutput steering;
	int random = rand() % 2;
	if (random == 0) random = -1;

	m_wanderOrientation += random * m_wanderRate;
	float m_targetOrientation = m_orientation + m_wanderOrientation;
	// Get the centre of the wander circle
	m_target = m_position + m_wanderOffset * sf::Vector2f(m_orientation, m_orientation);
	m_target += m_wanderRadius * sf::Vector2f(m_targetOrientation, m_targetOrientation);
	//m_steering = face.getSteering(m_target);
	//Full acceleration in direction we are facing
	m_steering.linear = m_maxAcc * sf::Vector2f(m_orientation, m_orientation);

	return steering;

}
