#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

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

	Character* m_targetCharacter;

	float m_speed;
	float m_acceleration;
	float m_rotationSpeed;
	float m_minimumSpeed;
	float m_maximumSpeed;
	float m_heading;

	std::vector<sf::Vector2f> m_visionConeLeft;
	std::vector<sf::Vector2f> m_visionConeRight;

	sf::Vector2f m_visionConeDir{ 1,0 };  // Initially point along the x-axis
	sf::VertexArray m_visionCone{sf::Lines};

	const float c_MAX_SEE_AHEAD = 50.0f;

	sf::Text m_textBox;
	sf::Color m_visionConeColour;
public:
	Character(float t_speed,
		float t_acceleration,
		float t_rotationSpeed,
		float t_rotation,
		std::string t_texturePath,
		Behaviour* t_behaviour,
		sf::Font* t_font,
		Character* t_targetPosition = nullptr,
		sf::Vector2f t_position = sf::Vector2f(400.0f, 300.0f),
		float t_maximumSpeed=150,
		std::string t_textBox=""
		);
	~Character() {  }
	virtual void update(float t_deltaTime);

	void setPosition(sf::Vector2f t_newPosition);
	sf::Vector2f getPosition()  { return m_sprite.getPosition(); }

	void setRotation(float t_newRotation);

	sf::Vector2f const getVelocity() const { return m_velocity; }
	void setVelocity(sf::Vector2f t_velocity);

	void accelerate(float t_deltaTime);
	void decelerate(float t_deltaTime);

	void rotate(int t_direction, float t_deltaTime);

	Character* getTargetCharacter() const { return m_targetCharacter; }

	void setSpeed(float t_speed);
	float getMaxSpeed() { return m_maximumSpeed; }

	std::pair<bool, bool> isCharacterInVisionCone(sf::Vector2f t_characterPosition);

	void setTexture() { m_sprite.setTexture(m_texture); }
	void moveToTarget(sf::Vector2f t_target, float t_deltaTime);

	void turnLeft(float t_deltaTime);
	void turnRight(float t_deltaTime);
private:
	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const;
	void handleBoundaries();
	void initialiseSprite(std::string t_texturePath);
	void setVisionCone(float t_angleWidth, float const MAX_SEE_AHEAD);
	void updateRotation();

	bool isPointRight(std::vector<sf::Vector2f> t_visionCone, sf::Vector2f t_characterPosition);
	void updateVisionCone();
};

#include "Behaviour.h"