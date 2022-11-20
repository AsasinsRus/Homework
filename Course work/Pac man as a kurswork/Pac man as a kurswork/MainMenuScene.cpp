#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(Level& level, string path) : Scene(level, path)
{
	for (int i = 0; i < levelCount; i++)
	{
		icons[i] = LevelIcon("sprites/icon.png", level);
	}

	icons[0].loadFromFile("saves/level1.txt");
	icons[1].loadFromFile("saves/level2.txt");
	icons[2].loadFromFile("saves/level3.txt");
	icons[3].loadFromFile("saves/level4.txt");
	icons[4].loadFromFile("saves/level5.txt");
	icons[5].loadFromFile("saves/level6.txt");
	icons[6].loadFromFile("saves/level7.txt");
	icons[7].loadFromFile("saves/level8.txt");

	for (int i = 0; i < levelCount; i++)
	{
		icons[i].sprite.setPosition(100 + i * 80, 300);
	}

	button.reserve(4);

	button.push_back(Button("sprites/playbutton.png"));
	//button.push_back(Button("sprites/redactbutton.png"));
	button.push_back(Button("sprites/quitbutton.png"));
	button.push_back(Button("sprites/customisebutton.png"));

	for (int i = 0; i < button.size(); i++)
	{
		button[i].sprite.setTexture(button[i].texture);
	}

	button[START].sprite.setPosition(120, 400);
	//button[REDACT].sprite.setPosition(120, 500);
	button[QUIT].sprite.setPosition(120, 600);
	button[CUSTOMIZE].sprite.setPosition(620, 700);

	text.push_back(Text("Sounds", font, 15));
	text.push_back(Text("Difficulty: Normal", font, 20));

	text[SOUNDS].setPosition(30, 770);
	text[DIFFICULTY].setPosition(30, 20);

	slider.push_back(Slider(Vector2f(100, 20), Vector2f(100, 770), 30));

	shadow.setFillColor(Color(0, 0, 0, 120));
}

void MainMenuScene::draw(RenderWindow& window)
{
	Scene::draw(window);

	for (int i = 0; i < levelCount; i++)
	{
		window.draw(icons[i].sprite);
	}
}

int MainMenuScene::getLevelCount()
{
	return levelCount;
}
