#include "stdafx.h"
#include "bossA.h"
#include "global.h"
#include "game_first_stage.h"

BossA::BossA()
{
	isDead = false;
	isHit = false;

	posX = WINDOW_WIDTH / 2;
	posY = -100;

	enemyDamage = 35;

	hp = 200;
	floatingTime = 0;
	shootingTime = 0;
	speed = 200;
}

void BossA::Update()
{
	if (posY < 100)
	{
		posY += deltaTime * speed;
	}
	else {
		floatingTime += deltaTime;

		posX = (WINDOW_WIDTH / 2) + sinf(floatingTime) * speed;

		if (posX > (WINDOW_WIDTH / 2) + sinf(floatingTime) * speed)
		{
			posX = (WINDOW_WIDTH / 2) + sinf(floatingTime) * speed;
			floatingTime = 0;
		}
	}

	shootingTime += deltaTime;

	if (rand() % 100 < 20)
	{
		if (shootingTime > 1) {
			float vx = 0;
			float vy = 300 * deltaTime;
			gameSystem.GenerateBossBullet(posX, posY, vx, vy, enemyDamage);
			if (shootingTime > 3)
			{
				shootingTime = 0;
			}
		}
	}
}

void BossA::Render()
{
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_BOSS_A_BODY_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 114;
		srcRect.bottom = 108;

		D3DXVECTOR3 pos(posX - 57, posY - 54, 0);
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
		srcRect.right = 200;
		srcRect.bottom = 19;

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - 100, 10, 0);
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

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - 100, 10, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}
}

bool BossA::IsDead()
{
	return isDead;
}

int BossA::GetEnemyDamage()
{
	return enemyDamage;
}

D3DXVECTOR2 BossA::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float BossA::GetRadius()
{
	return 57.0f;
}

void BossA::Hit(float damage)
{
	hp -= (damage*0.8);
	isHit = true;
	if (hp <= 0)
	{
		hp = 200;
		isDead = true;
		gameStat.score += hp;
		gameSystem.bossBullets.clear();
		gameStat.playerState = kSecond;
		gameStat.hp = gameStat.fullHP;
		if (gameStat.level <= 5)
			gameStat.exp += hp;
	}
}
