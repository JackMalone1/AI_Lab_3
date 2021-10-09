#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "InputBehaviour.h"
#include "Character.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
private:
	sf::RenderWindow m_window;

	bool m_exitGame;

	Character m_player;
	Character m_wander;
};

#endif 