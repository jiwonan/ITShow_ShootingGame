#include "stdafx.h"

#include "item.h"
#include "global.h"

Item::Item(float x, float y)
{
	posX = x;
	posY = y;
	velY = 100;

	isDead = false;

	type = rand() % 3;
}
void Item::Update()
{
	posY += velY * deltaTime;

	if (posY > WINDOW_HEIGHT)
		isDead = true;
}

void Item::Render()
{
	int id;
	switch (type)
	{
	case kHp:
		id = GAME_ITEM_HP;
		break;
	case kLevelUp:
		id = GAME_ITEM_LEVEL;
		break;
	case kResetCoolTime:
		id = GAME_ITEM_RESET;
		break;
	}

	TextureElement* newElement = textureManager.GetTexture(id);

	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 32;
	srcRect.bottom = 32;

	D3DXVECTOR3 pos(posX - 16, posY - 16, 0);

	newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	newElement->sprite->End();
}

bool Item::IsDead()
{
	return isDead;
}

void Item::Hit()
{
	isDead = true;
}
D3DXVECTOR2 Item::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}
float Item::GetRadius()
{
	return 16.0f;
}