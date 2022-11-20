#include "Ghost.h"

Ghost::Ghost(string path, string deathPath, Vector2f position,Color color, Level &level, State state, float movementSpeed) : SpriteRenderer(path, position)
{
	this->level = &level;
	this->state = state;
	this->movementSpeed = movementSpeed;

    death.loadFromFile(deathPath);

    sprite.setColor(color);

	direction = 0;
    choosedDirection = 0;

    deltaTime = 0;
    lastMoveTime = 0;

    deathB.loadFromFile("sounds/eatghosts.ogg");
    deathS.setBuffer(deathB);
    deathS.setVolume(30);

    hitB.loadFromFile("sounds/hit.ogg");
    hitS.setBuffer(hitB);
    hitS.setVolume(30);
}

void Ghost::Update()
{
    deltaTime = timer.restart().asSeconds();
    lastMoveTime += deltaTime;

    while (lastMoveTime > 0.01)
    {
        if(state != DEAD)
            move();

        lastMoveTime -= 0.01f;
    }

    if (randDirectionTimer.getElapsedTime() > seconds(1))
    {
        choosedDirection = rand() % 4;
        randDirectionTimer.restart();
    }
}

void Ghost::resetPosition(int index)
{
    sprite.setPosition(*level->getEntityPostion(index));
}

void Ghost::move()
{
    if (state == DEAD)
        return;

    if (sprite.getPosition().x <= 0 || sprite.getPosition().x >= level->fieldResolutionX * 50 - 50 ||
        sprite.getPosition().y <= 0 || sprite.getPosition().y >= level->fieldResolutionY * 50 - 50)
    {
        switch (direction)
        {
        case 0:
            sprite.move(0, -movementSpeed);
            break;
        case 1:
            sprite.move(0, movementSpeed);
            break;
        case 2:
            sprite.move(-movementSpeed, 0);
            break;
        case 3:
            sprite.move(movementSpeed, 0);
            break;
        }
    }
    else
    {
        int x, y;

        chooseDirection();

        switch (direction)
        {
        case 0:
            x = (int)sprite.getPosition().x / 50;
            y = (int)ceil(sprite.getPosition().y / 50) - 1;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY)
            {
                if(level->rect[x][y].getFillColor() == Color::Transparent)
                {
                    sprite.move(0, -movementSpeed);
                }
                else if(level->rect[x][y].getFillColor() == Color(52, 93, 169))
                {
                    choosedDirection = randNonColiderPosition();
                }
            }
            else if (y < 0)
            {
                sprite.move(0, -movementSpeed);
            }
                

            break;
        case 1:
            x = (int)sprite.getPosition().x / 50;
            y = (int)sprite.getPosition().y / 50 + 1;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY)
            {
                if (level->rect[x][y].getFillColor() == Color::Transparent)
                {
                    sprite.move(0, movementSpeed);
                }
                else if (level->rect[x][y].getFillColor() == Color(52, 93, 169))
                {
                    choosedDirection = randNonColiderPosition();
                }
            }
            else if (y > level->fieldResolutionY - 1)
            {
                sprite.move(0, movementSpeed);
            }

            break;
        case 2:
            x = (int)ceil(sprite.getPosition().x / 50) - 1;
            y = (int)sprite.getPosition().y / 50;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY)
            {
                if (level->rect[x][y].getFillColor() == Color::Transparent)
                {
                    sprite.move(-movementSpeed, 0);
                }
                else if (level->rect[x][y].getFillColor() == Color(52, 93, 169))
                {
                    choosedDirection = randNonColiderPosition();
                }
            }
            else if (x < 0)
            {
                sprite.move(-movementSpeed, 0);
            }

            break;
        case 3:
            x = (int)sprite.getPosition().x / 50 + 1;
            y = (int)sprite.getPosition().y / 50;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY)
            {
                if (level->rect[x][y].getFillColor() == Color::Transparent)
                {
                    sprite.move(movementSpeed, 0);
                }
                else if (level->rect[x][y].getFillColor() == Color(52, 93, 169))
                {
                    choosedDirection = randNonColiderPosition();
                }
            }
            else if (x > level->fieldResolutionX - 1)
            {
                sprite.move(movementSpeed, 0);
            }

            break;
        }
    }

        if (sprite.getPosition().x < -50)
            sprite.setPosition((*level).fieldResolutionX * 51, sprite.getPosition().y);
        if (sprite.getPosition().y < -50)
            sprite.setPosition(sprite.getPosition().x, (*level).fieldResolutionY * 51);
        if (sprite.getPosition().x > (*level).fieldResolutionX * 51)
            sprite.setPosition(-50, sprite.getPosition().y);
        if (sprite.getPosition().x > (*level).fieldResolutionY * 51)
            sprite.setPosition(sprite.getPosition().x, -50);
}

