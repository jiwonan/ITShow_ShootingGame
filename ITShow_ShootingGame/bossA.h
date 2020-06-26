#pragma once

#include "Enemy.h"

class BossA : public Enemy
{
public:
	BossA();
	void Update();
	void Render();
	bool IsDead();
	int GetEnemyDamage();
	D3DXVECTOR2 GetPosition();
	float GetRadius();
	void Hit(float damage);

	bool isDead;
	bool isHit;
	int enemyDamage;

	float posX;
	float posY;
	float velX;
	float velY;

	float floatingTime;
	float shootingTime;
	float speed;

	int hp;
};

