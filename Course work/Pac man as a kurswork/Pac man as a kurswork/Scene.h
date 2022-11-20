#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Level.h"
#include "Button.h"
#include "Slider.h"

using namespace sf;
using namespace std;

class Scene
{
protected:
	Level *level;

	Font font;
	RectangleShape shadow;

public:
	vector<Text> text;
	vector<Button> button;
	vector<Slider> slider;

	Scene(Level &level, string fontPath);

	void Update();

	void setLevel(Level& level);
	void setFont(string path);
	void setShadowColor(Color color);

	virtual void draw(RenderWindow& window);
};