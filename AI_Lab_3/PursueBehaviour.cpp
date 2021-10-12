#include "PursueBehaviour.h"

sf::Vector2f PursueBehaviour::normaliseVector(sf::Vector2f t_vector)
{
	return t_vector / vectorMagnitude(t_vector);
}

float PursueBehaviour::vectorMagnitude(sf::Vector2f t_vector)
{
	return sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y));
}


void PursueBehaviour::update(Character* t_character, float t_deltaTime)
{
	if (t_character->getTargetCharacter() == nullptr) return;

	if (t_character->getPosition() != t_character->getTargetCharacter()->getPosition())
	{
		sf::Vector2f velocity = t_character->getVelocity();
		float speed = (velocity.x * velocity.x) + (velocity.y * velocity.y);

		if (speed == 0) speed = 1;

		sf::Vector2f pointAheadOfPlayer = (normaliseVector(t_character->getTargetCharacter()->getVelocity())) * vectorMagnitude(t_character->getTargetCharacter()->getPosition()
			- t_character->getPosition() / speed);

		t_character->moveToTarget(normaliseVector(pointAheadOfPlayer - t_character->getPosition()), t_deltaTime);
	}
}
