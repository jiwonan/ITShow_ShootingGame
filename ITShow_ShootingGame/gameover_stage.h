#pragma once
#include "Stage.h"

#include <d3dx9core.h>
#include <vector>

using namespace std;

class GameoverStage : public Stage
{
public:
	enum StageState
	{
		kWaitingPlayerName
	};
	GameoverStage();
	~GameoverStage();
	void Update();
	void Render();

	vector<char> playerName;

	StageState stageState;
	float alpha;

	ID3DXFont* font;

	float btnX;
	float btnY;
	float btnW;
	float btnH;
};

