#include "Character.h"

Character::Character(float t_speed,
	float t_acceleration,
	float t_rotationSpeed,
	float t_rotation, 
	std::string t_texturePath,
	Behaviour* t_behaviour,
	sf::Font* t_font,
	Character* t_targetPosition,
	sf::Vector2f t_position,
	float t_maximumSpeed,
	std::string t_textBox,
	bool t_isEnabled
	) :
	m_speed(t_speed),
	m_acceleration(t_acceleration),
	m_rotationSpeed(t_rotationSpeed),
	m_maximumSpeed(t_maximumSpeed),
	m_minimumSpeed(0.1f),
	m_behaviour(t_behaviour),
	m_targetCharacter(t_targetPosition),
	m_visionConeColour(sf::Color::Red),
	m_isEnabled(t_isEnabled),
	m_heading(0),
	m_visionConeDistance(200),
	m_originalMaxSpeed(t_maximumSpeed)
{
	m_position = t_position;
	initialiseSprite(t_texturePath);
	m_velocity = sf::Vector2f(1.0f, 1.0f);
	if (t_font != nullptr)
	{
		m_textBox.setFont(*t_font);
		m_textBox.setFillColor(sf::Color::White);
		m_textBox.setCharacterSize(16);
		m_textBox.setString(t_textBox);
		m_textBox.setPosition(m_position);
	}
	setVisionCone();
	m_targetPositionCircle.setFillColor(sf::Color::Red);
	m_targetPositionCircle.setRadius(20);
}

void Character::update(float t_deltaTime)
{
	if(m_behaviour) m_behaviour->update(this, t_deltaTime);
	m_position += m_velocity * t_deltaTime;
	m_sprite.setPosition(m_position);
	m_textBox.setPosition(m_position);
	updateRotation();
	handleBoundaries();
	updateVisionCone();	
}

void Character::setPosition(sf::Vector2f t_newPosition)
{
	m_position = t_newPosition;
	m_sprite.setPosition(m_position);
}


void Character::accelerate(float t_deltaTime)
{
	m_speed += m_acceleration;

	if (m_speed > m_maximumSpeed) m_speed = m_maximumSpeed;
	m_velocity = normaliseVector(m_velocity) * m_speed;
}

void Character::decelerate(float t_deltaTime)
{
	m_speed -= m_acceleration;

	if (m_speed < m_minimumSpeed) m_speed = m_minimumSpeed;
	m_velocity = normaliseVector(m_velocity) * m_speed;
}



void Character::setSpeed(float t_speed)
{
	m_speed = t_speed;

	if (m_speed > m_maximumSpeed) m_speed = m_maximumSpeed;
	if (m_speed < m_minimumSpeed) m_speed = m_minimumSpeed;
}



void Character::updateVisionCone()
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f);
	setVisionCone();

	if (m_targetCharacter)
	{
		bool result = isCharacterInVisionCone(m_targetCharacter->getPosition());
		if (result)
		{
			m_visionConeColour = sf::Color(0,255,0,125);
		}
		else
		{
			m_visionConeColour = sf::Color(255, 0, 0, 125);
		}
		drawVisionCone();
	}
}

void Character::drawVisionCone()
{
	m_cone.clear();
	m_cone.append(sf::Vertex(m_sprite.getPosition(), m_visionConeColour));
	float visionConeAngle = 50 * 3.14 / 180.0f;
	float min = atan2f(m_velocity.y, m_velocity.x) - visionConeAngle;
	float max = atan2f(m_velocity.y, m_velocity.x) + visionConeAngle;
	for (float a = min; a < max; a += 5 * (3.14 / 180.0f))
	{
		m_cone.append(sf::Vertex{ sf::Vector2f(cosf(a) * m_visionConeDistance, sinf(a) * m_visionConeDistance) + m_position, m_visionConeColour });
	}
}


bool Character::isCharacterInVisionCone(sf::Vector2f t_characterPosition)
{
	float minCross = (minVec.x * (m_targetCharacter->getPosition() - getPosition()).y) - (minVec.y * (m_targetCharacter->getPosition() - getPosition()).x);
	float maxCross = (maxVec.x * (m_targetCharacter->getPosition() - getPosition()).y) - (maxVec.y * (m_targetCharacter->getPosition() - getPosition()).x);

	sf::Vector2f distVec = m_targetCharacter->getPosition() - getPosition();

	if (minCross > 0 && maxCross < 0)
	{

		if (((distVec.x * distVec.x) + (distVec.y * distVec.y)) < m_visionConeDistance * m_visionConeDistance)
		{
			return true;
		}
	}
	return false;
}

void Character::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_sprite, t_states);

	t_target.draw(m_cone, t_states);
	if (m_useTargetCircle) t_target.draw(m_targetPositionCircle, t_states);
	if(m_textBox.getString().toAnsiString() != "") t_target.draw(m_textBox, t_states);
}

void Character::handleBoundaries()
{
	sf::Vector2f globalBounds = sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	if (m_sprite.getPosition().x + globalBounds.x > WINDOW_WIDTH)
	{
		setPosition(sf::Vector2f(globalBounds.x + 10, m_position.y));
	}
	else if (m_sprite.getPosition().x - globalBounds.x < 0)
	{
		setPosition(sf::Vector2f(WINDOW_WIDTH - globalBounds.x, m_position.y));
	}

	if (m_position.y - globalBounds.y > WINDOW_HEIGHT)
	{
		setPosition(sf::Vector2f(m_position.x, globalBounds.y));
	}
	else if (m_position.y + globalBounds.y < 0)
	{
		setPosition(sf::Vector2f(m_position.x, WINDOW_HEIGHT - globalBounds.y));
	}
}

void Character::initialiseSprite(std::string t_texturePath)
{
	if (!m_texture.loadFromFile(t_texturePath)) std::cout << "Problem loading texture" << std::endl;
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f);
	setPosition(m_position);
	updateRotation();
}

void Character::setVisionCone()
{
	float visionConeAngle = 50 * 3.14 / 180.0f;
	float min = atan2f(m_velocity.y, m_velocity.x) - visionConeAngle;
	float max = atan2f(m_velocity.y, m_velocity.x) + visionConeAngle;

	minVec = sf::Vector2f(cosf(min), sinf(min));
	maxVec = sf::Vector2f(cosf(max), sinf(max));
}

void Character::updateRotation()
{
	m_sprite.setRotation(atan2f(m_velocity.y, m_velocity.x) * (180.0f / 3.14));
}

void Character::moveToTarget(sf::Vector2f t_target, float t_deltaTime)
{
	if (distance(m_velocity) > m_maximumSpeed * m_maximumSpeed)
	{
		m_velocity = normaliseVector(m_velocity) * m_maximumSpeed;
	}

	m_velocity += t_target * m_speed * t_deltaTime;
}

void Character::turnLeft(float t_deltaTime)
{
	m_heading -= m_rotationSpeed * t_deltaTime;
	m_velocity = sf::Vector2f(cosf(m_heading), sinf(m_heading)) * m_speed;
	updateRotation();
}

void Character::turnRight(float t_deltaTime)
{
	m_heading += m_rotationSpeed * t_deltaTime;
	m_velocity = sf::Vector2f(cosf(m_heading), sinf(m_heading)) * m_speed;
	updateRotation();
}
