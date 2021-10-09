#pragma once

#include "Behaviour.h"

class InputBehaviour : public Behaviour
{
public:
	void update(Character* t_character, float t_deltaTime);
};

