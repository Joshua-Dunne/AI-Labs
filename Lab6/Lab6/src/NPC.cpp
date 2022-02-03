#include "../include/NPC.h"

NPC::NPC(sf::Vector2i t_pos)
{
	m_body.setPosition(sf::Vector2f{ static_cast<float>(t_pos.x), static_cast<float>(t_pos.y) });
	m_body.setRadius(8.0f);
	m_body.setOrigin(sf::Vector2f{ m_body.getRadius(), m_body.getRadius() });
	m_body.setFillColor(sf::Color::Magenta);
}

void NPC::update(sf::Time& dt)
{
	// Update NPC
	m_velocity += (m_heading * m_speed) * dt.asSeconds();

	capVelocity();

	m_body.move(m_velocity);

	wrapAround();
}

void NPC::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

void NPC::wrapAround()
{
	if (m_body.getPosition().x > 800.0f + m_body.getGlobalBounds().width)
	{
		m_body.setPosition(sf::Vector2f{ -m_body.getGlobalBounds().width, m_body.getPosition().y });
	}
	else if (m_body.getPosition().x < -m_body.getGlobalBounds().width)
	{
		m_body.setPosition(sf::Vector2f{ 800.0f + m_body.getGlobalBounds().width, m_body.getPosition().y });
	}

	if (m_body.getPosition().y > 800.0f + m_body.getGlobalBounds().height)
	{
		m_body.setPosition(sf::Vector2f{ m_body.getPosition().x, -m_body.getGlobalBounds().height });
	}
	else if (m_body.getPosition().y < -m_body.getGlobalBounds().height)
	{
		m_body.setPosition(sf::Vector2f{ m_body.getPosition().x, 800.0f + m_body.getGlobalBounds().height });
	}
}

void NPC::capVelocity()
{
	if (m_velocity.x > c_MAX_VELOCITY.x)
		m_velocity.x = c_MAX_VELOCITY.x;
	else if (m_velocity.x < -c_MAX_VELOCITY.x)
		m_velocity.x = -c_MAX_VELOCITY.x;

	if (m_velocity.y > c_MAX_VELOCITY.y)
		m_velocity.y = c_MAX_VELOCITY.y;
	else if (m_velocity.y < -c_MAX_VELOCITY.y)
		m_velocity.y = -c_MAX_VELOCITY.y;
}
