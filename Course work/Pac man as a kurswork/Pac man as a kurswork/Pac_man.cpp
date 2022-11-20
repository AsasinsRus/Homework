#include "Pac_man.h"

bool Pac_man::scoreColider()
{
    int i = sprite.getGlobalBounds().left / 50;
    int j = sprite.getGlobalBounds().top / 50;

    if (i >= 0 && j >= 0 && i < level->fieldResolutionX && j < level->fieldResolutionY)
    {
        if (level->scores[i][j].getGlobalBounds().contains(sprite.getPosition() + Vector2f(25,25)))
        {
            (*level).scores[i][j].setPosition(-800, -880);
            score += scoreMultiplier;

            if (level->scores[i][j].getFillColor() == Color::Yellow)
            {
                fruitS.play();

                return true;
            }

            chompS.play();
        }
    }
    
    return false;
}

void Pac_man::movementAnimation()
{
    if (animator.fixedTimer.getElapsedTime() > seconds(animator.animationSpeed))
    {
        if (animator.isReversed)
        {
            animator.frame--;

            if (animator.frame <= 0)
                animator.isReversed = false;
        }
        else
        {
            animator.frame++;

            if (animator.frame >= 3)
                animator.isReversed = true;
        }
        sprite.setTextureRect(IntRect(animator.frame * 100, animator.direction * 100, 100, 100));

        animator.fixedTimer.restart();
    }
}

void Pac_man::chooseDirection()
{
    int x, y;

    if ((int)sprite.getPosition().x % 50 == 0 && (int)sprite.getPosition().y % 50 == 0)
    {
        switch (choosedDirection)
        {
        case 0:
            x = sprite.getPosition().x / 50;
            y = sprite.getPosition().y / 50 - 1;

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
            x = sprite.getPosition().x / 50;
            y = sprite.getPosition().y / 50 + 1;

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
            x = sprite.getPosition().x / 50 - 1;
            y = sprite.getPosition().y / 50;

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
            x = sprite.getPosition().x / 50 + 1;
            y = sprite.getPosition().y / 50;

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

Pac_man::Pac_man(string path, string colorPath, Vector2f position, Level &level, float movementSpeed, float animationSpeed, int health) : SpriteRenderer(path, position)
{
    ifstream loadColor(colorPath);

    if (loadColor.is_open())
    {
        int r, g, b;

        loadColor >> r >> g >> b;
        sprite.setColor(Color(r, g, b));
    }
    loadColor.close();

    this->movementSpeed = movementSpeed;
    this->animator.animationSpeed = animationSpeed;
    this->health = health;
    this->level = &level;

    chompB.loadFromFile("sounds/chomp.ogg");
    chompS.setBuffer(chompB);
    chompS.setVolume(30);

    deathB.loadFromFile("sounds/death.ogg");
    deathS.setBuffer(deathB);
    deathS.setVolume(30);

    fruitB.loadFromFile("sounds/eatfruits.ogg");
    fruitS.setBuffer(fruitB);
    fruitS.setVolume(30);

    sprite.setTextureRect(IntRect(0, 0, 100, 100));

    score = 0;
    direction = 0;
    lastMoveTime = 0;
    deltaTime = 0;
    choosedDirection = 0;
    scoreMultiplier = 1;
}

void Pac_man::Update()
{
    deltaTime = timer.restart().asSeconds();
    lastMoveTime += deltaTime;

    while (lastMoveTime > 0.01)
    {
        move();
        lastMoveTime -= 0.01;
    }
}

void Pac_man::move()
{
    if (getAxis(Keyboard::S, Keyboard::W, Keyboard::A, Keyboard::D) > -1)
        choosedDirection = getAxis(Keyboard::S, Keyboard::W, Keyboard::A, Keyboard::D);

    if (sprite.getPosition().x < 0 || sprite.getPosition().x >= level->fieldResolutionX * 50  ||
        sprite.getPosition().y < 0 || sprite.getPosition().y >= level->fieldResolutionY * 50 )
    {
        switch (direction)
        {
        case 0:
            sprite.move(0, -movementSpeed);
            animator.direction = 2;
            break;
        case 1:
            sprite.move(0, movementSpeed);
            animator.direction = 3;
            break;
        case 2:
            sprite.move(-movementSpeed, 0);
            animator.direction = 1;
            break;
        case 3:
            sprite.move(movementSpeed, 0);
            animator.direction = 0;
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
            x = sprite.getPosition().x / 50;
            y = ceil(sprite.getPosition().y / 50) - 1;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY &&
                level->rect[x][y].getFillColor() == Color::Transparent)
            {
                sprite.move(0, -movementSpeed);
            }
            else if (y < 0)
            {
                sprite.move(0, -movementSpeed);
            }

            animator.direction = 2;
            break;
        case 1:
            x = sprite.getPosition().x / 50;
            y = sprite.getPosition().y / 50 + 1;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY &&
                level->rect[x][y].getFillColor() == Color::Transparent)
            {   
                sprite.move(0, movementSpeed);
            }
            else if (y > level->fieldResolutionY - 1)
            {
                sprite.move(0, movementSpeed);
            }

            animator.direction = 3;
            break;
        case 2:
            x = ceil(sprite.getPosition().x / 50) - 1;
            y = sprite.getPosition().y / 50;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY &&
                level->rect[x][y].getFillColor() == Color::Transparent)
            {
                sprite.move(-movementSpeed, 0);
            }
            else if (x < 0)
            {
                sprite.move(-movementSpeed, 0);
            }

            animator.direction = 1;
            break;
        case 3:
            x = sprite.getPosition().x / 50 + 1;
            y = sprite.getPosition().y / 50;

            if (x >= 0 && x < level->fieldResolutionX &&
                y >= 0 && y < level->fieldResolutionY &&
                level->rect[x][y].getFillColor() == Color::Transparent)
            {
                sprite.move(movementSpeed, 0);
            }
            else if (x > level->fieldResolutionX - 1)
            {
                sprite.move(movementSpeed, 0);
            }

            animator.direction = 0;
            break;
        }
    }

    movementAnimation();

    if (sprite.getPosition().x < -50)
        sprite.setPosition((*level).fieldResolutionX * 51, sprite.getPosition().y);
    if(sprite.getPosition().y < -50)
        sprite.setPosition(sprite.getPosition().x, (*level).fieldResolutionY * 51);
    if (sprite.getPosition().x > (*level).fieldResolutionX * 51)
        sprite.setPosition(-50, sprite.getPosition().y);
    if (sprite.getPosition().y > (*level).fieldResolutionY * 51)
        sprite.setPosition(sprite.getPosition().x, -50);
}

