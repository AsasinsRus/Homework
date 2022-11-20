#pragma once

class Animator
{
public:
	float animationSpeed;
	Clock fixedTimer;
	int direction;
	int frame;
	bool isReversed;
};