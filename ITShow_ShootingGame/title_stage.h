#pragma once
#include "Stage.h"

class TitleStage : public Stage
{
public:
	enum TitleStageState
	{
		kTitleStage,
		kFading,
		kFadeOutDone
	};

	TitleStage();
	void Update();
	void Render();

	float btnX;
	float btnY;
	float btnW;
	float btnH;

	float btnX2;
	float btnY2;
	float btnW2;
	float btnH2;

	float RbtnX;
	float RbtnY;
	float RbtnW;
	float RbtnH;

	int sound;

	// state machine	
	TitleStageState titleStageState;
	float alpha;
};

