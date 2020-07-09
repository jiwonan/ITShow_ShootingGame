#pragma once
#include <d3dx9math.h>

class Skill
{
public:
	Skill();
	void Update(float x, float y);
	void Render();
	D3DXVECTOR2 GetPosition();
	float GetRadius();

	bool ShieldOn;
	
	float ShieldTime;
	float ShieldCoolTime;

	float BombCoolTime;

	float posX;
	float posY;
	
};

