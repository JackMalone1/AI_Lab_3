#pragma once
#include "Behaviour.h"
class SeekBehaviour : public Behaviour
{
private:
	sf::Vector2f normaliseVector(sf::Vector2f t_vector);
	float m_arrivalRadius = 100;
	float m_slowRadius = 300;
public:
	void update(Character* t_character, float t_deltaTime);
};

