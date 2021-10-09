#pragma once

#include <SFML/Graphics.hpp>

class Character;

class Behaviour
{
public:
	virtual void update(Character* t_character, float t_deltaTime) = 0;
};

#include "Character.h"