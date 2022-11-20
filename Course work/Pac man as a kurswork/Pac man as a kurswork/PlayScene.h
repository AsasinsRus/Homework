#pragma once

#include "Scene.h"
#include <fstream>

class PlayScene : public Scene
{
	Clock gameTimer;
	int highscore;
	int* score;

	vector<SpriteRenderer> hearts;
	int health;

public:
	enum TextName
	{
		SCORE,
		HIGHSCORE,
		TIMER,
		ALERT
	};

	int bonusScore;

	PlayScene(Level& level, string fontPath, string highscorePath, string heartPath,int &score, int highscore = 0);

	void Update();

	void timerUpdate();
	void scoreUpdate();

	int getHealth();
	void setHealth(int upToThree);

	int getGameTimerAsSeconds();
	void resetGameTimer();

	int getHighscore();

	void resetLevel(string highscorePath);

	void draw(RenderWindow& window);
};

