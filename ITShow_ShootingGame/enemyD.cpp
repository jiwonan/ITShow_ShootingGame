#include "stdafx.h"
#include "enemyD.h"
#include "global.h"

EnemyD::EnemyD()
{
	int centerX = WINDOW_WIDTH / 2;
	int rangeX = 400;
	float tempX = (rand() % rangeX) - (rangeX / 2);
	posX = centerX + tempX;
	posY = -50;
	velX = 0;
	velY = 0;

	shootingTime = 0.5;
	enemyDamage = 35;

	hp = 40;
	isDead = false;
	isHit = false;
}

void EnemyD::Update()
{
	if (posX<0 || posX>WINDOW_WIDTH ||
		posY>WINDOW_HEIGHT)
	{
		isDead = true;
	}
	posY += 200 * deltaTime;
	shootingTime += deltaTime;
	if (shootingTime > 1)
	{
		gameSystem.GenerateBossBullet(posX, posY, 0, 5, 10);
		shootingTime = 0;
	}
}

void EnemyD::Render()
{
	TextureElement* newElement = textureManager.GetTexture(GAME_ENEMY_D_BODY_IMAGE);

	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 59;
	srcRect.bottom = 64;

	D3DXVECTOR3 pos(posX - 30, posY - 32, 0);
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

bool EnemyD::IsDead()
{
	return isDead;
}

int EnemyD::GetEnemyDamage()
{
	return enemyDamage;
}

D3DXVECTOR2 EnemyD::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float EnemyD::GetRadius()
{
	return 30.0f;
}

void EnemyD::Hit(float damage)
{
	hp -= damage;
	isHit = true;
	if (hp <= 0)
	{
		gameStat.score += 100;
		if (gameStat.level <= 5)
			gameStat.exp += 40;
		isDead = true;
		hp = 0;

		if (rand() % 100 < 40)
			gameSystem.GenerateItem(posX, posY);
		gameSystem.GenerateEnemyExplosionA(posX, posY);

	}
}
