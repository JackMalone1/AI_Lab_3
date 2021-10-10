#include "WanderBehaviour.h"

void WanderBehaviour::update(Character* t_character, float t_deltaTime)
{
	if (m_updateHeadingTimer.getElapsedTime().asSeconds() > m_secondsUntilTimerReset)
	{
		m_updateHeadingTimer.restart();
		if (rand() % 2 == 1) t_character->rotate(-1, t_deltaTime);
		else t_character->rotate(1, t_deltaTime);	
	}
}
