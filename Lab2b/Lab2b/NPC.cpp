#include "NPC.h"

NPC::NPC(sf::Vector2f t_pos)
{
	if (!m_bodyTex.loadFromFile("resources/sprites/npc.png"))
	{
		throw std::exception("Error loading NPC sprite!");
	}

	m_body.setTexture(m_bodyTex);
	m_body.setOrigin(m_bodyTex.getSize().x / 2.0f, m_bodyTex.getSize().y / 2.0f);
	m_body.setPosition(t_pos);
	m_body.setScale(sf::Vector2f{ 0.15f, 0.15f });

	m_heading.x = cos(m_body.getRotation());
	m_heading.y = sin(m_body.getRotation());
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
	if (m_body.getPosition().x > 800.0 + m_body.getGlobalBounds().width)
	{
		m_body.setPosition(sf::Vector2f{ -m_body.getGlobalBounds().width, m_body.getPosition().y });
	}
	else if (m_body.getPosition().x < -m_body.getGlobalBounds().width)
	{
		m_body.setPosition(sf::Vector2f{ 800.0f + m_body.getGlobalBounds().width, m_body.getPosition().y });
	}

	if (m_body.getPosition().y > 600.0 + m_body.getGlobalBounds().height)
	{
		m_body.setPosition(sf::Vector2f{ m_body.getPosition().x, -m_body.getGlobalBounds().height });
	}
	else if (m_body.getPosition().y < -m_body.getGlobalBounds().height)
	{
		m_body.setPosition(sf::Vector2f{ m_body.getPosition().x, 600.0f + m_body.getGlobalBounds().height });
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
