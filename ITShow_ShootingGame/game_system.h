#pragma once

#include <vector>

#include "Bullet.h"
#include "Enemy.h"
#include "player.h"
#include "Skill.h"

class Item;
class SpriteEffect;

using namespace std;

class GameSystem
{
public:
	Player * player;
	vector<Bullet*> playerBullets;
	vector<Enemy*> enemies;
	vector<Bullet*> bossBullets;
	vector<Item*> items;
	Skill skill;
	vector<SpriteEffect*> effects;

	GameSystem();
	void GeneratePlayerBulletSpread(float x, float y);
	void GeneratePlayerBulletGeneral(float x, float y);

	void GenerateEnemyA();
	void GenerateEnemyB();
	void GenerateEnemyC();
	void GenerateEnemyD();

	void GenerateBossA();
	void GenerateBossB();
	void GenerateBossC();
	void GenerateBossD();

	void GenerateItem(float x, float y);
	void ResetSkillCoolTime();

	void GenerateBossBullet(float x, float y, float vx, float vy, int damage);

	void GenerateEnemyExplosionA(float x, float y);

	void Update();
	void Render();

	void ClearAll();

	bool isBombOn;
};