void Ghost::chooseDirection()
{
    int x, y;

    if ((int)sprite.getPosition().x % 50 == 0 && (int)sprite.getPosition().y % 50 == 0)
    {
        switch (choosedDirection)
        {
        case 0:
            x = (int)sprite.getPosition().x / 50;
            y = (int)sprite.getPosition().y / 50 - 1;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY &&
                level->rect[x][y].getFillColor() == Color::Transparent)
            {
                direction = choosedDirection;
            }
            else if (y < 0)
            {
                direction = choosedDirection;
            }

            break;
        case 1:
            x = (int)sprite.getPosition().x / 50;
            y = (int)sprite.getPosition().y / 50 + 1;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY &&
                level->rect[x][y].getFillColor() == Color::Transparent)
            {
                direction = choosedDirection;
            }
            else if (y > level->fieldResolutionY - 1)
            {
                direction = choosedDirection;
            }

            break;
        case 2:
            x = (int)sprite.getPosition().x / 50 - 1;
            y = (int)sprite.getPosition().y / 50;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY &&
                level->rect[x][y].getFillColor() == Color::Transparent)
            {
                direction = choosedDirection;
            }
            else if (x < 0)
            {
                direction = choosedDirection;
            }

            break;
        case 3:
            x = (int)sprite.getPosition().x / 50 + 1;
            y = (int)sprite.getPosition().y / 50;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY &&
                level->rect[x][y].getFillColor() == Color::Transparent)
            {
                direction = choosedDirection;
            }
            else if (x > level->fieldResolutionX - 1)
            {
                direction = choosedDirection;
            }

            break;
        }
    }
}

int Ghost::randNonColiderPosition()
{
    int direction = this->direction;

    while(!isNextCellFree(direction))
    {
        direction = rand() % 4;
    }

    return direction;
}

bool Ghost::isNextCellFree(int direction)
{
    int x, y;

    switch (direction)
    {
    case 0:
        x = (int)sprite.getPosition().x / 50;
        y = (int)ceil(sprite.getPosition().y / 50) - 1;

        if (x >= 0 && x < level->fieldResolutionX &&
            y >= 0 && y < level->fieldResolutionY)
        {
            if (level->rect[x][y].getFillColor() == Color::Transparent)
                return true;
        }

        break;
    case 1:
        x = (int)sprite.getPosition().x / 50;
        y = (int)sprite.getPosition().y / 50 + 1;

        if (x >= 0 && x < level->fieldResolutionX &&
            y >= 0 && y < level->fieldResolutionY)
        {
            if (level->rect[x][y].getFillColor() == Color::Transparent)
                return true;
        }

        break;
    case 2:
        x = (int)ceil(sprite.getPosition().x / 50) - 1;
        y = (int)sprite.getPosition().y / 50;

        if (x >= 0 && x < level->fieldResolutionX &&
            y >= 0 && y < level->fieldResolutionY)
        {
            if (level->rect[x][y].getFillColor() == Color::Transparent)
                return true;
        }

        break;
    case 3:
        x = (int)sprite.getPosition().x / 50 + 1;
        y = (int)sprite.getPosition().y / 50;

        if (x >= 0 && x < level->fieldResolutionX &&
            y >= 0 && y < level->fieldResolutionY)
        {
            if (level->rect[x][y].getFillColor() == Color::Transparent)
                return true;
        }

        break;
    }

    return false;
}

bool Ghost::colides(FloatRect colider)
{
	if (sprite.getGlobalBounds().intersects(colider))
		return true;

	return false;
}

void Ghost::setLevel(Level &level)
{
	this->level = &level;
}

int Ghost::getState()
{
	return state;
}

void Ghost::setState(State state)
{
	this->state = state;
}

float Ghost::getMovementSpeed()
{
	return movementSpeed;
}

void Ghost::setMovementSpeed(float movementSpeed)
{
	this->movementSpeed = movementSpeed;
}