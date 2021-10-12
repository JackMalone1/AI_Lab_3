#include "WanderBehaviour.h"

void WanderBehaviour::pickNewTravelTarget()
{
	sf::Vector2f aheadPosition = m_targetCharacter->getPosition() + (normaliseVector(m_targetCharacter->getVelocity() * m_targetCircleCentre));
	float randDegree = (rand() % 360) * (3.14 / 180.0f);
	m_targetPosition = (sf::Vector2f(cosf(randDegree), sinf(randDegree)) * m_targetCircleRadius) + aheadPosition;
}

void WanderBehaviour::update(Character* t_character, float t_deltaTime)
{
	if (m_updateHeadingTimer.getElapsedTime().asSeconds() > m_secondsUntilTimerReset)
	{
		m_updateHeadingTimer.restart();
		pickNewTravelTarget();
	}
	t_character->moveToTarget(normaliseVector(m_targetPosition - m_targetCharacter->getPosition()), t_deltaTime);
}

WanderBehaviour::WanderBehaviour(Character* t_targetCharacter) : m_targetCharacter(t_targetCharacter), m_targetCircleCentre(50), m_targetCircleRadius(50)
{
	pickNewTravelTarget();
}
