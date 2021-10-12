#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "AI_Lab_3" },
	m_exitGame{ false },
	m_player(0.0f,35.0f,60.0f * (3.14 / 180.0f),0.0f,"ASSETS//IMAGES//tile_0008.png", new InputBehaviour(), nullptr)
{
	if (!m_font.loadFromFile("ASSETS//FONTS//ariblk.ttf")) std::cout << "error loading font for text box" << std::endl;
	m_npcs.push_back(Character(0.0f, 45.0f, 90.0f * (3.14 / 180.0f), 0.0f, "ASSETS//IMAGES//tile_0007.png", new ArriveBehaviour(),
		&m_font, &m_player, sf::Vector2f(100, 200),120,
		"Arrive Slow", false));
	m_npcs.push_back(Character(0.0f, 90.0f, 90.0f * (3.14 / 180.0f), 0.0f, "ASSETS//IMAGES//tile_0007.png", new ArriveBehaviour(),
		&m_font, &m_player, sf::Vector2f(100, 300),190,
		"Arrive Fast", false));
	m_npcs.push_back(Character(70.0f, 35.0f, 90.0f * (3.14 / 180.0f), 0.0f, "ASSETS//IMAGES//tile_0007.png", new WanderBehaviour(&m_player),
		&m_font, &m_player, sf::Vector2f(100, 400),150,
		"Wander", false));
	m_npcs.push_back(Character(70.0f, 85.0f, 90.0f * (3.14 / 180.0f), 0.0f, "ASSETS//IMAGES//tile_0007.png", new SeekBehaviour(),
		&m_font, &m_player, sf::Vector2f(100, 500),200,
		"Seek", false));
	m_npcs.push_back(Character(35.0f, 60.0f, 90.0f * (3.14 / 180.0f), 0.0f, "ASSETS//IMAGES//tile_0007.png", new PursueBehaviour(),
		&m_font, &m_player, sf::Vector2f(100, 600),150,
		"Pursue", false));
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) m_npcs.at(0).setEnabled(!m_npcs.at(0).isEnabled());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) m_npcs.at(1).setEnabled(!m_npcs.at(1).isEnabled());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) m_npcs.at(2).setEnabled(!m_npcs.at(2).isEnabled());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) m_npcs.at(3).setEnabled(!m_npcs.at(3).isEnabled());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) m_npcs.at(4).setEnabled(!m_npcs.at(4).isEnabled());
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
		if(character.isEnabled()) character.update(t_deltaTime.asSeconds());
	}
}


void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_player);
	for (Character& character : m_npcs)
	{
		if (character.isEnabled())
		{
			character.setTexture();
			m_window.draw(character);
		}
	}

	m_window.display();
}

