#include "stdafx.h"

#include "Skill.h"
#include "global.h"

Skill::Skill()
{
	posX = 0;
	posY = 0;

	ShieldCoolTime = 0;
	ShieldOn = false;
	ShieldTime = 3;

	D3DXCreateFont(g_pd3dDevice, -12, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &g_pFont);

}

void Skill::Update(float x, float y)
{
	posX = x;
	posY = y;

	if (ShieldCoolTime > 0 && ShieldTime < 0)
	{
		ShieldCoolTime -= deltaTime;
	}

	if (ShieldTime > 0)
	{
		ShieldTime -= deltaTime;
	}
	else
	{
		ShieldOn = false;
	}

	if (inputManager.prevKeyBuffer['Q'] == 1 &&
		inputManager.keyBuffer['Q'] == 0 &&
		ShieldCoolTime <= 0)
	{
		ShieldOn = true;
		ShieldTime = 5.0f;
		ShieldCoolTime = 7.0f;
	}
}

void Skill::Render()
{
	// Shield
	if (ShieldOn)
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_SKILL_SHIELD);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 64;
		srcRect.bottom = 64;

		D3DXVECTOR3 pos(posX - 32, posY - 32, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

	// Shield Icon
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_SKILL_SHIELD_COOL);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 64;
		srcRect.bottom = 64;

		D3DXVECTOR3 pos(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 100, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

	// Shield CoolTime Icon
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_SKILL_COOL_BOX);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 64;
		srcRect.bottom = 64 * (ShieldCoolTime / 7);

		D3DXVECTOR3 pos(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 100, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}	
}

D3DXVECTOR2 Skill::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}
float Skill::GetRadius()
{
	return 16.0f;
}