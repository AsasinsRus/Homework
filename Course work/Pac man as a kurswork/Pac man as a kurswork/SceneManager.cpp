#include "SceneManager.h"

SceneManager::SceneManager(Level& level, Pac_man& pacman, Ghost* ghosts, MainMenuScene& menuScene, PlayScene& playScene, PauseScene& pauseScene, CustumizeScene& custumizeScene)
{
	this->level = &level;
	this->pacman = &pacman;
	this->ghosts = ghosts;
	this->menuScene = &menuScene;
	this->playScene = &playScene;
	this->pauseScene = &pauseScene;
	this->custumizeScene = &custumizeScene;

	menu = MAINMENU;
	choosedLevel = 0;
	volumeSounds = 30;
	volumeMusic = 30;
	difficulty = NORMAL;

	deltaTime = 0;
	lastMoveTime = 0;

	for (int i = 0; i < 4; i++)
	{
		ghostsColor[i] = ghosts[i].sprite.getColor();
	}

	soundtracksB[0].loadFromFile("sounds/MT.ogg");
	soundtracksB[1].loadFromFile("sounds/song1.ogg");
	soundtracksB[2].loadFromFile("sounds/song2.ogg");
	soundtracksB[3].loadFromFile("sounds/song3.ogg");
	soundtracksB[4].loadFromFile("sounds/song4.ogg");
	soundtracksB[5].loadFromFile("sounds/song5.ogg");
	soundtracksB[6].loadFromFile("sounds/song6.ogg");
	soundtracksB[7].loadFromFile("sounds/song7.ogg");
	soundtracksB[8].loadFromFile("sounds/song8.ogg");

	for (int i = 0; i < 9; i++)
	{
		soundtracksS[i].setBuffer(soundtracksB[i]);
		soundtracksS[i].setVolume(30);
		soundtracksS[i].setLoop(true);
	}

	soundtracksS[0].play();
}

void SceneManager::updateAndDraw(RenderWindow& window)
{
	switch (menu)
	{
	case MAINMENU:
		mainMenuUpdate(window);

		break;
	case GAME:
		gameUpdate(window);

		break;
	case PAUSE:
		pauseUpdate(window);

		break;
	case REDACT:
		redactUpdate(window);

		break;
	case REDACTPAUSE:
		redactPauseUpdate(window);

		break;
	case CUSTOMIZE:
		custumizeUpdate(window);

		break;
	}
}

void SceneManager::mainMenuUpdate(RenderWindow& window)
{
	chooseLevel(window);

	if (menuScene->button[MainMenuScene::ButtonName::START].isPressed(Mouse::Left, window))
	{
		menu = GAME;
		pacman->score = 0;
		playScene->bonusScore = 0;

		playScene->resetGameTimer();

		switch (difficulty)
		{
		case EASY:
			playScene->setHealth(0);
			break;
		case NORMAL:
			playScene->setHealth(3);
			break;
		case HARD:
			playScene->setHealth(1);
			break;
		}

		level->restart();
		pacman->sprite.setPosition(*level->getEntityPostion(0));

		for (int i = 0; i < level->getEntityCount() - 1; i++)
		{
			ghosts[i].resetPosition(i + 1);
		}
	}

	if (timer.getElapsedTime() > milliseconds(buttonTimer) && menuScene->button[MainMenuScene::ButtonName::CUSTOMIZE].isPressed(Mouse::Left, window))
	{
		timer.restart();
		menu = CUSTOMIZE;
	}

	if (menuScene->button[MainMenuScene::ButtonName::QUIT].isPressed(Mouse::Left, window))
	{
		window.close();
	}

	if (timer.getElapsedTime() > milliseconds(buttonTimer))
	{
		if (menuScene->text[MainMenuScene::TextName::DIFFICULTY].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				timer.restart();
				swithDifficulties();
			}
		}

		if (menuScene->text[MainMenuScene::TextName::SOUNDS].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				timer.restart();

				if ((string)menuScene->text[MainMenuScene::TextName::SOUNDS].getString() == "Sounds")
				{
					menuScene->text[MainMenuScene::TextName::SOUNDS].setString("Music");
				}
				else
				{
					menuScene->text[MainMenuScene::TextName::SOUNDS].setString("Sounds");
				}
			}
		}
	}

	if (menuScene->text[MainMenuScene::TextName::SOUNDS].getString() == "Sounds")
	{
		int volume = menuScene->slider[0].getValue(Mouse::Left, window);

		pacman->chompS.setVolume(volume);
		pacman->deathS.setVolume(volume);
		pacman->fruitS.setVolume(volume);

		for (int i = 0; i < 4; i++)
		{
			ghosts[i].hitS.setVolume(volume);
			ghosts[i].deathS.setVolume(volume);
		}
	}
	if (menuScene->text[MainMenuScene::TextName::SOUNDS].getString() == "Music")
	{
		int volume = menuScene->slider[0].getValue(Mouse::Left, window);

		for (int i = 0; i < 9; i++)
		{
			soundtracksS[i].setVolume(volume);
		}
	}

	menuScene->draw(window);
}

