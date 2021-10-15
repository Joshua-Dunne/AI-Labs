#include "NPC.h"

NPC::NPC(sf::Vector2f t_pos) : m_position(t_pos), m_bodyTex(nullptr)
{
	if (!m_font.loadFromFile("resources/fonts/arial.ttf"))
	{
		throw std::exception("Unable to load arial.ttf in NPC!");
	}
}

void NPC::render(sf::RenderWindow& t_window)
{
	if (m_isActive)
	{
		t_window.draw(m_body);

		drawVisionCone(t_window);

		t_window.draw(m_name);
	}
		
}

void NPC::wrapAround()
{
	if (m_body.getPosition().x > SCREEN_WIDTH + m_body.getGlobalBounds().width)
	{
		m_position = sf::Vector2f{ -m_body.getGlobalBounds().width, m_body.getPosition().y };
	}
	else if (m_body.getPosition().x < -m_body.getGlobalBounds().width)
	{
		m_position = sf::Vector2f{ SCREEN_WIDTH + m_body.getGlobalBounds().width, m_body.getPosition().y };
	}

	if (m_body.getPosition().y > SCREEN_HEIGHT + m_body.getGlobalBounds().height)
	{
		m_position = sf::Vector2f{ m_body.getPosition().x, -m_body.getGlobalBounds().height };
	}
	else if (m_body.getPosition().y < -m_body.getGlobalBounds().height)
	{
		m_position = sf::Vector2f{ m_body.getPosition().x, SCREEN_HEIGHT + m_body.getGlobalBounds().height };
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

float NPC::getNewOrientation(float t_current, sf::Vector2f t_velocity)
{
	if (getLength(t_velocity) > 0) {
		// Note atan2 returns an angle in radians which you 
				// may want to convert to degrees.
		return atan2(-m_position.x, m_position.y);
	}
	else
		return t_current;
}

void NPC::drawVisionCone(sf::RenderWindow& t_window)
{
	m_vision[0] = sf::Vertex(sf::Vector2f(), sf::Color::Red);
	m_vision[1] = sf::Vertex(sf::Vector2f(), sf::Color::Transparent);
	m_vision[2] = sf::Vertex(sf::Vector2f(), sf::Color::Transparent);

	float radians = (m_visionAngle / 2.0f) * (3.14159f / 180.0f);
	float rotationRadians = m_rotation * (3.14159f / 180.0f);

	m_vision[0].position = m_position;
	m_vision[1].position = m_position + sf::Vector2f{ cos((rotationRadians - radians / 2.0f)), sin((rotationRadians - radians / 2.0f)) } * m_visionRange;
	m_vision[2].position = m_position + sf::Vector2f{ cos((rotationRadians + radians / 2.0f)), sin((rotationRadians + radians / 2.0f)) } * m_visionRange;

	if (isLeft(m_vision[0].position, m_vision[1].position, m_target))
	{
		if (!isLeft(m_vision[0].position, m_vision[2].position, m_target))
		{
			float distance = getLength(m_position - m_target);
			
			if (distance < m_visionRange)
			{
				m_vision[0].color = sf::Color::Green;
			}
		}
	}

	t_window.draw(m_vision);
}

void NPC::initialize(sf::Texture* t_tex)
{
	m_bodyTex = t_tex;

	m_body.setTexture(*m_bodyTex);
	m_body.setPosition(m_position);
	m_body.setOrigin(m_bodyTex->getSize().x / 2.0f, m_bodyTex->getSize().y / 2.0f);
	m_body.setScale(sf::Vector2f{ 0.15f, 0.15f });
	m_body.setRotation(m_rotation);

	m_heading.x = static_cast<float>(cos(static_cast<double>((3.14159 / 180.0f) * m_rotation)));
	m_heading.y = static_cast<float>(sin(static_cast<double>((3.14159 / 180.0f) * m_rotation)));
}
