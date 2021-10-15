#pragma once
#include "Behaviour.h"
class WanderBehaviour :
    public Behaviour
{
    sf::Clock m_updateHeadingTimer;
    float m_secondsUntilTimerReset = 2;
    sf::Vector2f m_pointToTravelTowards;
    Character* m_targetCharacter;
    float m_targetCircleCentre;
    float m_targetCircleRadius;
    sf::Vector2f m_targetPosition;
private:
    void pickNewTravelTarget(Character* t_character);
public:
    void update(Character* t_character, float t_deltaTime);
    WanderBehaviour(Character* t_targetCharacter);
};

