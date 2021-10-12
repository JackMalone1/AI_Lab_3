#include "ArriveBehaviour.h"

sf::Vector2f ArriveBehaviour::normaliseVector(sf::Vector2f t_vector)
{
	return t_vector / vectorMagnitude(t_vector);
}

float ArriveBehaviour::vectorMagnitude(sf::Vector2f t_vector)
{
	return sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y));
}

void ArriveBehaviour::update(Character* t_character, float t_deltaTime)
{
	if (t_character->getTargetCharacter() == nullptr) return;

	if (t_character->getPosition() != t_character->getTargetCharacter()->getPosition())
	{
		sf::Vector2f steeringLinear = t_character->getTargetCharacter()->getPosition() - t_character->getPosition();
		float magnitude = sqrt((steeringLinear.x * steeringLinear.x) + (steeringLinear.y * steeringLinear.y));

		if (magnitude < m_arrivalRadius) t_character->setSpeed(0);		
		else if (magnitude > m_slowRadius) t_character->setSpeed(t_character->getMaxSpeed());
		else t_character->setSpeed(t_character->getMaxSpeed() * (magnitude / m_slowRadius));
		
		sf::Vector2f velocity = steeringLinear;
		velocity = normaliseVector(velocity);
		velocity *= t_character->getMaxSpeed();
		float timeToTarget = 5.5f;
		sf::Vector2f direction = velocity - t_character->getVelocity();
		direction /= timeToTarget;

		if (vectorMagnitude(direction) > t_character->getMaxSpeed())
		{
			direction = normaliseVector(direction);
			direction *= t_character->getMaxSpeed();
		}

		t_character->setVelocity(direction);
	}
}
