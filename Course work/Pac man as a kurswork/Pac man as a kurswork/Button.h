#pragma once
#include "SpriteRenderer.h"

class Button : public SpriteRenderer
{
	Clock timer;

public:
	Button(string path);

	bool isPressed(Mouse::Button button, RenderWindow& window);
};

