#include "stdafx.h"
#include "player_bullet_g.h"
#include "global.h"

PlayerBulletG::PlayerBulletG(float x, float y, float vx, float vy)
{
	posX = x;
	posY = y;
	velX = vx;
	velY = vy;

	isDead = false;
}

void PlayerBulletG::Update()
{
	posX += velX;
	posY -= velY;

	if (posX<0 || posX>WINDOW_WIDTH ||
		posY<0 || posY>WINDOW_HEIGHT)
	{
		isDead = true;
	}
}

void PlayerBulletG::Render()
{
	TextureElement* newElement = textureManager.GetTexture(GAME_PLAYER_BULLET_G_IMAGE);

	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 12;
	srcRect.bottom = 30;

	D3DXVECTOR3 pos(posX - 6, posY - 15, 0);
	newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	newElement->sprite->End();
}

bool PlayerBulletG::IsDead()
{
	return isDead;
}

int PlayerBulletG::GetDamage()
{
	return gameStat.generalDamage;
}

D3DXVECTOR2 PlayerBulletG::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float PlayerBulletG::GetRadius()
{
	return 6.0f;
}

void PlayerBulletG::Hit()
{
	isDead = true;
}
