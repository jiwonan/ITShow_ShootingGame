#include "stdafx.h"
#include "clear_stage.h"
#include "global.h"
#include <string>

ClearStage::ClearStage()
{
	stageState = kWaitingPlayerName;
	alpha = 0;

	btnX = WINDOW_WIDTH / 2 - 90;
	btnY = WINDOW_HEIGHT * 0.7 - 25;

	btnW = 180;
	btnH = 50;

	D3DXCreateFont(g_pd3dDevice, 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &g_pFont);

	// 폰트 생성
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

ClearStage::~ClearStage()
{
	font->Release();
}

void ClearStage::Update()
{
	if (stageState == kWaitingPlayerName)
	{
		int startIndex = 'A';
		int endIndex = 'Z';

		if (inputManager.prevKeyBuffer[VK_BACK] == 1 &&
			inputManager.keyBuffer[VK_BACK] == 0)
		{
			if (!playerName.empty())
			{
				playerName.pop_back();
			}
		}
		else if (inputManager.prevKeyBuffer[VK_RETURN] == 1 &&
			inputManager.keyBuffer[VK_RETURN] == 0)
		{

			// 랭킹을 저장해야 한다.
			std::string name(playerName.begin(), playerName.end());
			gameStat.SaveNewRecord(name.c_str());

			// 저장하고 타이틀 화면으로...
			stageManager.LoadTitleStage();
		}
		else
		{
			for (int i = startIndex; i <= endIndex; ++i)
			{
				if (inputManager.prevKeyBuffer[i] == 1 &&
					inputManager.keyBuffer[i] == 0)
				{
					playerName.push_back((char)i);
				}
			}
		}
	}

	//POINT pt;
	//GetCursorPos(&pt);
	//ScreenToClient(gWindowHandle, &pt);

	//if (inputManager.keyBuffer[VK_LBUTTON] == 0 &&
	//	inputManager.prevKeyBuffer[VK_LBUTTON] == 1)
	//{
	//	if (pt.x > btnX && pt.x<btnX + btnW &&
	//		pt.y>btnY && pt.y < btnY + btnH)
	//	{
	//		stageManager.LoadTitleStage();
	//	}
	//}
}

void ClearStage::Render()
{
	// draw BG
	{
		TextureElement* newElement = textureManager.GetTexture(CLEAR_SCREEN_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 800;
		srcRect.bottom = 600;

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

	{
		RECT rc;
		SetRect(&rc, WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT * 0.6, 0, 0);
		WCHAR buffer[128];
		std::wstring wName(playerName.begin(), playerName.end());
		swprintf_s<128>(buffer, L"%s", wName.c_str());
		font->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
	//// draw Btn
	//{
	//	TextureElement* newElement = textureManager.GetTexture(GAMEOVER_BTN_IMG);

	//	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//	RECT srcRect;
	//	srcRect.left = 0;
	//	srcRect.top = 0;
	//	srcRect.right = 180;
	//	srcRect.bottom = 50;

	//	D3DXVECTOR3 pos(btnX, btnY, 0);

	//	newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	//	newElement->sprite->End();
	//}

	{
		RECT fontRect;
		fontRect.left = 270;
		fontRect.top = 160;
		fontRect.right = 100;
		fontRect.bottom = 10;

		WCHAR buffer[128];

		swprintf_s(buffer, 128, L"Current Score : %d", gameStat.score);

		g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}