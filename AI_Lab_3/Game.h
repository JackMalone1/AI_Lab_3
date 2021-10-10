#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "InputBehaviour.h"
#include "ArriveBehaviour.h"
#include "PursueBehaviour.h"
#include "SeekBehaviour.h"
#include "WanderBehaviour.h"
#include "Character.h"
#include <vector>

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
	std::vector<Character> m_npcs;
	sf::Font m_font;
};

#endif 