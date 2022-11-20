#include "Level.h"

Level::Level()
{
    rect = new RectangleShape * [fieldResolutionX];
    for (int i = 0; i < fieldResolutionX; i++)
    {
        rect[i] = new RectangleShape[fieldResolutionY];
    }

    scores = new CircleShape * [fieldResolutionX];
    for (int i = 0; i < fieldResolutionX; i++)
    {
        scores[i] = new CircleShape[fieldResolutionY];
    }

    for (int i = 0; i < fieldResolutionX; i++)
    {
        for (int j = 0; j < fieldResolutionY; j++)
        {
            rect[i][j] = RectangleShape(Vector2f(50, 50));
            rect[i][j].setPosition(i * 50, j * 50);
            rect[i][j].setFillColor(Color(52, 93, 169));
            scores[i][j] = CircleShape(11);
            scores[i][j].setPosition(15 + i * 50, 15 + j * 50);
        }
    }
}

Level::Level(string path)
{
    rect = new RectangleShape * [fieldResolutionX];
    for (int i = 0; i < fieldResolutionX; i++)
    {
        rect[i] = new RectangleShape[fieldResolutionY];
    }

    scores = new CircleShape * [fieldResolutionX];
    for (int i = 0; i < fieldResolutionX; i++)
    {
        scores[i] = new CircleShape[fieldResolutionY];
    }

    ifstream save(path);
    float saveBuffer[fieldResolutionX][fieldResolutionY];
    this->path = path;

    scoreToWin = 0;


    if (save.is_open())
    {
        for (int i = 0; i < fieldResolutionX; i++)
        {
            for (int j = 0; j < fieldResolutionY; j++)
            {
                save >> saveBuffer[i][j];
            }
        }

        for (int i = 0; i < entityCount; i++)
        {
            float bufferX, bufferY;

            save >> bufferX;
            save >> bufferY;

            positions.push_back(Vector2f(bufferX, bufferY));
        }

        for (int i = 0; i < fieldResolutionX; i++)
        {
            for (int j = 0; j < fieldResolutionY; j++)
            {
                rect[i][j] = RectangleShape(Vector2f(50, 50));
                rect[i][j].setPosition(i * 50, j * 50);
                rect[i][j].setFillColor(Color(52, 93, 169));
                scores[i][j] = CircleShape(11);
                scores[i][j].setPosition(15 + i * 50, 15 + j * 50);
            }
        }

        for (int i = 0; i < fieldResolutionX; i++)
        {
            for (int j = 0; j < fieldResolutionY; j++)
            {
                if (saveBuffer[i][j] == 1)
                {
                    rect[i][j].setFillColor(Color(52, 93, 169));
                }
                else if (saveBuffer[i][j] == 0)
                {
                    rect[i][j].setFillColor(Color(0, 0, 0, 0));
                    scoreToWin++;
                }
                else if (saveBuffer[i][j] == 2)
                {
                    rect[i][j].setFillColor(Color(0, 0, 0, 0));

                    scores[i][j].setPosition(scores[i][j].getPosition().x - 3, scores[i][j].getPosition().y - 3);
                    scores[i][j].setFillColor(Color::Yellow);
                    scores[i][j].setRadius(14);
                    scoreToWin++;

                    bigScoresPositions.push_back(Vector2f(i, j));
                }
            }
        }
    }
    save.close();
    
}

Level::~Level()
{
    for (int i = 0; i < fieldResolutionX; i++)
    {
        delete[] rect[i];
        delete[] scores[i];
    }

    delete[] rect;
    delete[] scores;
}

