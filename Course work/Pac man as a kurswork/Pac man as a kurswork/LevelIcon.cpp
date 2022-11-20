#include "LevelIcon.h"

LevelIcon::LevelIcon()
{
    level = nullptr;
}

LevelIcon::LevelIcon(string path, Level& level)
{
	this->level = &level;
    image.loadFromFile(path);

	for (int i = 0; i < level.fieldResolutionX; i++)
	{
		for (int j = 0; j < level.fieldResolutionY; j++)
		{
			image.setPixel(i,j,level.rect[i][j].getFillColor());
		}
	}

    texture.loadFromImage(image);
	sprite.setTexture(texture);
    sprite.setScale(Vector2f(4, 4));
}

void LevelIcon::Update()
{
	for (int i = 0; i < level->fieldResolutionX; i++)
	{
		for (int j = 0; j < level->fieldResolutionY; j++)
		{
			image.setPixel(i, j, level->rect[i][j].getFillColor());
		}
	}

    texture.loadFromImage(image);
	sprite.setTexture(texture);
}

void LevelIcon::loadFromFile(string path)
{
    ifstream save(path);
    float saveBuffer[sizeX][sizeY];

    if (save.is_open())
    {
        for (int i = 0; i < sizeX; i++)
        {
            for (int j = 0; j < sizeY; j++)
            {
                save >> saveBuffer[i][j];
            }
        }

        for (int i = 0; i < sizeX; i++)
        {
            for (int j = 0; j < sizeY; j++)
            {
                if (saveBuffer[i][j] == 1)
                {
                    image.setPixel(i,j,Color(52, 93, 169));
                }
                else
                {
                    image.setPixel(i, j, Color::Black);
                }
            }
        }
    }
    save.close();

    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

bool LevelIcon::onClick(Mouse::Button button, RenderWindow& window)
{
    if(timer.getElapsedTime() > milliseconds(onClickTimer))
    {
        timer.restart();

        if (sprite.getGlobalBounds().contains((int)Mouse::getPosition(window).x, (int)Mouse::getPosition(window).y))
        {
            if (Mouse::isButtonPressed(button))
            {
                return true;
            }
        }
    }

    return false;
}

void LevelIcon::setLevel(Level &level)
{
    this->level = &level;
}

void LevelIcon::draw(RenderWindow& window)
{
    window.draw(sprite);
}
