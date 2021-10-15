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

	float m_speed = 0.01f;
	float m_acceleration;
	float m_rotationSpeed;
	float m_minimumSpeed;
	float m_maximumSpeed;
	float m_originalMaxSpeed;
	float m_heading;

	std::vector<sf::Vector2f> m_visionConeLeft;
	std::vector<sf::Vector2f> m_visionConeRight;

	const float c_MAX_SEE_AHEAD = 50.0f;

	sf::Text m_textBox;
	sf::Color m_visionConeColour;

	bool m_isEnabled;

	sf::CircleShape m_targetPositionCircle;

	bool m_useTargetCircle = false;
	float m_visionConeDistance;
	sf::VertexArray m_cone = sf::VertexArray{ sf::TriangleFan, 3 };
	sf::Vector2f minVec;
	sf::Vector2f maxVec;
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
		float t_maximumSpeed = 350,
		std::string t_textBox = "",
		bool t_isEnabled = true
	);
	~Character() {  }
	virtual void update(float t_deltaTime);

	void setPosition(sf::Vector2f t_newPosition);
	sf::Vector2f getPosition() { return m_sprite.getPosition(); }

	sf::Vector2f const getVelocity() const { return m_velocity; }

	void accelerate(float t_deltaTime);
	void decelerate(float t_deltaTime);

	Character* getTargetCharacter() const { return m_targetCharacter; }

	void setSpeed(float t_speed);
	void setMaxSpeed(float t_maxSpeed) { m_maximumSpeed = t_maxSpeed; }
	float getMaxSpeed() { return m_maximumSpeed; }
	float getOriginalMaxSpeed() { return m_originalMaxSpeed; }

	bool isCharacterInVisionCone(sf::Vector2f t_characterPosition);

	void setTexture() { m_sprite.setTexture(m_texture); }
	void moveToTarget(sf::Vector2f t_target, float t_deltaTime);

	void turnLeft(float t_deltaTime);
	void turnRight(float t_deltaTime);

	void setEnabled(bool t_enabled) { m_isEnabled = t_enabled; }
	bool isEnabled() { return m_isEnabled; }

	sf::CircleShape getTargetCircle() { return m_targetPositionCircle; }
	void setTargetCirclePosition(sf::Vector2f t_vector) { m_targetPositionCircle.setPosition(t_vector); }

	void useCircleTarget(bool t_useCircle) { m_useTargetCircle = t_useCircle; }
	bool getCircleTarget() { return m_useTargetCircle; }
private:
	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const;
	void handleBoundaries();
	void initialiseSprite(std::string t_texturePath);
	void setVisionCone();
	void updateRotation();
	void updateVisionCone();
	void drawVisionCone();
};

#include "Behaviour.h"