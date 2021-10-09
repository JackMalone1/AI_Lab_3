#pragma once
#include "Behaviour.h"
class WanderBehaviour :
    public Behaviour
{
    sf::Clock m_timer;
public:
    void update(Character* t_character, float t_deltaTime);
};

