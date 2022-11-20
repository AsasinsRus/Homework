#include "Button.h"

Button::Button(string path): SpriteRenderer(path){}

bool Button::isPressed(Mouse::Button button, RenderWindow& window)
{
	if(timer.getElapsedTime() > milliseconds(70))
	{
		timer.restart();

		if (sprite.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			if (sprite.getColor() != Color::Transparent && Mouse::isButtonPressed(button))
			{
				return true;
			}
		}
	}

	return false;
}