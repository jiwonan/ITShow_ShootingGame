#pragma once

#include <d3dx9math.h>

enum itemType
{
	kHp,
	kLevelUp,
	kResetCoolTime
};

class Item
{
public:
	Item(float x, float y);
	void Update();
	void Render();
	bool IsDead();
	void Hit();
	D3DXVECTOR2 GetPosition();
	float GetRadius();

	bool isDead;

	float posX;
	float posY;
	float velY;

	int type;

};