void SceneManager::gameUpdate(RenderWindow& window)
{
	if (timer.getElapsedTime() > milliseconds(buttonTimer))
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			timer.restart();
			menu = PAUSE;
		}
	}

	if (pacman->scoreColider())
	{
		murdaryTimer.restart();
	}
	else
	{
		reviving();

		if (murdaryTimer.getElapsedTime() < seconds(5))
		{
			fruitKiller();
		}

		if (ghosts[0].sprite.getColor() == Color::Blue && murdaryTimer.getElapsedTime() > seconds(5))
		{
			for (int i = 0; i < 4; i++)
			{
				if (ghosts[i].sprite.getColor() == Color::Blue)
				{
					ghosts[i].sprite.setColor(ghostsColor[i]);
				}
			}
		}

		if (deathDetector())
		{
			for (int i = 0; i < level->getEntityCount() - 1; i++)
			{
				ghosts[i].resetPosition(i + 1);
			}

			pacman->deathAnimation();

			if (playScene->text[PlayScene::TextName::ALERT].getString() == "")
			{
				if (playScene->text[PlayScene::ALERT].getString() == "")
				{
					pacman->deathS.play();
					pacman->animator.direction = 4;
					pacman->animator.frame = 0;
				}

				alertTimer.restart();
				playScene->text[PlayScene::TextName::ALERT].setString("Game over!");
				playScene->text[PlayScene::TextName::ALERT].setFillColor(Color::Red);
			}

			if (alertTimer.getElapsedTime() > seconds(3))
			{
				playScene->text[PlayScene::TextName::ALERT].setString("");
				menu = MAINMENU;
			}
		}
		else if (pacman->score >= *level->getScoreToWin() * pacman->scoreMultiplier)
		{
			if (pacman->score + playScene->bonusScore - (playScene->getGameTimerAsSeconds() * 5) > playScene->getHighscore())
			{
				saveHighscore(pacman->score - (playScene->getGameTimerAsSeconds() * 5));
			}

			if (playScene->text[PlayScene::TextName::ALERT].getString() == "")
			{
				alertTimer.restart();
				playScene->text[PlayScene::TextName::ALERT].setString("You win!");
				playScene->text[PlayScene::TextName::ALERT].setFillColor(Color::Green);
			}

			if (alertTimer.getElapsedTime() > seconds(3))
			{
				playScene->text[PlayScene::TextName::ALERT].setString("");
				menu = MAINMENU;
			}
		}
		else
		{
			playScene->Update();
			pacman->Update();

			for (int i = 0; i < 4; i++)
			{
				if (ghosts[i].getState() != Ghost::DEAD)
					ghosts[i].Update();
			}
		}
	}


	for (int i = 0; i < 4; i++)
	{
		ghosts[i].draw(window);
	}
	pacman->draw(window);
	playScene->draw(window);
}

