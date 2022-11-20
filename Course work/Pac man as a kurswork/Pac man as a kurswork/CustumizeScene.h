#pragma once

#include "Scene.h"
#include "Pac_man.h"

class CustumizeScene : public Scene
{
	Pac_man* pacman;

public:
	enum SliderName
	{
		RED,
		GREEN,
		BLUE
	};

	enum ButtonName
	{
		BACK
	};

	CustumizeScene(Pac_man& pacman, Level& level, string fontPath);

	void Update();
};