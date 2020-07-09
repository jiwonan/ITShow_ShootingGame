#include "stdafx.h"
#include "boss_bullet.h"
#include "global.h"

BossBullet::BossBullet(float x, float y, float vx, float vy, int damage2)
{
	posX = x;
	posY = y;
	velX = vx;
	velY = vy;

	damage = damage2;

	isDead = false;
}

void BossBullet::Update()
{
	posX += velX;
	posY += velY;

	if (posX<0 || posX>WINDOW_WIDTH ||
		posY<0 || posY>WINDOW_HEIGHT)
	{
		isDead = true;
	}
}

void BossBullet::Render()
{
	TextureElement* newElement = textureManager.GetTexture(GAME_BOSS_BULLET_A_IMAGE);

	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 15;
	srcRect.bottom = 14;

	D3DXVECTOR3 pos(posX - 8, posY - 7, 0);
	newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	newElement->sprite->End();
}

bool BossBullet::IsDead()
{
	return isDead;
}

int BossBullet::GetDamage()
{
	return damage;
}

D3DXVECTOR2 BossBullet::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float BossBullet::GetRadius()
{
	return 8.0f;
}

void BossBullet::Hit()
{
	isDead = true;
}
