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
		sf::Vector2f direction = t_character->getTargetCharacter()->getPosition() - t_character->getPosition();
		float distance = vectorMagnitude(direction);
		float speed = vectorMagnitude(t_character->getVelocity());
		float maxTimePrediction = 2.5f;
		float timePrediction = 0.0f;

		if (speed <= distance / maxTimePrediction) timePrediction = maxTimePrediction;
		else timePrediction = distance / speed;

		sf::Vector2f targetPosition = t_character->getTargetCharacter()->getPosition() + sf::Vector2f(0.0f, 0.0f) * timePrediction;
		m_seekBehaviour.update(t_character, t_deltaTime);
	}
}
