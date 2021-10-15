#include "WanderBehaviour.h"

void WanderBehaviour::pickNewTravelTarget(Character* t_character)
{
	sf::Vector2f aheadPosition = t_character->getPosition() + (normaliseVector(t_character->getVelocity() * m_targetCircleCentre));
	float randDegree = (rand() % 180) * (3.14 / 180.0f);
	m_targetPosition = (sf::Vector2f(cosf(randDegree), sinf(randDegree)) * m_targetCircleRadius) + aheadPosition;
}

void WanderBehaviour::update(Character* t_character, float t_deltaTime)
{
	if (m_updateHeadingTimer.getElapsedTime().asSeconds() > m_secondsUntilTimerReset)
	{
		m_updateHeadingTimer.restart();
		pickNewTravelTarget(t_character);
	}
	t_character->moveToTarget(normaliseVector(m_targetPosition - t_character->getPosition()), t_deltaTime);
}

WanderBehaviour::WanderBehaviour(Character* t_targetCharacter) : m_targetCharacter(t_targetCharacter), m_targetCircleCentre(50), m_targetCircleRadius(50)
{
	pickNewTravelTarget(t_targetCharacter);
}
