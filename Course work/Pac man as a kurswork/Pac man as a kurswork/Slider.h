#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Slider
{
	RectangleShape rect[2];
	int maxValue;
	int currentValue;

public:
	Slider(Vector2f size, Vector2f position, int currentValue = 0, int maxValue = 100, Color backgroundColor = Color::Black, Color frontColor = Color::White);

	int getValue(Mouse::Button button, RenderWindow& window);
	void setCurrentValue(int currentValue);

	void setMaxValue(int maxValue);
	int getMaxValue();

	void setSize(Vector2f size);
	Vector2f getSize();

	void setPosition(Vector2f position);
	Vector2f getPosition();

	void setBackgroundColor(Color backgroundColor);
	Color getBackgroundColor();

	void setFrontColor(Color frontColor);
	Color getFrontColor();

	void draw(RenderWindow& window);
};

