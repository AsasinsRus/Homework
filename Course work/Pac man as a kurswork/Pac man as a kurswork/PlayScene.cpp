#include "PlayScene.h"

PlayScene::PlayScene(Level& level, string fontPath, string heartPath, string highscorePath,int &score, int highscore) : Scene(level, fontPath)
{
	this->highscore = highscore;
	this->score = &score;

	fstream readHighscore(highscorePath);

	if (readHighscore.is_open())
	{
		readHighscore >> highscore;
	}

	readHighscore.close();

	for (int i = 0; i < 4; i++)
	{
		text.push_back(Text("", font, 20));
	}

	text[HIGHSCORE].setString("Highscore: " + to_string(highscore));


	hearts.reserve(3);

	for (int i = 0; i < 3; i++)
	{
		hearts.push_back(SpriteRenderer(heartPath));
		hearts[i].sprite.setPosition(740 - (float)i * 50, 755);
		hearts[i].reloadTexture();
		hearts[i].sprite.setScale(3,3);
	}

	text[SCORE].setPosition(20,10);
	text[HIGHSCORE].setPosition(610,10);
	text[TIMER].setPosition(20, 760);

	text[ALERT].setPosition(250, 350);
	text[ALERT].setCharacterSize(50);

	this->health = 0;
	this->bonusScore = 0;
}

void PlayScene::Update()
{
	scoreUpdate();
	timerUpdate();
}

void PlayScene::timerUpdate()
{
	text[TIMER].setString("Timer: " + to_string((int)gameTimer.getElapsedTime().asSeconds() + bonusScore));
}

void PlayScene::scoreUpdate()
{
	text[SCORE].setString("Score: " + to_string(*score));
}

void PlayScene::resetLevel(string highscorePath)
{
	fstream readHighscore(highscorePath);

	if (readHighscore.is_open())
	{
		readHighscore >> highscore;
	}
	else highscore = 0;

	readHighscore.close();
	text[HIGHSCORE].setString("Highscore: " + to_string(highscore));

	gameTimer.restart();
}

void PlayScene::setHealth(int value)
{
	if (value < 4 && value >= 0)
	{
		this->health = value;
	}
}

int PlayScene::getHealth()
{
	return health;
}

void PlayScene::draw(RenderWindow& window)
{
	Scene::draw(window);

	if(health != 0)
	{
		for (int i = 0; i < health; i++)
		{
			window.draw(hearts[i].sprite);
		}
	}
}

int PlayScene::getGameTimerAsSeconds()
{
	return (int)gameTimer.getElapsedTime().asSeconds();
}

void PlayScene::resetGameTimer()
{
	gameTimer.restart();
}

int PlayScene::getHighscore()
{
	return highscore;
}