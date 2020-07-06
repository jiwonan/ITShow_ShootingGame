#include "stdafx.h"
#include "bossD.h"


#include "global.h"
#include "game_second_stage.h"

BossD::BossD()
{
	isDead = false;
	isHit = false;

	posX = WINDOW_WIDTH / 2;
	posY = -100;

	enemyDamage = 50;

	hp = 600;
	floatingTime = 0;
	shootingTime = 0;
	speed = 200;
}

void BossD::Update()
{
	if (posY < 100)
	{
		posY += deltaTime * speed;
	}
	else {
		floatingTime += deltaTime;

		posX = (WINDOW_WIDTH / 2) + sinf(floatingTime * 1.2) * speed;

		if (posX >(WINDOW_WIDTH / 2) + sinf(floatingTime * 1.2) * speed)
		{
			posX = (WINDOW_WIDTH / 2) + sinf(floatingTime * 1.2) * speed;
			floatingTime = 0;
		}
	}

	if (rand() % 100 < 30)
	{

		shootingTime += deltaTime;

		if (shootingTime > 1)
		{
			int noshoot = rand() % 5;
			float speed = 4;
			
			for (int i = 0; i < 33; i++)
			{
				float deltaAngle = (i * 31 + 70)*3.141592f / 10.0f;
				float vx = cos(deltaAngle)*speed;
				float vy = sin(deltaAngle)*speed;
				if (noshoot != i)
					gameSystem.GenerateBossBullet(posX, posY, vx, vy, enemyDamage);
			}
			// 0.2초동안 발사.
			if (shootingTime > 1.2)
				shootingTime = 0;
		}
	}
}

void BossD::Render()
{
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_STAGE_2_FINAL_BOSS_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 256;
		srcRect.bottom = 146;

		D3DXVECTOR3 pos(posX - 128, posY - 73, 0);
		if (isHit)
		{
			newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 0, 0));
			isHit = false;
		}
		else
		{
			newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		}
		newElement->sprite->End();
	}
	// boss HP BG
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_HP_BG_UI);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 600;
		srcRect.bottom = 19;

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - 300, 10, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}

	// boss HP
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_HP_UI);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = hp;
		srcRect.bottom = 19;

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - 300, 10, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}
}

bool BossD::IsDead()
{
	return isDead;
}

int BossD::GetEnemyDamage()
{
	return enemyDamage;
}

D3DXVECTOR2 BossD::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float BossD::GetRadius()
{
	return 73.0f;
}

void BossD::Hit(float damage)
{
	hp -= (damage*0.4);
	isHit = true;
	if (hp <= 0)
	{
		hp = 600;
		isDead = true;
		gameStat.score += hp;
		gameStat.hp = gameStat.fullHP;
		gameSystem.bossBullets.clear();
		gameStat.playerState = kEnd;
		if (gameStat.level <= 5)
			gameStat.exp += hp * gameStat.expGage;
	}
}
