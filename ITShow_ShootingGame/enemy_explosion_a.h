#pragma once

#include "sprite_effect.h"
#include "anim_frame.h"
#include <vector>
#include <windows.h>

using namespace std;

class EnemyExplosionA : public SpriteEffect
{
public:
	EnemyExplosionA(float x, float y);
	void Update();
	void Render();
	bool IsDead();

	vector<AnimFrame> frames;

	RECT GetSourceRect();

	float posX;
	float posY;
	bool isDead;

	int frameIndex;
	float animTime;
};

