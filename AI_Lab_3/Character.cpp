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
	m_minimumSpeed(25),
	m_behaviour(t_behaviour),
	m_targetCharacter(t_targetPosition),
	m_visionConeColour(sf::Color::Red),
	m_isEnabled(t_isEnabled)
{
	m_position = t_position;
	initialiseSprite(t_texturePath);
	setRotation(t_rotation);
	if (t_font != nullptr)
	{
		m_textBox.setFont(*t_font);
		m_textBox.setFillColor(sf::Color::Black);
		m_textBox.setCharacterSize(16);
		m_textBox.setString(t_textBox);
		m_textBox.setPosition(m_position);
	}
	setVisionCone(90, c_MAX_SEE_AHEAD);
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

void Character::setRotation(float t_newRotation)
{
	m_velocity.x = cosf(t_newRotation * (3.14 / 180.0f));
	m_velocity.y = sinf(t_newRotation * (3.14 / 180.0f));
	m_sprite.setRotation(t_newRotation);
}

void Character::setVelocity(sf::Vector2f t_velocity)
{
	m_velocity = t_velocity;
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

void Character::rotate(int t_direction, float t_deltaTime)
{	
	if(t_direction == -1) setRotation((m_sprite.getRotation() - m_speed * m_rotationSpeed * t_deltaTime));
	else setRotation((m_sprite.getRotation() + m_speed * m_rotationSpeed * t_deltaTime));
	m_visionConeLeft.at(1).x = m_visionConeLeft.at(1).x * cos(m_rotationSpeed) - m_visionConeLeft.at(1).y * sin(m_rotationSpeed) * (3.14 / 180.0f);
	m_visionConeLeft.at(1).y = m_visionConeLeft.at(1).x * sin(m_rotationSpeed) + m_visionConeLeft.at(1).y * cos(m_rotationSpeed) * (3.14 / 180.0f);

	m_visionConeRight.at(1).x = m_visionConeRight.at(1).x * cos(m_rotationSpeed) - m_visionConeRight.at(1).y * sin(m_rotationSpeed) * (3.14 / 180.0f);
	m_visionConeRight.at(1).y = m_visionConeRight.at(1).x * sin(m_rotationSpeed) + m_visionConeRight.at(1).y * cos(m_rotationSpeed) * (3.14 / 180.0f);
}

void Character::setSpeed(float t_speed)
{
	m_speed = t_speed;

	if (m_speed > m_maximumSpeed) m_speed = m_maximumSpeed;
	if (m_speed < m_minimumSpeed) m_speed = m_minimumSpeed;
}

bool Character::isPointRight(std::vector<sf::Vector2f> t_visionCone, sf::Vector2f t_characterPosition)
{
	return (t_visionCone[1].x - t_visionCone[0].x)
		* (t_characterPosition.y - t_visionCone[0].y)
		- (t_visionCone[1].y - t_visionCone[0].y)
		* (t_characterPosition.x - t_visionCone[0].x)
	> 0;
}

void Character::updateVisionCone()
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f);
	setVisionCone(90, c_MAX_SEE_AHEAD);

	if (m_targetCharacter)
	{
		std::pair<bool, bool> result = isCharacterInVisionCone(m_targetCharacter->getPosition());
		if (!(result.first && result.second) && !(!result.first && !result.second))
		{
			m_visionConeColour = sf::Color::Green;
		}
		else
		{
			m_visionConeColour = sf::Color::Red;
		}
	}
}


std::pair<bool, bool> Character::isCharacterInVisionCone(sf::Vector2f t_characterPosition)
{
	bool isPlayerLeft = false;
	bool isPlayerRight = false;
	if (!isPointRight(m_visionConeRight, t_characterPosition))
	{
		isPlayerRight = true;
	}
	if (isPointRight(m_visionConeLeft, t_characterPosition))
	{
		isPlayerLeft = true;
	}
	return std::pair<bool, bool>(isPlayerLeft, isPlayerRight);
}

