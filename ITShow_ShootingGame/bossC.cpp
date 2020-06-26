#include "stdafx.h"
#include "bossC.h"

#include "global.h"
#include "game_second_stage.h"

BossC::BossC()
{
	isDead = false;
	isHit = false;

	posX = WINDOW_WIDTH / 2;
	posY = -100;

	enemyDamage = 45;

	hp = 500;
	floatingTime = 0;
	speed = 200;
}

void BossC::Update()
{
	if (posY < 100)
	{
		posY += deltaTime * speed;
	}
	else {
		floatingTime += deltaTime;

		posX = (WINDOW_WIDTH / 2) + sinf(floatingTime * 1.2) * speed;

		if (posX > (WINDOW_WIDTH / 2) + sinf(floatingTime * 1.2) * speed)
		{
			posX = (WINDOW_WIDTH / 2) + sinf(floatingTime * 1.2) * speed;
			floatingTime = 0;
		}
	}

	if (rand() % 100 < 10)
	{

		float vx = rand() % 20 - 10;
		float vy = rand() % 20 - 10;
		float d = sqrt(vx * vx + vy * vy);

		vx = vx / d;
		vy = vy / d;

		float speed = 2;

		gameSystem.GenerateBossBullet(posX, posY, vx*speed, vy*speed, enemyDamage);
	}
}

void BossC::Render()
{
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_STAGE_2_MID_BOSS_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 134;
		srcRect.bottom = 170;

		D3DXVECTOR3 pos(posX - 67, posY - 85, 0);
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
		srcRect.right = 500;
		srcRect.bottom = 19;

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - 250, 10, 0);
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

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - 250, 10, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}
}

bool BossC::IsDead()
{
	return isDead;
}

int BossC::GetEnemyDamage()
{
	return enemyDamage;
}

D3DXVECTOR2 BossC::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float BossC::GetRadius()
{
	return 67.0f;
}

void BossC::Hit(float damage)
{
	hp -= (damage*0.5);
	isHit = true;
	if (hp <= 0)
	{
		hp = 500;
		isDead = true;
		gameStat.score += hp;
		gameStat.hp = gameStat.fullHP;
		gameSystem.bossBullets.clear();
		gameStat.playerState = kSecond;
		if (gameStat.level <= 5)
			gameStat.exp += hp;
	}
}


