#include "stdafx.h"
#include "game_first_stage.h"
#include "global.h"

GameFirstStage::GameFirstStage()
{
	gameSystem.ClearAll();
	gameStat.score = 0;
	gameStat.exp = 0;
	gameStat.level = 1;

	gameStat.hp = 100;
	gameStat.speed = 300;
	gameStat.fullHP = 100;

	gameStat.generalDamage = 15;
	gameStat.spreadDamage = 2;

	gameStat.shootDelay = 0.3f;

	D3DXCreateFont(g_pd3dDevice, -12, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &g_pFont);

	per = 50;

	enemyTime = 0;
	gameSystem.player = &player;
	gameStat.playerState = kFirst;
	gameStat.playerLevelUp = 300;

	cheatManager.isPause = false;
}


void GameFirstStage::Update()
{
	// Pause가 아닐 때.
	if (!cheatManager.isPause)
	{
		int enemyType = rand() % 3 + 1;
		// EnemyA 랜덤 생성.
		enemyTime += deltaTime;
		if (rand() % 100 < per)
		{
			if (enemyTime > 1)
			{
				switch (enemyType)
				{
				case 1:
					gameSystem.GenerateEnemyA();
					break;
				case 2:
					gameSystem.GenerateEnemyB();
					break;
				case 3:
					gameSystem.GenerateEnemyC();
					break;
				default:
					break;
				}
				enemyTime = 0;
			}
		}

		// 보스가 아닐 때 배경 업데이트
		if (gameStat.playerState != kMidBoss)
		{
			background.Update();
			gameStat.score++;
		}
		player.Update();
		gameSystem.Update();
		
		// 중간 보스 생성.
		if (gameStat.score > 1000 && gameStat.playerState == kFirst)
		{
			gameStat.playerState = kMidBoss;
			gameSystem.GenerateBossA();
			per = 60;
		}

		if (gameStat.score > 3000 && gameStat.playerState == kSecond)
		{
			gameStat.playerState = kLastBoss;
			gameSystem.GenerateBossB();
		}

		// 플레이어 레벨업.
		if (gameStat.playerLevelUp < gameStat.exp && gameStat.level <= 5)
		{
			gameStat.PlayerLevelUp();
		}
		cheatManager.Update();
	}

	if (inputManager.keyBuffer[VK_F7] == 1)
	{
		cheatManager.isPause = true;
		cheatManager.Render();
	}
	if (inputManager.keyBuffer[VK_F7] == 0)
	{
		cheatManager.isPause = false;
	}

	if (gameStat.playerState == kEnd)
	{
		stageManager.LoadTimerStage();
		gameStat.score += 1000;
	}
}

void GameFirstStage::Render()
{
	background.Render();
	gameSystem.Render();
	player.Render();

	// Score
	{
		RECT fontRect;
		fontRect.left = 0;
		fontRect.top = 0;
		fontRect.right = 640;
		fontRect.bottom = 10;

		WCHAR buffer[128];
		swprintf_s(buffer, 128, L"Score: %d", gameStat.score);

		g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// Player Level
	{
		RECT fontRect;
		fontRect.left = 0;
		fontRect.top = 15;
		fontRect.right = 640;
		fontRect.bottom = 10;

		WCHAR buffer_hp[128];
		swprintf_s(buffer_hp, 128, L"%d", gameStat.level);

		g_pFont->DrawText(NULL, buffer_hp, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	// Stage
	{
		RECT fontRect;
		fontRect.left = WINDOW_WIDTH - 80;
		fontRect.top = 0;
		fontRect.right = 30;
		fontRect.bottom = 10;

		g_pFont->DrawText(NULL, L"Stage One", -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}