#include "stdafx.h"

#include "enemyA.h"
#include "global.h"


EnemyA::EnemyA()
{
	int centerX = WINDOW_WIDTH / 2;
	int rangeX = 400;
	float tempX = (rand() % rangeX) - (rangeX / 2);
	posX = centerX + tempX;
	posY = -50;
	velX = 0;
	velY = 0;

	enemyDamage = 10;

	hp = 5;
	isDead = false;
	isHit = false;
	enemyState = kMoveToDirection;
}

void EnemyA::Update()
{
	if (posX<0 || posX>WINDOW_WIDTH ||
		posY>WINDOW_HEIGHT)
	{
		isDead = true;
	}

	switch (enemyState)
	{
	case kMoveToDirection:
		{
			MoveToDirection();
			break;
		}
	case kChooseDirection:
		{
			ChooseDirection();
			break;
		}
	case kMoveToEnd:
		{
			MoveToEnd();
			break;
		}
	default:
		break;
	}
	posX += velX;
	posY += velY;
	// posY += 100 * deltaTime;
}

void EnemyA::Render()
{
	TextureElement* newElement = textureManager.GetTexture(GAME_ENEMY_A_BODY_IMAGE);

	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 40;
	srcRect.bottom = 70;

	D3DXVECTOR3 pos(posX - 20, posY - 35, 0);
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

bool EnemyA::IsDead()
{
	return isDead;
}

int EnemyA::GetEnemyDamage()
{
	return enemyDamage;
}

D3DXVECTOR2 EnemyA::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float EnemyA::GetRadius()
{
	return 20.0f;
}

void EnemyA::Hit(float damage)
{
	hp -= damage;
	isHit = true;
	if (hp <= 0)
	{
		gameStat.score += 100;
		if (gameStat.level <= 5)
			gameStat.exp += 5 * gameStat.expGage;
		isDead = true;
		hp = 0;

		if (rand() % 100 < 40)
			gameSystem.GenerateItem(posX, posY);

		gameSystem.GenerateEnemyExplosionA(posX, posY);
	}
}

void EnemyA::MoveToDirection()
{
	velY += deltaTime * 100;
	if (posY > 150)
	{
		enemyState = kChooseDirection;
	}
}

void EnemyA::ChooseDirection()
{
	const int randValue = rand() % 100;
	if (randValue > 50)
	{
		velX += -(20 + rand() % 50);
	}
	else
	{
		velX += (20 + rand() % 50);
	}
	enemyState = kMoveToEnd;
}

void EnemyA::MoveToEnd()
{

}
