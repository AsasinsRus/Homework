#pragma once

#include "Scene.h"
#include "LevelIcon.h"

class MainMenuScene : public Scene
{
	const static int levelCount = 8;

public:
	LevelIcon icons[levelCount];

	enum ButtonName
	{
		START,
		//REDACT,
		QUIT,
		CUSTOMIZE
	};

	enum TextName
	{
		SOUNDS,
		DIFFICULTY
	};

	MainMenuScene(Level& level, string path);

	int getLevelCount();

	void draw(RenderWindow& window);
};

