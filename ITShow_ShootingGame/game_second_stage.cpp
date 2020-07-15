#include "stdafx.h"

#include "game_second_stage.h"
#include "global.h"

GameSecondStage::GameSecondStage()
{
	gameSystem.ClearAll();
	gameSystem.player = &player;

	D3DXCreateFont(g_pd3dDevice, -12, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &g_pFont);	

	enemyTime = 0;

	alpha = 0;

	per = 90;

	gameStat.playerState = kFirst;

	cheatManager.isPause = false;
}

void GameSecondStage::Update()
{
	// Pause가 아닐 때.
	if (!cheatManager.isPause)
	{
		int enemyType = rand() % 4 + 1;
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
				case 4:
					gameSystem.GenerateEnemyD();
					break;
				default:
					break;
				}
				enemyTime = 0;
			}
		}

		// 보스가 아닐 때 배경 업데이트
		if (gameStat.playerState != kMidBoss || gameStat.playerState != kLastBoss)
		{
			background.Update();
		}
		player.Update();
		gameSystem.Update();

		// 중간 보스 생성.
		if (gameStat.score > 3000 && gameStat.playerState == kFirst)
		{
			gameStat.playerState = kMidBoss;
			per = 95;
			gameSystem.GenerateBossC();
		}

		if (gameStat.score > 4000 && gameStat.playerState == kSecond)
		{
			gameStat.playerState = kLastBoss;
			per = 70;
			gameSystem.GenerateBossD();
		}

		// 플레이어 레벨업.
		if (gameStat.playerLevelUp < gameStat.exp&&gameStat.level <= 5)
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

		alpha += 3;
		if (alpha > 255)
		{
			alpha = 255;
			soundManager.sndSecondStageBGM->Stop();
			stageManager.LoadClearStage();
		}
	}
}

void GameSecondStage::Render()
{
	background.Render();
	gameSystem.Render();
	player.Render();
	// Score
	{
		RECT fontRect;
		fontRect.left = 0;
		fontRect.top = 65;
		fontRect.right = 640;
		fontRect.bottom = 10;

		WCHAR buffer[128];
		swprintf_s(buffer, 128, L"Score: %d", gameStat.score);

		g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// Stage
	{
		RECT fontRect;
		fontRect.left = WINDOW_WIDTH - 80;
		fontRect.top = 0;
		fontRect.right = 30;
		fontRect.bottom = 10;

		g_pFont->DrawText(NULL, L"Stage Two", -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (gameStat.playerState == kEnd)
	{
		TextureElement* fadeElement = textureManager.GetTexture(FADE_SCREEN);

		fadeElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 800;
		srcRect.bottom = 600;

		D3DXVECTOR3 pos(0, 0, 0);
		fadeElement->sprite->Draw(fadeElement->texture, &srcRect, nullptr, &pos,
			D3DCOLOR_RGBA(0, 0, 0, (int)alpha));

		fadeElement->sprite->End();
	}
}