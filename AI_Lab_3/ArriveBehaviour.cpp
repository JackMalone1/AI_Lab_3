#include "ArriveBehaviour.h"

sf::Vector2f ArriveBehaviour::normaliseVector(sf::Vector2f t_vector)
{
	return t_vector / sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y));
}

void ArriveBehaviour::update(Character* t_character, float t_deltaTime)
{
	if (t_character->getTargetPosition() == nullptr) return;

	if (t_character->getPosition() != *t_character->getTargetPosition())
	{
		sf::Vector2f steeringLinear = *t_character->getTargetPosition() - t_character->getPosition();
		float magnitude = sqrt((steeringLinear.x * steeringLinear.x) + (steeringLinear.y * steeringLinear.y));
		if (magnitude < m_arrivalRadius)
		{
			t_character->setSpeed(0);
		}
		else if (magnitude > m_slowRadius)
		{
			t_character->setSpeed(t_character->getMaxSpeed());
		}
		else
		{
			t_character->setSpeed(t_character->getMaxSpeed() * (magnitude / m_slowRadius));
		}

		sf::Vector2f velocity = steeringLinear;
		velocity = normaliseVector(velocity);
		velocity *= t_character->getMaxSpeed();
		t_character->setVelocity(velocity);
	}
}