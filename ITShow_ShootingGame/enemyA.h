#pragma once
#include "Enemy.h"

enum enemyAState
{
	kMoveToDirection,
	kChooseDirection,
	kMoveToEnd
};

class EnemyA : public Enemy
{
public:
	EnemyA();
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

	int enemyState;

	void MoveToDirection();
	void ChooseDirection();
	void MoveToEnd();

	bool isDead;
	bool isHit;

	int Index;

	int enemyDamage;

	int type;

};

