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

	BombCoolTime = 0;

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
		ShieldCoolTime <= 0 &&
		gameStat.level >= 2)
	{
		ShieldOn = true;
		ShieldTime = 5.0f;
		ShieldCoolTime = 7.0f;
	}

	if (BombCoolTime > 0)
	{
		BombCoolTime -= deltaTime;
	}

	if (inputManager.prevKeyBuffer['W'] == 1 &&
		inputManager.keyBuffer['W'] == 0 &&
		BombCoolTime <= 0 &&
		gameStat.level >= 3)
	{
		gameSystem.isBombOn = true;
		BombCoolTime = 30.0f;
		soundManager.sndBomb->Reset();
		soundManager.sndBomb->Play(0, 0, 1);
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

		if (gameStat.level >= 2) {
			RECT fontRect;
			fontRect.left = WINDOW_WIDTH - 170;
			fontRect.top = WINDOW_HEIGHT - 32;
			fontRect.right = 64;
			fontRect.bottom = 10;

			WCHAR buffer[128];
			swprintf_s(buffer, 128, L"%d", (int)ShieldCoolTime);

			g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	// Bomb Icon
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_SKILL_BOMB_COOL);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 64;
		srcRect.bottom = 64;

		D3DXVECTOR3 pos(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

	// Bomb Cool Icon
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_SKILL_COOL_BOX);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 64;
		srcRect.bottom = 64 * (BombCoolTime / 30.0);

		D3DXVECTOR3 pos(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();

		if (gameStat.level >= 3) {
			RECT fontRect;
			fontRect.left = WINDOW_WIDTH - 75;
			fontRect.top = WINDOW_HEIGHT - 32;
			fontRect.right = 640;
			fontRect.bottom = 10;

			WCHAR buffer[128];
			swprintf_s(buffer, 128, L"%d", (int)BombCoolTime);

			g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	// shield yet
	if(gameStat.level<2)
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_SKILL_LOCK);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 64;
		srcRect.bottom = 64;

		D3DXVECTOR3 pos(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 100, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();

		RECT fontRect;
		fontRect.left = WINDOW_WIDTH - 200;
		fontRect.top = WINDOW_HEIGHT - 32;
		fontRect.right = 30;
		fontRect.bottom = 10;

		g_pFont->DrawText(NULL, L"UNLOCK\n   Lv.2", -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// Bomb yet
	if(gameStat.level < 3)
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_SKILL_LOCK);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 64;
		srcRect.bottom = 64;

		D3DXVECTOR3 pos(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();

		RECT fontRect;
		fontRect.left = WINDOW_WIDTH - 100;
		fontRect.top = WINDOW_HEIGHT - 32;
		fontRect.right = 30;
		fontRect.bottom = 10;

		g_pFont->DrawText(NULL, L"UNLOCK\n   Lv.3", -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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