#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "SceneManager.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(800, 800), "Pac man");
    window.setFramerateLimit(120);
    srand(time(NULL));
    Clock clock;

    Level level("saves/level6.txt");
    Pac_man pacman("sprites/pacmanTileset.png", "saves/Color.txt", *level.getEntityPostion(0), level);
    pacman.setScoreMultiplier(10);

    Ghost ghosts[4] = { Ghost("sprites/ghost.png","sprites/deadGhost.png", *level.getEntityPostion(1), Color(rand() % 256, rand() % 256, rand() % 256), level) ,
                        Ghost("sprites/ghost.png","sprites/deadGhost.png", *level.getEntityPostion(2), Color(rand() % 256, rand() % 256, rand() % 256), level) ,
                        Ghost("sprites/ghost.png","sprites/deadGhost.png", *level.getEntityPostion(3), Color(rand() % 256, rand() % 256, rand() % 256), level) ,
                        Ghost("sprites/ghost.png","sprites/deadGhost.png", *level.getEntityPostion(4), Color(rand() % 256, rand() % 256, rand() % 256), level) };

    PlayScene playScene(level, "font.ttf", "sprites/heart.png", "saves/highscore5.txt", pacman.getScore());
    PauseScene pauseScene(level, "font.ttf");
    MainMenuScene menuScene(level, "font.ttf");
    CustumizeScene custumizeScene(pacman, level, "font.ttf");

    SceneManager sceneManager(level, pacman, ghosts, menuScene, playScene, pauseScene, custumizeScene);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        level.draw(window);
        sceneManager.updateAndDraw(window);

        window.display();

    }
    return 0;

    
}