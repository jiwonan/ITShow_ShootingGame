#pragma once
#include "Enemy.h"

class EnemyB : public Enemy
{
public:
	EnemyB();
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

	int enemyDamage;
};

