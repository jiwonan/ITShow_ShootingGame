#pragma once
#include "Enemy.h"

class EnemyC : public Enemy
{
public:
	EnemyC();
	void Update();
	void Render();
	bool IsDead();
	int GetEnemyDamage();
	D3DXVECTOR2 GetPosition();
	float GetRadius();
	void Hit(float damage);
	int GetType();

	float posX;
	float posY;
	float velX;
	float velY;

	int hp;

	bool isDead;
	bool isHit;

	float floatingTime;

	int enemyDamage;

	int type;

};

