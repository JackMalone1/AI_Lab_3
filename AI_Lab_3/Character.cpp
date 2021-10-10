#include "Character.h"

Character::Character(float t_speed,
	float t_acceleration,
	float t_rotationSpeed,
	float t_rotation, 
	std::string t_texturePath,
	Behaviour* t_behaviour,
	Character* t_targetPosition,
	sf::Vector2f t_position,
	float t_maximumSpeed
	) :
	m_speed(t_speed),
	m_acceleration(t_acceleration),
	m_rotationSpeed(t_rotationSpeed),
	m_maximumSpeed(t_maximumSpeed),
	m_minimumSpeed(-5),
	m_behaviour(t_behaviour),
	m_targetCharacter(t_targetPosition)
{
	m_position = t_position;
	initialiseSprite(t_texturePath);
	setRotation(t_rotation);
}

void Character::update(float t_deltaTime)
{
	if(m_behaviour) m_behaviour->update(this, t_deltaTime);
	m_sprite.move(sf::Vector2f(m_velocity.x * m_speed, m_velocity.y * m_speed ));
	m_position = m_sprite.getPosition();
	handleBoundaries();
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
}

void Character::decelerate(float t_deltaTime)
{
	m_speed -= m_acceleration;

	if (m_speed < m_minimumSpeed) m_speed = m_minimumSpeed;
}

void Character::rotate(int t_direction, float t_deltaTime)
{	
	if(t_direction == -1) setRotation((m_sprite.getRotation() - m_speed * m_rotationSpeed * t_deltaTime));
	else setRotation((m_sprite.getRotation() + m_speed * m_rotationSpeed * t_deltaTime));
}

void Character::setSpeed(float t_speed)
{
	m_speed = t_speed;

	if (m_speed > m_maximumSpeed) m_speed = m_maximumSpeed;
	if (m_speed < m_minimumSpeed) m_speed = m_minimumSpeed;
}

std::pair<bool, bool> Character::isCharacterInVisionCone(sf::Vector2f t_characterPosition)
{
	return std::pair<bool, bool>();
}

void Character::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_sprite, t_states);
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
