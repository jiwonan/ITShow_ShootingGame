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
	if (ShieldOn)
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_SKILL_SHILD);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 32;
		srcRect.bottom = 64;

		D3DXVECTOR3 pos(posX - 16, posY - 32, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

	RECT fontRect;
	fontRect.left = 0;
	fontRect.top = 30;
	fontRect.right = 10;
	fontRect.bottom = 10;

	WCHAR buffer[128];
	swprintf_s(buffer, 128, L"ShieldCoolTime.%d", (int)ShieldCoolTime);

	g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

D3DXVECTOR2 Skill::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}
float Skill::GetRadius()
{
	return 16.0f;
}