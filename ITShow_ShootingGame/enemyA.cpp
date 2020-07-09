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

	type = 2;

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
	return 16.0f;
}

void EnemyA::Hit(float damage)
{
	hp -= damage;
	isHit = true;
	if (hp <= 0)
	{
		gameStat.score += 10;
		if (gameStat.level <= 5)
			gameStat.exp += 5 * gameStat.expGage;
		isDead = true;
		hp = 0;

		if (rand() % 100 < 30)
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

int EnemyA::GetType()
{
	return type;
}