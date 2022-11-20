#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include "Level.h"
#include "Animator.h"
#include "SpriteRenderer.h"


class Pac_man : public SpriteRenderer
{
	float movementSpeed;

	Animator animator;

	SoundBuffer chompB;
	SoundBuffer fruitB;
	SoundBuffer deathB;

	int health;
	int score;
	int direction;
	int choosedDirection;

	float scoreMultiplier;

	float deltaTime;
	float lastMoveTime;

	Clock timer;

	Level *level;

	void movementAnimation();
	void chooseDirection();

public:
	Pac_man(string path, string colorPath, Vector2f position, Level &level, float movementSpeed = 1, float animationSpeed = 0.07, int health = 1);

	Sound chompS;
	Sound deathS;
	Sound fruitS;

	void Update();
	void move();
	bool scoreColider();

	int getAxis(Keyboard::Key upKey, Keyboard::Key downKey, Keyboard::Key rightKey, Keyboard::Key leftKey);

	void deathAnimation();
	void chooseDirection(int direction);

	int getHealth();
	void setHealth(int health);

	int& getScore();
	void setScore(int score);

	float getMovementSpeed();
	void setMovementSpeed(float movementSpeed);

	void setCurrentLevel(Level &level);
	void setScoreMultiplier(float multilpier);

	friend class EntityManager;
	friend class SceneManager;
};

