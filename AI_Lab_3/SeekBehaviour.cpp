#include "SeekBehaviour.h"

sf::Vector2f SeekBehaviour::normaliseVector(sf::Vector2f t_vector)
{
	return t_vector / sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y));
}

void SeekBehaviour::update(Character* t_character, float t_deltaTime)
{
	if (t_character->getTargetCharacter() == nullptr) return;//cant seek if there's no target position

	if (t_character->getPosition() != t_character->getTargetCharacter()->getPosition())
	{
		

		sf::Vector2f steeringLinear = t_character->getTargetCharacter()->getPosition() - t_character->getPosition();
		float magnitude = sqrt((steeringLinear.x * steeringLinear.x) + (steeringLinear.y * steeringLinear.y));
		t_character->moveToTarget(normaliseVector(t_character->getTargetCharacter()->getPosition() - t_character->getPosition()), t_deltaTime);
	}
}
