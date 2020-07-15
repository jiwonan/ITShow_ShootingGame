#include "stdafx.h"
#include "game_system.h"
#include "player_bullet.h"
#include "enemyA.h"
#include "enemyB.h"
#include "enemyC.h"
#include "enemyD.h"
#include "math_util.h"
#include "bossA.h"
#include "bossB.h"
#include "bossC.h"
#include "bossD.h"
#include "boss_bullet.h"
#include "global.h"
#include "player_bullet_g.h"
#include "item.h"
#include "enemy_explosion_a.h"

GameSystem::GameSystem()
{
	isBombOn = false;
}

void GameSystem::ClearAll()
{
	playerBullets.clear();
	enemies.clear();
	bossBullets.clear();
}

void GameSystem::GeneratePlayerBulletSpread(float x, float y)
{
	float speed = 8;
	// float deltaAngle = (i * 31 + 70)*3.141592f / 10.0f;
	for (int i = 0; i < 5; i++)
	{
		float deltaAngle = (i * 8 + 70) * 3.141592f / 180.0f;
		float vx = cos(deltaAngle) * speed;
		float vy = -sin(deltaAngle) * speed;

		PlayerBullet* newBullet = new PlayerBullet(x, y, vx, vy);
		playerBullets.push_back(newBullet);
	}
}

void GameSystem::GeneratePlayerBulletGeneral(float x, float y)
{
	float speed = 10;

	float vx = 0;
	float vy = speed;

	PlayerBulletG* newBullet = new PlayerBulletG(x, y, vx, vy);
	playerBullets.push_back(newBullet);
}

void GameSystem::GenerateEnemyA()
{
	EnemyA* newEnemyA = new EnemyA();
	enemies.push_back(newEnemyA);
}

void GameSystem::GenerateEnemyB()
{
	EnemyB* newEnemyB = new EnemyB();
	enemies.push_back(newEnemyB);
}

void GameSystem::GenerateEnemyC()
{
	EnemyC* newEnemyC = new EnemyC();
	enemies.push_back(newEnemyC);
}

void GameSystem::GenerateEnemyD()
{
	EnemyD* newEnemyD = new EnemyD();
	enemies.push_back(newEnemyD);
}


void GameSystem::GenerateBossA()
{
	BossA* newBossA = new BossA();
	enemies.push_back(newBossA);
}

void GameSystem::GenerateBossB()
{
	BossB* newBossB = new BossB();
	enemies.push_back(newBossB);
}

void GameSystem::GenerateBossC()
{
	BossC* newBossC = new BossC();
	enemies.push_back(newBossC);
}

void GameSystem::GenerateBossD()
{
	BossD* newBossD = new BossD();
	enemies.push_back(newBossD);
}

void GameSystem::GenerateItem(float x, float y)
{
	Item* newItem = new Item(x, y);
	items.push_back(newItem);
}

void GameSystem::ResetSkillCoolTime()
{
	skill.ShieldCoolTime = 0.f;
}

void GameSystem::GenerateBossBullet(float x, float y, float vx, float vy, int damage)
{
	BossBullet* newBossBullet = new BossBullet(x, y, vx, vy, damage);
	bossBullets.push_back(newBossBullet);
}

void GameSystem::GenerateEnemyExplosionA(float x, float y)
{
	EnemyExplosionA* newEffect = new EnemyExplosionA(x, y);
	effects.push_back(newEffect);
}

