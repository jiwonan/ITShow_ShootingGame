#include "stdafx.h"

#include "cheat_manager.h"
#include "global.h"

CheatManager::CheatManager()
{
	D3DXCreateFont(g_pd3dDevice, -12, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &g_pFont);
}

void CheatManager::KeyF1()
{
	if (gameStat.cheatInvincible)
		gameStat.cheatInvincible = false;
	else
		gameStat.cheatInvincible = true;
}

void CheatManager::KeyF2()
{
	if (gameStat.level < 5)
		gameStat.PlayerLevelUp();
}

void CheatManager::KeyF3()
{

}

void CheatManager::KeyF4()
{
	stageManager.LoadTitleStage();
}

void CheatManager::KeyF5()
{
	stageManager.LoadGameFirstStage();
}

void CheatManager::KeyF6()
{
	gameStat.score += 2500;
	stageManager.LoadGameSecondStage();
}

void CheatManager::KeyF7()
{

}

void CheatManager::Update()
{
	if (inputManager.prevKeyBuffer[VK_F1] == 1 &&
		inputManager.keyBuffer[VK_F1] == 0)
	{
		KeyF1();
	}
	if (inputManager.prevKeyBuffer[VK_F2] == 1 &&
		inputManager.keyBuffer[VK_F2] == 0)
	{
		KeyF2();
	}
	if (inputManager.prevKeyBuffer[VK_F3] == 1 &&
		inputManager.keyBuffer[VK_F3] == 0)
	{
		KeyF3();
	}
	if (inputManager.prevKeyBuffer[VK_F4] == 1 &&
		inputManager.keyBuffer[VK_F4] == 0)
	{
		KeyF4();
	}
	if (inputManager.prevKeyBuffer[VK_F5] == 1 &&
		inputManager.keyBuffer[VK_F5] == 0)
	{
		KeyF5();
	}
	if (inputManager.prevKeyBuffer[VK_F6] == 1 &&
		inputManager.keyBuffer[VK_F6] == 0)
	{
		KeyF6();
	}
}

void CheatManager::Render()
{
	// Player Level
	{
		RECT fontRect;
		fontRect.left = 100;
		fontRect.top = 35;
		fontRect.right = 640;
		fontRect.bottom = 10;

		WCHAR buffer_hp[128];
		swprintf_s(buffer_hp, 128, L"Player Level: %d", gameStat.level);

		g_pFont->DrawText(NULL, buffer_hp, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// Player EXP
	{
		RECT fontRect;
		fontRect.left = 100;
		fontRect.top = 50;
		fontRect.right = 640;
		fontRect.bottom = 10;

		WCHAR buffer_hp[128];
		swprintf_s(buffer_hp, 128, L"currEXP: %d", gameStat.exp);

		g_pFont->DrawText(NULL, buffer_hp, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	// Player Level
	{
		RECT fontRect;
		fontRect.left = 100;
		fontRect.top = 75;
		fontRect.right = 640;
		fontRect.bottom = 10;

		WCHAR buffer_hp[128];
		swprintf_s(buffer_hp, 128, L"Level Up EXP: %d", gameStat.playerLevelUp);

		g_pFont->DrawText(NULL, buffer_hp, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}