int Pac_man::getAxis(Keyboard::Key upKey, Keyboard::Key downKey, Keyboard::Key rightKey, Keyboard::Key leftKey)
{
    if (Keyboard::isKeyPressed(downKey))
        return 0;
    else if (Keyboard::isKeyPressed(upKey))
        return 1;
    else if (Keyboard::isKeyPressed(rightKey))
        return 2;
    else if (Keyboard::isKeyPressed(leftKey))
        return 3;

    return -1;
}

void Pac_man::deathAnimation()
{

    if (animator.fixedTimer.getElapsedTime() > seconds(animator.animationSpeed * 2))
    {
        if (animator.isReversed)
        {
            if(animator.frame > 0)
            {
                animator.frame--;
            }
            else
            {
                animator.isReversed = true;
            }
        }
        else
        {
            if(animator.direction != 5)
                animator.frame++;

            if (animator.frame == 3)
            {
                animator.isReversed = true;
                animator.direction = 5;
            }
        }

        sprite.setTextureRect(IntRect(animator.frame * 100, animator.direction * 100, 100, 100));

        animator.fixedTimer.restart();
    }
    
}

void Pac_man::chooseDirection(int direction)
{
    animator.direction = direction;

    while (animator.direction != 5 && animator.frame)
    {

        if (animator.fixedTimer.getElapsedTime() > seconds(animator.animationSpeed * 2))
        {
            if (animator.isReversed)
            {
                animator.frame--;

                if (animator.frame == 0)
                    animator.isReversed = false;
            }
            else
            {
                animator.frame++;

                if (animator.frame == 3)
                    animator.isReversed = true;
            }

            sprite.setTextureRect(IntRect(animator.frame * 100, animator.direction * 100, 100, 100));

            animator.fixedTimer.restart();
        }
    }
}

int Pac_man::getHealth()
{
    return health;
}

void Pac_man::setHealth(int health)
{
    this->health = health;
}

void Pac_man::setScore(int score)
{
    this->score = score;
}

float Pac_man::getMovementSpeed()
{
    return movementSpeed;
}

void Pac_man::setMovementSpeed(float movementSpeed)
{
    this->movementSpeed = movementSpeed;
}

void Pac_man::setCurrentLevel(Level &level)
{
    this->level = &level;
}

void Pac_man::setScoreMultiplier(float multilpier)
{
    this->scoreMultiplier = multilpier;
}

int& Pac_man::getScore()
{
    return score;
}

