#pragma once

#include "Stage.h"
#include "game_background_2.h"
#include "player.h"

class GameSecondStage : public Stage
{
public:
	GameBackground2 background;
	Player player;

	GameSecondStage();
	void Update();
	void Render();

	float enemyTime;

	int per;
};

