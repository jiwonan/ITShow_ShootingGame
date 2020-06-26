#pragma once

#include "Bullet.h"

class BossBullet : public Bullet
{
public:
	BossBullet(float x, float y, float vx, float vy, int damage);
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

	int damage;

	bool isDead;
};

