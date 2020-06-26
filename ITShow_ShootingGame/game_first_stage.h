#pragma once

#include "Stage.h"
#include "game_background.h"
#include "player.h"

class GameFirstStage : public Stage
{
public:
	GameBackground background;
	Player player;

	GameFirstStage();
	void Update();
	void Render();

	float enemyTime;

	int per;
};

