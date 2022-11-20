#include "Slider.h"

Slider::Slider(Vector2f size, Vector2f position, int currentValue, int maxValue, Color backgroundColor, Color frontColor)
{
	this->maxValue = maxValue;
	this->currentValue = currentValue;

	rect[0] = RectangleShape(size);
	rect[1] = RectangleShape(Vector2f(size.x / maxValue * currentValue, size.y));

	rect[0].setFillColor(backgroundColor);
	rect[1].setFillColor(frontColor);

	for (int i = 0; i < 2; i++)
	{
		rect[i].setPosition(position);
	}
}

int Slider::getValue(Mouse::Button button, RenderWindow& window)
{
	if (rect[0].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
	{
		if (rect[0].getFillColor() != Color::Transparent && Mouse::isButtonPressed(button))
		{
			rect[1].setSize(Vector2f(Mouse::getPosition(window).x - rect[1].getGlobalBounds().left, rect[1].getSize().y));
			currentValue = rect[0].getSize().x / maxValue * rect[1].getSize().x;
		}
	}

	return currentValue;
}

void Slider::setCurrentValue(int currentValue)
{
	this->currentValue = currentValue;

	rect[1].setSize(Vector2f(rect[0].getSize().x / maxValue * currentValue, rect[1].getSize().y));
}

void Slider::setMaxValue(int maxValue)
{
	this->maxValue = maxValue;
}

int Slider::getMaxValue()
{
	return maxValue;
}

void Slider::setSize(Vector2f size)
{
	for (int i = 0; i < 2; i++)
	{
		rect[i].setSize(size);
	}
}

Vector2f Slider::getSize()
{
	return rect[0].getSize();
}

void Slider::setPosition(Vector2f position)
{
	for (int i = 0; i < 2; i++)
	{
		rect[i].setPosition(position);
	}
}

Vector2f Slider::getPosition()
{
	return rect[0].getPosition();
}

void Slider::setBackgroundColor(Color backgroundColor)
{
	rect[0].setFillColor(backgroundColor);
}

Color Slider::getBackgroundColor()
{
	return rect[0].getFillColor();
}

void Slider::setFrontColor(Color frontColor)
{
	rect[1].setFillColor(frontColor);
}
Color Slider::getFrontColor()
{
	return rect[1].getFillColor();
}

void Slider::draw(RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		if (rect[i].getPosition().x > 0 && rect[i].getPosition().x < window.getSize().x &&
			rect[i].getPosition().y > 0 && rect[i].getPosition().x < window.getSize().y &&
			rect[i].getFillColor() != Color::Transparent)
		{
			window.draw(rect[i]);
		}
	}
}