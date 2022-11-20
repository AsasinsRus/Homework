#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(string path, Vector2f position, Vector2f scale) 
{
	Image img;
	img.loadFromFile(path);

	texture.loadFromImage(img);
	sprite.setTexture(texture);

	sprite.setPosition(position);
	sprite.setScale(scale);
}

void SpriteRenderer::reloadTexture()
{
	sprite.setTexture(texture);
}

void SpriteRenderer::loadFromFile(string path)
{

	texture.loadFromFile(path);
	sprite.setTexture(texture);
}

void SpriteRenderer::draw(RenderWindow& window)
{
	if (sprite.getPosition().x > -50 && sprite.getPosition().x < window.getSize().x &&
		sprite.getPosition().y > -50 && sprite.getPosition().x < window.getSize().y &&
		sprite.getColor() != Color::Transparent)
	{
		window.draw(sprite);
	}
}