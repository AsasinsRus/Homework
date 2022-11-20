#pragma once

#include "SFML/Audio.hpp"
#include "Level.h"
#include "Animator.h"
#include "SpriteRenderer.h"

class Ghost : public SpriteRenderer
{
public:
	enum State
	{
		DEAD,
		ALIVE
	};

	Texture death;

	Sound hitS;
	Sound deathS;

	Ghost(string path, string deathPath, Vector2f position, Color color, Level& level, State state = ALIVE, float movementSpeed = 1);

	void Update();
	void move();

	bool colides(FloatRect colider);
	void resetPosition(int index);

	void setLevel(Level &level);

	int getState();
	void setState(State state);

	float getMovementSpeed();
	void setMovementSpeed(float movementSpeed);

	friend class EntityManager;
	
private:
	Level* level;
	State state;

	SoundBuffer hitB;
	SoundBuffer deathB;

	float deltaTime;
	float lastMoveTime;
	Clock timer;
	Clock randDirectionTimer;

	float movementSpeed;
	int direction;
	int choosedDirection;

	void chooseDirection();
	int randNonColiderPosition();
	bool isNextCellFree(int direction);
};

