#include "Player.h"

Player::Player(sf::Vector2f t_pos) : m_position(t_pos)
{
	if (!m_bodyTex.loadFromFile("resources/sprites/player.png"))
	{
		throw std::exception("Error loading Player sprite!");
	}

	m_body.setTexture(m_bodyTex);
	m_body.setOrigin(m_bodyTex.getSize().x / 2.0f, m_bodyTex.getSize().y / 2.0f);
	m_body.setScale(sf::Vector2f{ 0.15f, 0.15f });

	m_heading.x = cos((3.14159 / 180.0f) * m_body.getRotation());
	m_heading.y = sin((3.14159 / 180.0f) * m_body.getRotation());
}

void Player::update(sf::Time& dt)
{
	handleInput(dt);

	capVelocity();

	m_position += m_velocity;

	m_body.setPosition(m_position);

	wrapAround();
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

void Player::handleInput(sf::Time& dt)
{
	// Update Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_velocity += (m_heading * m_speed) * dt.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_velocity -= (m_heading * m_speed) * dt.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_rotation += -m_rotationSpeed;
		m_heading.x = cos((3.14159 / 180.0f) * m_rotation);
		m_heading.y = sin((3.14159 / 180.0f) * m_rotation);
		m_body.setRotation(m_rotation);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_rotation += m_rotationSpeed;
		m_heading.x = cos((3.14159 / 180.0f) * m_rotation);
		m_heading.y = sin((3.14159 / 180.0f) * m_rotation);
		m_body.setRotation(m_rotation);
	}
}

void Player::wrapAround()
{
	if (m_position.x > 800.0 + m_body.getGlobalBounds().width)
	{
		m_position = sf::Vector2f{-m_body.getGlobalBounds().width, m_position.y};
	}
	else if (m_position.x < -m_body.getGlobalBounds().width)
	{
		m_position = sf::Vector2f{ 800.0f + m_body.getGlobalBounds().width, m_position.y };
	}

	if (m_position.y > 600.0 + m_body.getGlobalBounds().height)
	{
		m_position = sf::Vector2f{ m_position.x, -m_body.getGlobalBounds().height };
	}
	else if (m_position.y < -m_body.getGlobalBounds().height)
	{
		m_position = sf::Vector2f{ m_position.x, 600.0f + m_body.getGlobalBounds().height };
	}
}

void Player::capVelocity()
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
