#include "stdafx.h"

#include "timer_stage.h"
#include "global.h"

TimerStage::TimerStage()
{
	Timer = 6;

	top = 0;
	bottom = 600;

	isOpen = false;

	D3DXCreateFont(g_pd3dDevice, 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &g_pFont);
}

void TimerStage::Update()
{
	Timer -= deltaTime;

	if (Timer < 0)
	{
		top += deltaTime * 1000;
		bottom += deltaTime * 1000;

		if (top > WINDOW_HEIGHT)
			isOpen = true;
	}

	if (isOpen)
	{
		soundManager.sndSecondStageBGM->Reset();
		soundManager.sndSecondStageBGM->Play(0, DSBPLAY_LOOPING, 1);
		stageManager.LoadGameSecondStage();
	}
}

void TimerStage::Render()
{
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_DOOR_UI);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = top;
		srcRect.right = 800;
		srcRect.bottom = bottom;

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

	{
		RECT fontRect;
		fontRect.left = 400;
		fontRect.top = 330;
		fontRect.right = 100;
		fontRect.bottom = 10;

		swprintf_s(buffer, 128, L"%d", (int)Timer);

		g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	{
		RECT fontRect;
		fontRect.left = 300;
		fontRect.top = 130;
		fontRect.right = 100;
		fontRect.bottom = 10;

		swprintf_s(buffer, 128, L"Stage One Clear!");

		g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (Timer < 4)
	{
		RECT fontRect;
		fontRect.left = 270;
		fontRect.top = 160;
		fontRect.right = 100;
		fontRect.bottom = 10;

		swprintf_s(buffer, 128, L"Current Score : %d", gameStat.score);

		g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}