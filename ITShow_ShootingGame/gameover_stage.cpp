#include "stdafx.h"

#include "gameover_stage.h"
#include "global.h"

GameoverStage::GameoverStage()
{
	btnX = WINDOW_WIDTH / 2 - 90;
	btnY = WINDOW_HEIGHT * 0.7 - 25;

	btnW = 180;
	btnH = 50;

	D3DXCreateFont(g_pd3dDevice, 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &g_pFont);
}

void GameoverStage::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(gWindowHandle, &pt);

	if (inputManager.keyBuffer[VK_LBUTTON] == 0 &&
		inputManager.prevKeyBuffer[VK_LBUTTON] == 1)
	{
		if (pt.x > btnX&&pt.x<btnX + btnW &&
			pt.y>btnY&&pt.y < btnY + btnH)
		{
			stageManager.LoadTitleStage();
		}
	}
}

void GameoverStage::Render()
{
	// draw BG
	{
		TextureElement* newElement = textureManager.GetTexture(GAMEOVER_SCREEN_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 640;
		srcRect.bottom = 480;

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}
	// draw Btn
	{
		TextureElement* newElement = textureManager.GetTexture(GAMEOVER_BTN_IMG);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 180;
		srcRect.bottom = 50;

		D3DXVECTOR3 pos(btnX, btnY, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

	{
		RECT fontRect;
		fontRect.left = 200;
		fontRect.top = 160;
		fontRect.right = 100;
		fontRect.bottom = 10;

		WCHAR buffer[128];

		swprintf_s(buffer, 128, L"Current Score : %d", gameStat.score);

		g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
