#pragma once
#include "Stage.h"
#include <d3dx9core.h>
#include <vector>

using namespace std;

class ClearStage : public Stage
{
public:
	enum StageState
	{
		kWaitingPlayerName
	};
	ClearStage();
	virtual ~ClearStage();
	void Update() override;
	void Render() override;

	vector<char> playerName;

	StageState stageState;
	float alpha;

	ID3DXFont* font;

	float btnX;
	float btnY;
	float btnW;
	float btnH;
};

