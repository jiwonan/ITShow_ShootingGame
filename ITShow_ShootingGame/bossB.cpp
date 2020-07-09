#include "stdafx.h"

#include "bossB.h"

#include "global.h"
#include "game_first_stage.h"

BossB::BossB()
{
	isDead = false;
	isHit = false;

	posX = WINDOW_WIDTH / 2;
	posY = -100;

	enemyDamage = 40;

	hp = 303;
	floatingTime = 0;
	shootingTime = 0;
	speed = 200;

	type = 1;

}

void BossB::Update()
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

	shootingTime += deltaTime;

	if (shootingTime > 1)
	{
		int noshoot = rand() % 5;
		float speed = 4;
		// float deltaAngle = (i * 31 + 70)*3.141592f / 10.0f;
		for (int i = 0; i < 5; i++)
		{
			float deltaAngle = (i * 8 + 70)*3.141592f / 180.0f;
			float vx = cos(deltaAngle)*speed;
			float vy = sin(deltaAngle)*speed;
			if (noshoot != i)
				gameSystem.GenerateBossBullet(posX, posY, vx, vy, enemyDamage);
		}
		// 0.5초동안 발사.
		if (shootingTime > 1.5)
			shootingTime = 0;
	}
}

void BossB::Render()
{
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_BOSS_B_BODY_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 168;
		srcRect.bottom = 104;

		D3DXVECTOR3 pos(posX - 84, posY - 52, 0);
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
		TextureElement* newElement = textureManager.GetTexture(GAME_BOSS_HP_BG_UI);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 303;
		srcRect.bottom = 49;

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - 151, 5, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}

	// boss HP
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_BOSS_HP_UI);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = hp;
		srcRect.bottom = 49;

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - 151, 5, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}
}

bool BossB::IsDead()
{
	return isDead;
}

int BossB::GetEnemyDamage()
{
	return enemyDamage;
}

D3DXVECTOR2 BossB::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float BossB::GetRadius()
{
	return 52.0f;
}

void BossB::Hit(float damage)
{
	hp -= (damage*0.7);
	isHit = true;
	if (hp <= 0)
	{
		hp = 300;
		isDead = true;
		gameStat.score += hp;
		gameStat.hp = gameStat.fullHP;
		gameSystem.bossBullets.clear();
		gameStat.playerState = kEnd;
		if (gameStat.level <= 5)
			gameStat.exp += hp * gameStat.expGage;
	}
}

int BossB::GetType()
{
	return type;
}