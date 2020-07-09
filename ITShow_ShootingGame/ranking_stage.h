#pragma once
#include "Stage.h"
#include <d3dx9core.h>


class RankingStage : public Stage
{
public:
	RankingStage();
	void Update() override;
	void Render() override;

	ID3DXFont* font;
};

