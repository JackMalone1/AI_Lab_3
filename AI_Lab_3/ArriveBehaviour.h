#pragma once

#include "Behaviour.h"

class ArriveBehaviour : public Behaviour
{
	float m_arrivalRadius = 150;
	float m_slowRadius = 300;

private:
	sf::Vector2f normaliseVector(sf::Vector2f t_vector);
	float vectorMagnitude(sf::Vector2f t_vector);
public:
	void update(Character* t_character, float t_deltaTime);
};