void SceneManager::pauseUpdate(RenderWindow& window)
{
	if (timer.getElapsedTime() > milliseconds(buttonTimer))
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			timer.restart();
			menu = GAME;
		}
	}

	if (timer.getElapsedTime() > milliseconds(buttonTimer))
	{
		if (pauseScene->button[PauseScene::ButtonName::BACK].isPressed(Mouse::Left, window))
		{
			timer.restart();
			menu = MAINMENU;
		}
	}

	if (timer.getElapsedTime() > milliseconds(buttonTimer))
	{
		if (pauseScene->text[PauseScene::TextName::VOLUME].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				timer.restart();

				if ((string)pauseScene->text[PauseScene::TextName::VOLUME].getString() == "Sounds")
				{
					pauseScene->text[PauseScene::TextName::VOLUME].setString("Music");
				}
				else
				{
					pauseScene->text[PauseScene::TextName::VOLUME].setString("Sounds");
				}
			}
		}
	}

	if (pauseScene->text[PauseScene::TextName::VOLUME].getString() == "Sounds")
	{
		int volume = pauseScene->slider[0].getValue(Mouse::Left, window);

		pacman->chompS.setVolume(volume);
		pacman->deathS.setVolume(volume);
		pacman->fruitS.setVolume(volume);

		for (int i = 0; i < 4; i++)
		{
			ghosts[i].hitS.setVolume(volume);
			ghosts[i].deathS.setVolume(volume);
		}

	}
	if (pauseScene->text[PauseScene::TextName::VOLUME].getString() == "Music")
	{
		int volume = pauseScene->slider[0].getValue(Mouse::Left, window);

		for (int i = 0; i < 9; i++)
		{
			soundtracksS[i].setVolume(volume);
		}
	}

	pauseScene->draw(window);
}

void SceneManager::custumizeUpdate(RenderWindow& window)
{
	pacman->sprite.setScale(3, 3);
	pacman->Update();
	pacman->animator.direction = 1;

	if (timer.getElapsedTime() > milliseconds(buttonTimer) && custumizeScene->button[CustumizeScene::ButtonName::BACK].isPressed(Mouse::Left, window))
	{
		timer.restart();
		menu = MAINMENU;
		pacman->sprite.setScale(0.5, 0.5);
		saveColor(pacman->sprite.getColor());
	}

	pacman->sprite.setColor(Color(custumizeScene->slider[CustumizeScene::SliderName::RED].getValue(Mouse::Left, window),
		custumizeScene->slider[CustumizeScene::SliderName::GREEN].getValue(Mouse::Left, window),
		custumizeScene->slider[CustumizeScene::SliderName::BLUE].getValue(Mouse::Left, window)));

	custumizeScene->Update();

	custumizeScene->draw(window);
	pacman->draw(window);
}

void SceneManager::redactUpdate(RenderWindow& window)
{

}
void SceneManager::redactPauseUpdate(RenderWindow& window)
{

}

void SceneManager::saveColor(Color color)
{
	ofstream toSave("saves/Color.txt");

	if (toSave.is_open())
	{
		toSave << (int)color.r << " " << (int)color.g << " " << (int)color.b;
	}

	toSave.close();
}

void SceneManager::reviving()
{
	for (int i = 0; i < 4; i++)
	{
		if (ghosts[i].getState() == Ghost::DEAD && revivingTimer[i].getElapsedTime() > seconds(4))
		{
			ghosts[i].setState(Ghost::ALIVE);
			ghosts[i].reloadTexture();
		}
	}
}

bool SceneManager::fruitKiller()
{
	for (int i = 0; i < 4; i++)
	{
		if (ghosts[i].getState() == Ghost::ALIVE && pacman->sprite.getGlobalBounds().intersects(ghosts[i].sprite.getGlobalBounds()))
		{
			ghosts[i].deathS.play();
			ghosts[i].sprite.setTexture(ghosts[i].death);
			ghosts[i].setState(Ghost::DEAD);
			revivingTimer[i].restart();
			playScene->bonusScore += 20;

			return true;
		}
	}

	
	if (animationTimer.getElapsedTime() > seconds(0.30))
	{
		animationTimer.restart();

		for (int i = 0; i < 4; i++)
		{
			if (ghosts[i].getState() == Ghost::ALIVE)
			{
				if (ghosts[i].sprite.getColor() == Color::Blue)
				{
					ghosts[i].sprite.setColor(ghostsColor[i]);
				}
				else
				{
					ghosts[i].sprite.setColor(Color::Blue);
				}
			}
		}
	}

	return false;
}

void SceneManager::saveHighscore(int value)
{
	ofstream saveHighscore;

	switch (choosedLevel)
	{
	case 0:
		saveHighscore.open("saves/highscore1.txt");

		break;
	case 1:
		saveHighscore.open("saves/highscore2.txt");

		break;
	case 2:
		saveHighscore.open("saves/highscore3.txt");

		break;
	case 3:
		saveHighscore.open("saves/highscore4.txt");

		break;
	case 4:
		saveHighscore.open("saves/highscore5.txt");

		break;
	case 5:
		saveHighscore.open("saves/highscore6.txt");

		break;
	case 6:
		saveHighscore.open("saves/highscore7.txt");

		break;
	case 7:
		saveHighscore.open("saves/highscore8.txt");

		break;
	}

	if(saveHighscore.is_open())
		saveHighscore << value;

	saveHighscore.close();
}

