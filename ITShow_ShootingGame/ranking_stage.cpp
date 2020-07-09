#include "stdafx.h"
#include "ranking_stage.h"
#include "global.h"
#include <string>

RankingStage::RankingStage()
{
	D3DXCreateFont(g_pd3dDevice, 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &g_pFont);

	HDC hDC = GetDC(NULL);
	int nLogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);

	int fontSize = 15;
	int nHeight = -fontSize * nLogPixelsY / 72;

	TCHAR g_strFont[LF_FACESIZE];
	wcscpy_s(g_strFont, 32, L"Arial");

	D3DXCreateFont(g_pd3dDevice,            // D3D device
		nHeight,               // Height
		0,                     // Width
		FW_DONTCARE,           // Weight
		1,                     // MipLevels, 0 = autogen mipmaps
		FALSE,                 // Italic
		DEFAULT_CHARSET,       // CharSet
		OUT_DEFAULT_PRECIS,    // OutputPrecision
		DEFAULT_QUALITY,       // Quality
		DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
		g_strFont,              // pFaceName
		&font);              // ppFont
}

void RankingStage::Update()
{
	gameStat.Load();

	if (inputManager.keyBuffer[VK_LBUTTON] == 0 &&
		inputManager.prevKeyBuffer[VK_LBUTTON] == 1)
	{
		stageManager.LoadTitleStage();
	}
}

void RankingStage::Render()
{
	// draw BG
	{
		TextureElement* newElement = textureManager.GetTexture(RANKING_SCREEN_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 800;
		srcRect.bottom = 600;

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}
	// draw Ranking
	{
		for (int i = 0; i < 5; ++i)
		{
			RECT fontRect;
			fontRect.left = 300;
			fontRect.top = 200 + i * 50;
			fontRect.right = 100;
			fontRect.bottom = 10;

			WCHAR buffer[128];

			swprintf_s(buffer, 128, L"%d %S %d", (i + 1), gameStat.ranking[i].playerName, gameStat.ranking[i].playerScore);

			font->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}
