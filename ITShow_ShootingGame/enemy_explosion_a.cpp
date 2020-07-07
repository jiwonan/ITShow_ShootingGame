#include "stdafx.h"

#include "enemy_explosion_a.h"
#include "global.h"

EnemyExplosionA::EnemyExplosionA(float x, float y)
{
	posX = x;
	posY = y;
	isDead = false;

	for (int i = 0; i < 5; ++i)
	{
		int x = i * 16;
		int y = 0;
		int width = 16;
		int height = 16;

		AnimFrame newFrame;
		newFrame.x = x;
		newFrame.y = y;
		newFrame.width = width;
		newFrame.height = height;
		newFrame.time = 0.5f;

		frames.push_back(newFrame);
	}

	animIndex = 0;
	animTime = 0;
}

void EnemyExplosionA::Update()
{
	animTime += deltaTime;
	if (animTime > frames[animIndex].time)
	{
		animIndex++;
		animTime = 0;
		if (animIndex > frames.size() - 1)
		{
			animIndex = frames.size() - 1;
			isDead = true;
		}
	}
}

void EnemyExplosionA::Render()
{
	TextureElement* newElement = textureManager.GetTexture(GAME_ENEMY_EXPLOSION_A);

	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect = GetSourceRect();

	D3DXVECTOR3 pos(posX - 8, posY - 8, 0);
	newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	newElement->sprite->End();
}

bool EnemyExplosionA::IsDead()
{
	return isDead;
}

RECT EnemyExplosionA::GetSourceRect()
{
	RECT srcRect;

	srcRect.top = frames[animIndex].x;
	srcRect.left = frames[animIndex].y;
	srcRect.right = frames[animIndex].x + frames[animIndex].width;
	srcRect.bottom = frames[animIndex].y + frames[animIndex].height;

	return srcRect;
}

