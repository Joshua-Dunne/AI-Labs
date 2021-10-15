#include "ArriveAI.h"

ArriveAI::ArriveAI(sf::Vector2f t_pos) : NPC(t_pos)
{
	m_name.setFont(m_font);
	m_name.setString("Arrive");
}

void ArriveAI::update(sf::Time& dt)
{
	if (m_isActive)
	{
		SteeringOutput steering = getSteering();
		m_position += steering.linear;
		m_body.setPosition(m_position);
		m_body.setRotation(steering.rotation);

		m_name.setPosition(m_position - sf::Vector2f{ m_name.getGlobalBounds().width / 2.0f, 75.0f });
	}
	
}

SteeringOutput ArriveAI::getSteering()
{
	SteeringOutput steering;

	sf::Vector2f direction = m_target - m_position;
	float distance = getLength(direction);

	float targetSpeed = 0;

	//Set the speed
	if (distance < m_arrivalRadius) targetSpeed = 0;

	else if (distance > m_slowRadius)
	{
		targetSpeed = m_maxSpeed;
	}
	else
	{
		targetSpeed = m_maxSpeed * (distance / m_slowRadius);
	}
	
	//Now set the velocity (speed and direction)
	sf::Vector2f targetVelocity = direction;
	targetVelocity = normalize(targetVelocity);
	targetVelocity = targetVelocity * targetSpeed;
	m_timeToTarget = 0.1f;

	steering.linear = targetVelocity - m_velocity;
	steering.linear = steering.linear / m_timeToTarget;

	//Are we going too fast?
	if (getLength(steering.linear) > m_maxAcceleration)
	{
		steering.linear = normalize(steering.linear);
		steering.linear = steering.linear * m_maxAcceleration;
		steering.angular = sf::Vector2f{ 0.0f, 0.0f };
	}

	steering.rotation = getRotation(normalize(direction));

	return steering;
}
