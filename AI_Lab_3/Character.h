#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"

class Behaviour;


class Character : public sf::Drawable
{
private:
	Behaviour* m_behaviour;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	sf::Vector2f* m_targetPosition;

	float m_speed;
	float m_acceleration;
	float m_rotationSpeed;
	float m_minimumSpeed;
	float m_maximumSpeed;
public:
	Character(float t_speed,
		float t_acceleration,
		float t_rotationSpeed,
		float t_rotation,
		std::string t_texturePath,
		Behaviour* t_behaviour,
		sf::Vector2f* t_targetPosition=nullptr);
	~Character() { if (m_behaviour) delete m_behaviour; }
	virtual void update(float t_deltaTime);

	void setPosition(sf::Vector2f t_newPosition);
	sf::Vector2f const getPosition() const { return m_sprite.getPosition(); }

	void setRotation(float t_newRotation);

	sf::Vector2f const getVelocity() const { return m_velocity; }
	void setVelocity(sf::Vector2f t_velocity);

	void accelerate(float t_deltaTime);
	void decelerate(float t_deltaTime);

	void rotate(int t_direction, float t_deltaTime);

	sf::Vector2f* getTargetPosition() const { return m_targetPosition; }

	void setSpeed(float t_speed);
	float getMaxSpeed() { return m_maximumSpeed; }
private:
	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const;
	void handleBoundaries();
	void initialiseSprite(std::string t_texturePath);
};

#include "Behaviour.h"