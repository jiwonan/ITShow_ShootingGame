#pragma once
#include "Enemy.h"

class EnemyD : public Enemy
{
public:
	EnemyD();
	void Update();
	void Render();
	bool IsDead();
	int GetEnemyDamage();
	D3DXVECTOR2 GetPosition();
	float GetRadius();
	void Hit(float damage);

	float posX;
	float posY;
	float velX;
	float velY;

	int hp;

	bool isDead;
	bool isHit;

	float shootingTime;

	int enemyDamage;
};