bool SceneManager::deathDetector()
{
	if(invulnerableTimer.getElapsedTime() > seconds(1))
	{
		for (int i = 0; i < 4; i++)
		{
			if (ghosts[i].getState() != Ghost::DEAD && pacman->sprite.getGlobalBounds().intersects(ghosts[i].sprite.getGlobalBounds()))
			{
				if (difficulty != EASY)
				{
					playScene->setHealth(playScene->getHealth() - 1);
				}

				ghosts[i].hitS.play();
				playScene->bonusScore -= 20;
			}
		}

		invulnerableTimer.restart();
	}

	if (playScene->getHealth() == 0 && difficulty != EASY)
	{
		return true;
	}

	return false;
}

void SceneManager::swithDifficulties()
{
	switch (difficulty)
	{
	case EASY:
		difficulty = setDifficulty(NORMAL);
		menuScene->text[MainMenuScene::TextName::DIFFICULTY].setString("Difficulty: Normal");

		break;
	case NORMAL:
		difficulty = setDifficulty(HARD);
		menuScene->text[MainMenuScene::TextName::DIFFICULTY].setString("Difficulty: Hard");

		break;
	case HARD:
		difficulty = setDifficulty(EASY);
		menuScene->text[MainMenuScene::TextName::DIFFICULTY].setString("Difficulty: Easy");

		break;
	}
}

int SceneManager::setDifficulty(DifficultyNames difficulty)
{
	switch (difficulty)
	{
	case SceneManager::EASY:
		playScene->setHealth(0);
		pacman->setScoreMultiplier(5);

		break;
	case SceneManager::NORMAL:
		playScene->setHealth(3);
		pacman->setScoreMultiplier(10);

		break;
	case SceneManager::HARD:
		playScene->setHealth(1);
		pacman->setScoreMultiplier(20);

		break;
	}

	return difficulty;
}

void SceneManager::chooseLevel(RenderWindow& window)
{
	for (int i = 0; i < menuScene->getLevelCount(); i++)
	{
		if (menuScene->icons[i].onClick(Mouse::Left, window))
		{
			for (int i = 0; i < 9; i++)
			{
				soundtracksS[i].stop();
			}

			menuScene->icons[choosedLevel].sprite.setScale(4, 4);

			choosedLevel = i;

			menuScene->icons[choosedLevel].sprite.setScale(3.5, 3.5);
			switch (choosedLevel)
			{
			case 0:
				level->load("saves/level1.txt");
				playScene->resetLevel("saves/highscore1.txt");
				soundtracksS[1].play();

				break;
			case 1:
				level->load("saves/level2.txt");
				playScene->resetLevel("saves/highscore2.txt");
				soundtracksS[2].play();

				break;
			case 2:
				level->load("saves/level3.txt");
				playScene->resetLevel("saves/highscore3.txt");
				soundtracksS[3].play();

				break;
			case 3:
				level->load("saves/level4.txt");
				playScene->resetLevel("saves/highscore4.txt");
				soundtracksS[4].play();

				break;
			case 4:
				level->load("saves/level5.txt");
				playScene->resetLevel("saves/highscore5.txt");
				soundtracksS[5].play();

				break;
			case 5:
				level->load("saves/level6.txt");
				playScene->resetLevel("saves/highscore6.txt");
				soundtracksS[6].play();

				break;
			case 6:
				level->load("saves/level7.txt");
				playScene->resetLevel("saves/highscore7.txt");
				soundtracksS[7].play();

				break;
			case 7:
				level->load("saves/level8.txt");
				playScene->resetLevel("saves/highscore8.txt");
				soundtracksS[8].play();

				break;
			}

			pacman->sprite.setPosition(*level->getEntityPostion(0));

			for (int i = 0; i < level->getEntityCount() - 1; i++)
			{
				ghosts[i].sprite.setPosition(*level->getEntityPostion(i+1));
			}

			break;
		}
	}
}