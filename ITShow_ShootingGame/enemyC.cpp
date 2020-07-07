#include "stdafx.h"

#include "enemyC.h"
#include "global.h"

EnemyC::EnemyC()
{
	int centerX = WINDOW_WIDTH / 2;
	int rangeX = 400;
	float tempX = (rand() % rangeX) - (rangeX / 2);
	posX = centerX + tempX;
	posY = -50;
	velX = 0;
	velY = 100;

	floatingTime = 0;
	enemyDamage = 30;

	hp = 20;
	isDead = false;
	isHit = false;
}

void EnemyC::Update()
{

	if (posX<0 || posX>WINDOW_WIDTH ||
		posY>WINDOW_HEIGHT)
	{
		isDead = true;
	}
	floatingTime += deltaTime;

	int range = rand() % 50 + 150;

	posX = (WINDOW_WIDTH / 2) + sinf(floatingTime * 2) * 200;

	if (posX > (WINDOW_WIDTH / 2) + sinf(floatingTime * 2) * 200)
	{
		posX = (WINDOW_WIDTH / 2) + sinf(floatingTime * 2) * 200;
		floatingTime = 0;
	}
	posY += velY * deltaTime;
}

void EnemyC::Render()
{
	TextureElement* newElement = textureManager.GetTexture(GAME_ENEMY_C_BODY_IMAGE);

	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 64;
	srcRect.bottom = 36;

	D3DXVECTOR3 pos(posX - 32, posY - 18, 0);
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

bool EnemyC::IsDead()
{
	return isDead;
}

int EnemyC::GetEnemyDamage()
{
	return enemyDamage;
}

D3DXVECTOR2 EnemyC::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float EnemyC::GetRadius()
{
	return 18.0f;
}

void EnemyC::Hit(float damage)
{
	hp -= damage;
	isHit = true;
	if (hp <= 0)
	{
		gameStat.score += 100;
		if (gameStat.level <= 5)
			gameStat.exp += 35 * gameStat.expGage;
		isDead = true;
		hp = 0;
		
		if (rand() % 100 < 30)
			gameSystem.GenerateItem(posX, posY);
		gameSystem.GenerateEnemyExplosionA(posX, posY);

	}
}
