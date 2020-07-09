#pragma once
#include "Enemy.h"

class BossD : public Enemy
{
public:
	BossD();
	void Update();
	void Render();
	bool IsDead();
	int GetEnemyDamage();
	D3DXVECTOR2 GetPosition();
	float GetRadius();
	void Hit(float damage);
	int GetType();

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

	int type;

};