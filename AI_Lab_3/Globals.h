#pragma once
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

static float distance(sf::Vector2f vector)
{
	return (vector.x * vector.x) + (vector.y * vector.y);
}

static float vectorMagnitude(sf::Vector2f t_vector)
{
	return sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y));
}


static sf::Vector2f normaliseVector(sf::Vector2f t_vector)
{
	float magnitude = vectorMagnitude(t_vector);
	if (magnitude > 0) return t_vector / magnitude;
	return t_vector;
}

