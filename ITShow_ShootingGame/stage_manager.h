#pragma once

#include "Stage.h"

class StageManager : public Stage
{
public:
	Stage* currentStage;

	void LoadTitleStage();
	void LoadGameFirstStage();
	void LoadGameSecondStage();
	void LoadGameoverStage();
	void LoadTimerStage();
	void LoadHowtoStage();
	void LoadClearStage();
	void LoadRankingStage();

	void Update();
	void Render();
};

