#pragma once

#include "Behaviour.h"

class PursueBehaviour : public Behaviour
{
public:
	void update(Character* t_character, float t_deltaTime);
};

