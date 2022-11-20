#pragma once

#include "Scene.h"

class PauseScene : public Scene
{

public:
	enum ButtonName
	{
		BACK
	};

	enum TextName
	{
		VOLUME
	};

	PauseScene(Level& level, string fontPath);
};

