#pragma once

#include "Behaviour.h"
#include "SeekBehaviour.h"

class PursueBehaviour : public Behaviour
{
private:
	SeekBehaviour m_seekBehaviour;
private:
	sf::Vector2f normaliseVector(sf::Vector2f t_vector);
	float vectorMagnitude(sf::Vector2f t_vector);
public:
	void update(Character* t_character, float t_deltaTime);
};

