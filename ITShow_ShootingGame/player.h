#pragma once

#include <d3dx9math.h>

enum Weapon
{
	kSpread,
	kGeneral
};

class Player
{
public:
	Player();
	
	void Update();
	void Render();
	D3DXVECTOR2 GetPosition();
	float GetRadius();
	void Hit(float damage);
	void HitByItem(int type);

	float playerX;
	float playerY;

	float shootTime;

	int weaponType;

	bool isInvincible;
	float invincibleTimer;
};

