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

		if (magnitude < m_arrivalRadius) t_character->setSpeed(0.0f);		
		else if (magnitude > m_slowRadius) t_character->setSpeed(t_character->getMaxSpeed());
		else t_character->setSpeed(t_character->getMaxSpeed() * (magnitude / m_slowRadius));
	
		if (magnitude < m_arrivalRadius) 
			t_character->moveToTarget(normaliseVector(t_character->getTargetCharacter()->getPosition() - t_character->getPosition()) / 100.0f, t_deltaTime);
		else
			t_character->moveToTarget(normaliseVector(t_character->getTargetCharacter()->getPosition() - t_character->getPosition()), t_deltaTime);
	}
}
