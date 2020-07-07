#pragma once

#include <winnt.h>
#include "Stage.h"

class TimerStage : public Stage
{
public:
	TimerStage();

	void Update();
	void Render();

	float top;
	float bottom;

	bool isOpen;

	WCHAR buffer[128];
	float Timer;
};

