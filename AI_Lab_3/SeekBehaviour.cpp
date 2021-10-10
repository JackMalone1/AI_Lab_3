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
		sf::Vector2f distance = t_character->getTargetCharacter()->getPosition() - t_character->getPosition();
		distance = normaliseVector(distance);
		t_character->setRotation(atan2f(distance.y, distance.x) * (180 / 3.14f));
	}
}
