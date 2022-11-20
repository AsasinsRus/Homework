#pragma once

#include <iostream>
#include "Pac_man.h"
#include "Ghost.h"
#include "PlayScene.h"
#include "PauseScene.h"
#include "MainMenuScene.h"
#include "CustumizeScene.h"

class SceneManager
{
    enum DifficultyNames
    {
        EASY,
        NORMAL,
        HARD
    };

    enum MenuNames
    {
        MAINMENU,
        GAME,
        PAUSE,
        REDACT,
        REDACTPAUSE,
        CUSTOMIZE
    };

    const static int buttonTimer = 200;

    int menu;
    int choosedLevel;
    int volumeSounds;
    int volumeMusic;
    int difficulty;

    float deltaTime;
    float lastMoveTime;

    Level* level;
    Pac_man* pacman;
    Ghost* ghosts;

    SoundBuffer soundtracksB[9];
    Sound soundtracksS[9];

    PlayScene* playScene;
    PauseScene* pauseScene;
    MainMenuScene* menuScene;
    CustumizeScene* custumizeScene;

    Clock timer;
    Clock invulnerableTimer;
    Clock alertTimer;
    Clock murdaryTimer;
    Clock animationTimer;
    Clock revivingTimer[4];

    Color ghostsColor[4];

    void chooseLevel(RenderWindow& window);
    void swithDifficulties();
    bool deathDetector();
    void saveHighscore(int value);
    bool fruitKiller();
    void reviving();
    void saveColor(Color color);

    void mainMenuUpdate(RenderWindow& window);
    void gameUpdate(RenderWindow& window);
    void pauseUpdate(RenderWindow& window);
    void custumizeUpdate(RenderWindow& window);
    void redactUpdate(RenderWindow& window);
    void redactPauseUpdate(RenderWindow& window);

public:
    SceneManager(Level &level, Pac_man &pacman, Ghost *ghosts, MainMenuScene& menuScene, PlayScene& playScene, PauseScene& pauseScene, CustumizeScene& custumizeScene);

    void updateAndDraw(RenderWindow& window);
    int setDifficulty(DifficultyNames difficulty);
};

