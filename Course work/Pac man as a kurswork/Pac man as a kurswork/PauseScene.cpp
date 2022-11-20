#include "PauseScene.h"

PauseScene::PauseScene(Level& level, string fontPath) : Scene(level, fontPath)
{
	slider.push_back(Slider(Vector2f(100,20), Vector2f(100,770), 30));

	button.push_back(Button("sprites/backbutton.png"));

	button[BACK].sprite.setPosition(Vector2f(620, 700));
	button[BACK].sprite.setTexture(button[BACK].texture);

	text.push_back(Text("Sounds", font, 15));
	text[VOLUME].setPosition(30, 770);

	shadow.setFillColor(Color(0, 0, 0, 120));
}
