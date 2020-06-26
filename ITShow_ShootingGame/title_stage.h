#pragma once
#include "Stage.h"

class TitleStage : public Stage
{
public:
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
};

