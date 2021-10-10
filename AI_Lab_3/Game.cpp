#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "AI_Lab_3" },
	m_exitGame{ false },
	m_player(0.0f,5.0f,15.0f,0.0f,"ASSETS//IMAGES//tile_0008.png", new InputBehaviour())
{
	m_npcs.push_back(Character(0.0f, 5.0f, 15.0f, 0.0f, "ASSETS//IMAGES//tile_0007.png", new ArriveBehaviour(), &m_player, sf::Vector2f(100, 200),8));
	m_npcs.push_back(Character(0.0f, 5.0f, 15.0f, 0.0f, "ASSETS//IMAGES//tile_0007.png", new ArriveBehaviour(), &m_player, sf::Vector2f(100, 300)));
	m_npcs.push_back(Character(0.0f, 5.0f, 15.0f, 0.0f, "ASSETS//IMAGES//tile_0007.png", new WanderBehaviour(), &m_player, sf::Vector2f(100, 400)));
	m_npcs.push_back(Character(0.0f, 5.0f, 15.0f, 0.0f, "ASSETS//IMAGES//tile_0007.png", new SeekBehaviour(), &m_player, sf::Vector2f(100, 500)));
	m_npcs.push_back(Character(0.0f, 5.0f, 15.0f, 0.0f, "ASSETS//IMAGES//tile_0007.png", new PursueBehaviour(), &m_player, sf::Vector2f(100, 600)));
}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); 
			update(timePerFrame); 
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) 
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) 
		{
			processKeys(newEvent);
		}
	}
}



void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	m_player.update(t_deltaTime.asSeconds());

	for (Character& character : m_npcs)
	{
		character.update(t_deltaTime.asSeconds());
	}
}


void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_player);
	for (Character& character : m_npcs)
	{
		character.setTexture();
		m_window.draw(character);
	}

	m_window.display();
}

