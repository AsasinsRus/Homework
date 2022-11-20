#include "Scene.h"

Scene::Scene(Level &level,string fontPath)
{
	this->level = &level;
	shadow = RectangleShape(Vector2f(level.fieldResolutionX * 50, level.fieldResolutionY * 50));
	shadow.setFillColor(Color(0, 0, 0, 0));

	font.loadFromFile(fontPath);
}

void Scene::setLevel(Level& level)
{
	this->level = &level;
}

void Scene::setFont(string path)
{
	font.loadFromFile(path);
}

void Scene::setShadowColor(Color color)
{
	shadow.setFillColor(color);
}

void Scene::draw(RenderWindow& window)
{
	window.draw(shadow);

	for (int i = 0; i < slider.size(); i++)
	{
		slider[i].draw(window);
	}

	for (int i = 0; i < button.size(); i++)
	{
		button[i].draw(window);
	}

	for (int i = 0; i < text.size(); i++)
	{
		if (text[i].getFillColor() != Color::Transparent)
			window.draw(text[i]);
	}
}