void GameSystem::Update()
{
	// Update playerBullets.
	for (auto iter = playerBullets.begin(); iter != playerBullets.end();)
	{
		(*iter)->Update();

		for (int i = 0; i < enemies.size(); ++i)
		{
			D3DXVECTOR2 bulletPos = (*iter)->GetPosition();
			float bulletR = (*iter)->GetRadius();

			D3DXVECTOR2 enemyPos = enemies[i]->GetPosition();
			float enemyR = enemies[i]->GetRadius();

			bool Result = IsCircleCollided(bulletPos.x, bulletPos.y, bulletR,
				enemyPos.x, enemyPos.y, enemyR);

			if (Result)
			{
				(*iter)->Hit();
				enemies[i]->Hit((*iter)->GetDamage());
			}
		}

		if ((*iter)->IsDead())
		{
			iter = playerBullets.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	// Update all Enemies.
	for (auto iter = enemies.begin(); iter != enemies.end();)
	{
		(*iter)->Update();
		// Check player body, enemy collided.
		if (!player->isInvincible)
		{
			D3DXVECTOR2 playerPos = player->GetPosition();
			float playerR = player->GetRadius();

			D3DXVECTOR2 enemyPos = (*iter)->GetPosition();
			float enemyR = (*iter)->GetRadius();

			bool Result = IsCircleCollided(playerPos.x, playerPos.y, playerR,
				enemyPos.x, enemyPos.y, enemyR);

			if (Result)
			{
				if (!skill.ShieldOn)
					player->Hit((*iter)->GetEnemyDamage());
				if ((*iter)->GetType() == 2)
					(*iter)->Hit(9999);
			}

			if (isBombOn)
			{
				if ((*iter)->GetType() == 2)
					(*iter)->Hit(9999);
			}
		}
		if ((*iter)->IsDead())
		{
			iter = enemies.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	isBombOn = false;

	// Update boss bullets.
	for (auto iter = bossBullets.begin(); iter != bossBullets.end();)
	{
		// Check bossBullet, player collided 
		if (!player->isInvincible)
		{
			D3DXVECTOR2 playerPos = player->GetPosition();
			float playerR = player->GetRadius();

			D3DXVECTOR2 bulletPos = (*iter)->GetPosition();
			float bulletR = (*iter)->GetRadius();

			bool Result = IsCircleCollided(playerPos.x, playerPos.y, playerR,
				bulletPos.x, bulletPos.y, bulletR);

			if (Result)
			{
				if (!skill.ShieldOn)
					player->Hit((*iter)->GetDamage());
				(*iter)->Hit();
			}
		}

		(*iter)->Update();
		if ((*iter)->IsDead())
		{
			iter = bossBullets.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	for (auto iter = items.begin(); iter != items.end();)
	{
		(*iter)->Update();

		// Check player body, enemy collided.
		D3DXVECTOR2 playerPos = player->GetPosition();
		float playerR = player->GetRadius();

		D3DXVECTOR2 itemPos = (*iter)->GetPosition();
		float itemR = (*iter)->GetRadius();

		bool Result = IsCircleCollided(playerPos.x, playerPos.y, playerR,
			itemPos.x, itemPos.y, itemR);

		if (Result)
		{
			player->HitByItem((*iter)->type);
			(*iter)->Hit();
		}
	
		if ((*iter)->IsDead())
		{
			iter = items.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	for (auto iter = effects.begin(); iter != effects.end();)
	{
		(*iter)->Update();
		if ((*iter)->IsDead())
		{
			iter = effects.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	skill.Update(player->GetPosition().x, player->GetPosition().y);
}

void GameSystem::Render()
{
	for (int i = 0; i < playerBullets.size(); ++i)
	{
		playerBullets[i]->Render();
	}
	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->Render();
	}
	for (int i = 0; i < bossBullets.size(); ++i)
	{
		bossBullets[i]->Render();
	}
	for (int i = 0; i < items.size(); ++i)
	{
		items[i]->Render();
	}
	for (int i = 0; i < effects.size(); ++i)
	{
		effects[i]->Render();
	}
	skill.Render();

	// level
	{
		int lv = GAME_PLAYER_LEVEL_ONE;
		switch (gameStat.level)
		{
		case 1:
			lv = GAME_PLAYER_LEVEL_ONE;
			break;
		case 2:
			lv = GAME_PLAYER_LEVEL_TWO;
			break;
		case 3:
			lv = GAME_PLAYER_LEVEL_THREE;
			break;
		case 4:
			lv = GAME_PLAYER_LEVEL_FOUR;
			break;
		case 5:
			lv = GAME_PLAYER_LEVEL_FIVE;
			break;
		}
		TextureElement* newElement = textureManager.GetTexture(lv);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 64;
		srcRect.bottom = 64;

		D3DXVECTOR3 pos(5, 5, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}
}