#pragma once

#include "Bullet.h"

class PlayerBullet : public Bullet
{
public:
	PlayerBullet(float x, float y, float vx, float vy);
	void Update();
	void Render();
	bool IsDead();
	int GetDamage();
	D3DXVECTOR2 GetPosition();
	float GetRadius();
	void Hit();

	float posX;
	float posY;
	float velX;
	float velY;

	bool isDead;
};

