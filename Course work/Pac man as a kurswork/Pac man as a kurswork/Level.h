#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>


using namespace sf;
using namespace std;

class Level
{
	const static int fieldResolutionX = 16;
	const static int fieldResolutionY = 16;
	const static int entityCount = 5;

	int scoreToWin;
	string path;

	CircleShape **scores;
	vector<Vector2f> bigScoresPositions;

	RectangleShape **rect;
	vector<Vector2f> positions;

public:
	Level();
	Level(string path);
	~Level();

	void load(string path);
	void draw(RenderWindow & window);

	int getEntityCount();
	int* getScoreToWin();

	Vector2i* getFieldResolution();

	Vector2f* getBigScorePosition(int index);
	Vector2f* getEntityPostion(int index);

	void restart();

	friend class Pac_man;
	friend class Ghost;
	friend class Scene;
	friend class LevelIcon;
};

