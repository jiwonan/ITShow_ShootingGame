#include "stdafx.h"

#include "stage_manager.h"
#include "global.h"

#include "title_stage.h"
#include "game_first_stage.h"
#include "game_second_stage.h"
#include "gameover_stage.h"
#include "timer_stage.h"
#include "howto_stage.h"
#include "clear_stage.h"
#include "ranking_stage.h"

void StageManager::LoadTitleStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	TitleStage* stage = new TitleStage();
	currentStage = stage;
}

void StageManager::LoadGameFirstStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	GameFirstStage* stage = new GameFirstStage();
	currentStage = stage;
}

void StageManager::LoadGameSecondStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	GameSecondStage* stage = new GameSecondStage();
	currentStage = stage;
}

void StageManager::LoadGameoverStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	GameoverStage* stage = new GameoverStage();
	currentStage = stage;
}

void StageManager::LoadTimerStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	TimerStage* stage = new TimerStage();
	currentStage = stage;
}

void StageManager::LoadHowtoStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	HowtoStage* stage = new HowtoStage();
	currentStage = stage;
}

void StageManager::LoadClearStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	ClearStage* stage = new ClearStage();
	currentStage = stage;
}

void StageManager::LoadRankingStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	RankingStage* stage = new RankingStage();
	currentStage = stage;
}

void StageManager::Update()
{
	currentStage->Update();
}

void StageManager::Render()
{

	currentStage->Render();
}
