#include "stdafx.h"

#include "enemyB.h"
#include "global.h"

EnemyB::EnemyB()
{
	int centerX = WINDOW_WIDTH / 2;
	int rangeX = 400;
	float tempX = (rand() % rangeX) - (rangeX / 2);
	posX = centerX + tempX;
	posY = -50;
	velX = 0;
	velY = 0;

	enemyDamage = 20;

	hp = 6;
	isDead = false;
	isHit = false;

	type = 2;

}

void EnemyB::Update()
{
	if (posX<0 || posX>WINDOW_WIDTH ||
		posY>WINDOW_HEIGHT)
	{
		isDead = true;
	}
	posY += 200 * deltaTime;
}

void EnemyB::Render()
{
	TextureElement* newElement = textureManager.GetTexture(GAME_ENEMY_B_BODY_IMAGE);

	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 32;
	srcRect.bottom = 32;

	D3DXVECTOR3 pos(posX - 16, posY - 16, 0);
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

bool EnemyB::IsDead()
{
	return isDead;
}

int EnemyB::GetEnemyDamage()
{
	return enemyDamage;
}

D3DXVECTOR2 EnemyB::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float EnemyB::GetRadius()
{
	return 16.0f;
}

void EnemyB::Hit(float damage)
{
	hp -= damage;
	isHit = true;
	if (hp <= 0)
	{
		gameStat.score += 20;
		if (gameStat.level <= 5)
			gameStat.exp += 25 * gameStat.expGage;
		isDead = true;
		hp = 0;
		
		if (rand() % 100 < 20)
			gameSystem.GenerateItem(posX, posY);

		gameSystem.GenerateEnemyExplosionA(posX, posY);
	}
}

int EnemyB::GetType()
{
	return type;
}