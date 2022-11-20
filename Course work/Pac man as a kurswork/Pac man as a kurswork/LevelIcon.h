#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"
#include <fstream>

using namespace sf;
using namespace std;

class LevelIcon
{
	const static int sizeX = 16;
	const static int sizeY = 16;
	const static int onClickTimer = 70;

	Level* level;

	Clock timer;

public:
	Image image;
	Texture texture;
	Sprite sprite;

	LevelIcon();
	LevelIcon(string path, Level & level);

	void Update();
	void loadFromFile(string path);
	
	bool onClick(Mouse::Button button, RenderWindow& window);

	void setLevel(Level& level);

	void draw(RenderWindow& window);
};

