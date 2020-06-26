#pragma once
#include "Stage.h"

class GameoverStage : public Stage
{
public:
	GameoverStage();
	void Update();
	void Render();

	float btnX;
	float btnY;
	float btnW;
	float btnH;
};