void Character::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_sprite, t_states);
	sf::VertexArray visionCone(sf::Lines);
	visionCone.append(sf::Vertex(m_visionConeLeft[0], m_visionConeColour));
	visionCone.append(sf::Vertex(m_visionConeLeft[1], m_visionConeColour));
	visionCone.append(sf::Vertex(m_visionConeRight[0], m_visionConeColour));
	visionCone.append(sf::Vertex(m_visionConeRight[1], m_visionConeColour));
	visionCone.append(sf::Vertex(m_visionConeLeft[1], m_visionConeColour));
	visionCone.append(sf::Vertex(m_visionConeRight[1], m_visionConeColour));
	visionCone.append(sf::Vertex(m_visionConeDir, m_visionConeColour));
	t_target.draw(visionCone, t_states);
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
	m_sprite.setScale(sf::Vector2f(4.0f, 4.0f));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f);
	setPosition(m_position);
}

void Character::setVisionCone(float t_angleWidth, float const MAX_SEE_AHEAD)
{
	m_visionConeLeft.clear();
	sf::Vector2f leftPosition = m_sprite.getPosition();
	m_visionConeDir.x = m_sprite.getPosition().x * cos(-t_angleWidth) - m_sprite.getPosition().y * sin(-t_angleWidth);
	m_visionConeDir.y = m_sprite.getPosition().x * sin(-t_angleWidth) + m_sprite.getPosition().y * cos(-t_angleWidth);
	m_visionConeLeft.push_back(leftPosition);
	m_visionConeLeft.push_back(sf::Vector2f(leftPosition.x + (m_visionConeDir.x * MAX_SEE_AHEAD),
		leftPosition.y + (m_visionConeDir.y * MAX_SEE_AHEAD)));
	sf::Vector2f rightPosition = m_sprite.getPosition();
	m_visionConeDir.x = m_sprite.getPosition().x * cos(t_angleWidth*2) - m_sprite.getPosition().y * sin(t_angleWidth*2);
	m_visionConeDir.y = m_sprite.getPosition().x * sin(t_angleWidth * 2) + m_sprite.getPosition().y * cos(t_angleWidth * 2);
	m_visionConeRight.clear();
	m_visionConeRight.push_back(rightPosition);
	m_visionConeRight.push_back(sf::Vector2f(rightPosition.x + (m_visionConeDir.x * MAX_SEE_AHEAD),
		rightPosition.y + (m_visionConeDir.y * MAX_SEE_AHEAD)));
	m_visionConeDir.x = m_sprite.getPosition().x * cos(-t_angleWidth) - m_sprite.getPosition().y * sin(-t_angleWidth);
	m_visionConeDir.y = m_sprite.getPosition().x * sin(-t_angleWidth) + m_sprite.getPosition().y * cos(-t_angleWidth);
}

void Character::updateRotation()
{
	m_sprite.setRotation(atan2f(m_velocity.y, m_velocity.x));
	m_visionConeLeft.at(1).x = m_visionConeLeft.at(1).x * cos(m_rotationSpeed) - m_visionConeLeft.at(1).y * sin(m_rotationSpeed) * (3.14 / 180.0f);
	m_visionConeLeft.at(1).y = m_visionConeLeft.at(1).x * sin(m_rotationSpeed) + m_visionConeLeft.at(1).y * cos(m_rotationSpeed) * (3.14 / 180.0f);

	m_visionConeRight.at(1).x = m_visionConeRight.at(1).x * cos(m_rotationSpeed) - m_visionConeRight.at(1).y * sin(m_rotationSpeed) * (3.14 / 180.0f);
	m_visionConeRight.at(1).y = m_visionConeRight.at(1).x * sin(m_rotationSpeed) + m_visionConeRight.at(1).y * cos(m_rotationSpeed) * (3.14 / 180.0f);
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
	m_heading += m_rotationSpeed * t_deltaTime;
	m_velocity = sf::Vector2f(cosf(m_heading), sinf(m_heading)) * m_speed;
	updateRotation();
}

void Character::turnRight(float t_deltaTime)
{
	m_heading -= m_rotationSpeed * t_deltaTime;
	m_velocity = sf::Vector2f(cosf(m_heading), sinf(m_heading)) * m_speed;
	updateRotation();
}
