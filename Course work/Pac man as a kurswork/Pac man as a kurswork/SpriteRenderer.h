#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class SpriteRenderer
{
public:
	Texture texture;
	Sprite sprite;

	SpriteRenderer();
	SpriteRenderer(string path, Vector2f position = Vector2f(400, 400), Vector2f scale = Vector2f(0.5, 0.5));

	void reloadTexture();
	void loadFromFile(string path);

	void draw(RenderWindow & window);
};