#pragma once
#include "Behaviour.h"
class WanderBehaviour :
    public Behaviour
{
    sf::Clock m_updateHeadingTimer;
    float m_secondsUntilTimerReset = 2;
public:
    void update(Character* t_character, float t_deltaTime);
};