void Level::load(string path)
{
    ifstream save(path);
    float saveBuffer[fieldResolutionX][fieldResolutionY];
    this->path = path;

    positions.clear();
    bigScoresPositions.clear();
    scoreToWin = 0;

    if (save.is_open())
    {
        for (int i = 0; i < fieldResolutionX; i++)
        {
            for (int j = 0; j < fieldResolutionY; j++)
            {
                save >> saveBuffer[i][j];
            }
        }

        for (int i = 0; i < entityCount; i++)
        {
            float bufferX, bufferY;

            save >> bufferX;
            save >> bufferY;

            positions.push_back(Vector2f(bufferX, bufferY));
        }

        for (int i = 0; i < fieldResolutionX; i++)
        {
            for (int j = 0; j < fieldResolutionY; j++)
            {
                scores[i][j].setRadius(11);
                scores[i][j].setFillColor(Color::White);
                scores[i][j].setPosition(15 + i * 50, 15 + j * 50);
            }
        }

        for (int i = 0; i < fieldResolutionX; i++)
        {
            for (int j = 0; j < fieldResolutionY; j++)
            {
                if (saveBuffer[i][j] == 1)
                {
                    rect[i][j].setFillColor(Color(52, 93, 169));
                }
                else if (saveBuffer[i][j] == 0)
                {
                    rect[i][j].setFillColor(Color(0, 0, 0, 0));
                    scoreToWin++;
                }
                else if (saveBuffer[i][j] == 2)
                {
                    rect[i][j].setFillColor(Color(0, 0, 0, 0));

                    scores[i][j].setFillColor(Color::Yellow);
                    scores[i][j].setPosition(scores[i][j].getPosition().x - 3, scores[i][j].getPosition().y - 3);
                    scores[i][j].setRadius(15);
                    scoreToWin++;

                    bigScoresPositions.push_back(Vector2f(i, j));
                }
            }
        }
    }
    save.close();

}

void Level::draw(RenderWindow &window)
{
    for (int i = 0; i < fieldResolutionX; i++)
    {
        for (int j = 0; j < fieldResolutionY; j++)
        {
            if (scores[i][j].getPosition().x > 0 && scores[i][j].getPosition().x < window.getSize().x &&
                scores[i][j].getPosition().y > 0 && scores[i][j].getPosition().x < window.getSize().y &&
                scores[i][j].getRadius() > 10)
                window.draw(scores[i][j]);

            if(rect[i][j].getFillColor() != Color::Transparent)
                window.draw(rect[i][j]);
        }
    }
}

int Level::getEntityCount()
{
    return entityCount;
}

int* Level::getScoreToWin()
{
    return &scoreToWin;
}

Vector2i* Level::getFieldResolution()
{
    Vector2i* fieldResolution = new Vector2i(fieldResolutionX, fieldResolutionY);

    return fieldResolution;
}

Vector2f* Level::getBigScorePosition(int index)
{
    if (index < bigScoresPositions.size())
        return &bigScoresPositions[index];

    return nullptr;
}

Vector2f* Level::getEntityPostion(int index)
{
    if (index < positions.size())
        return &positions[index];

    return nullptr;
}

void Level::restart()
{
    ifstream save(path);
    float saveBuffer[fieldResolutionX][fieldResolutionY];

    positions.clear();
    bigScoresPositions.clear();
    scoreToWin = 0;

    if (save.is_open())
    {
        for (int i = 0; i < fieldResolutionX; i++)
        {
            for (int j = 0; j < fieldResolutionY; j++)
            {
                save >> saveBuffer[i][j];
            }
        }

        for (int i = 0; i < entityCount; i++)
        {
            float bufferX, bufferY;

            save >> bufferX;
            save >> bufferY;

            positions.push_back(Vector2f(bufferX, bufferY));
        }

        for (int i = 0; i < fieldResolutionX; i++)
        {
            for (int j = 0; j < fieldResolutionY; j++)
            {
                scores[i][j].setRadius(11);
                scores[i][j].setFillColor(Color::White);
                scores[i][j].setPosition(15 + i * 50, 15 + j * 50);
            }
        }

        for (int i = 0; i < fieldResolutionX; i++)
        {
            for (int j = 0; j < fieldResolutionY; j++)
            {
                if (saveBuffer[i][j] == 1)
                {
                    rect[i][j].setFillColor(Color(52, 93, 169));
                }
                else if (saveBuffer[i][j] == 0)
                {
                    rect[i][j].setFillColor(Color(0, 0, 0, 0));
                    scoreToWin++;
                }
                else if (saveBuffer[i][j] == 2)
                {
                    rect[i][j].setFillColor(Color(0, 0, 0, 0));

                    scores[i][j].setFillColor(Color::Yellow);
                    scores[i][j].setPosition(scores[i][j].getPosition().x - 3, scores[i][j].getPosition().y - 3);
                    scores[i][j].setRadius(15);

                    bigScoresPositions.push_back(Vector2f(i, j));
                }
            }
        }
    }
    save.close();
}
