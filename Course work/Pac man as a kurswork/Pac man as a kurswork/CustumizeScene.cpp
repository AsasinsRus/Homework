#include "CustumizeScene.h"

CustumizeScene::CustumizeScene(Pac_man& pacman, Level& level, string fontPath) : Scene(level, fontPath)
{
	this->pacman = &pacman;

	for (int i = 0; i < 3; i++)
	{
		slider.push_back(Slider(Vector2f(256, 30), Vector2f(450, 200 + i*50), 0, 256));
		text.push_back(Text("", font, 25));
		text[i].setPosition(425, 200 + i * 50);
	}

	slider[RED].setCurrentValue(pacman.sprite.getColor().r);
	text[RED].setString("R");
	text[RED].setFillColor(Color::Red);
	slider[GREEN].setCurrentValue(pacman.sprite.getColor().g);
	text[GREEN].setString("G");
	text[GREEN].setFillColor(Color::Green);
	slider[BLUE].setCurrentValue(pacman.sprite.getColor().b);
	text[BLUE].setString("B");
	text[BLUE].setFillColor(Color::Blue);

	button.push_back(Button("sprites/backbutton.png"));
	button[BACK].sprite.setPosition(Vector2f(620, 700));
	button[BACK].reloadTexture();

	shadow.setFillColor(Color(0, 0, 0, 120));
}

void CustumizeScene::Update()
{
	pacman->sprite.setPosition(100, 100);
}