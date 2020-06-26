#pragma once
#include "Enemy.h"

class BossC : public Enemy
{
public:
	BossC();
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
	float speed;

	int hp;
};

