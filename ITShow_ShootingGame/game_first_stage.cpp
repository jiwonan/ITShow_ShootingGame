#include "stdafx.h"

#include "game_first_stage.h"
#include "global.h"

GameFirstStage::GameFirstStage()
{
	gameSystem.ClearAll();
	gameStat.score = 0;
	gameStat.exp = 0;
	gameStat.level = 1;

	gameStat.hp = 200;
	gameStat.speed = 300;
	gameStat.fullHP = 200;

	gameStat.playerDamage = 1;
	gameStat.expGage = 1;

	gameStat.generalDamage = 6;
	gameStat.spreadDamage = 1;

	gameStat.shootDelay = 0.3f;

	D3DXCreateFont(g_pd3dDevice, -12, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &g_pFont);

	per = 80;

	enemyTime = 0;
	gameSystem.player = &player;
	gameStat.playerState = kFirst;
	gameStat.playerLevelUp = 300;

	cheatManager.isPause = false;

	gameState = kFading;
	alpha = 255;
}


void GameFirstStage::Update()
{
	if (gameState == kFading)
	{
		alpha -= 4;

		if (alpha <= 0)
		{
			alpha = 0;
			gameState = kPlaying;

			soundManager.sndFirstStageBGM->Reset();
			soundManager.sndFirstStageBGM->Play(0, DSBPLAY_LOOPING, 1);
		}
	}
	// Pause�� �ƴ� ��.
	else if (!cheatManager.isPause && gameState != kEnding)
	{
		int enemyType = rand() % 3 + 1;
		// EnemyA ���� ����.
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

		// ������ �ƴ� �� ��� ������Ʈ
		if (gameStat.playerState != kMidBoss || gameStat.playerState != kLastBoss)
		{
			background.Update();
		}
		player.Update();
		gameSystem.Update();

		// �߰� ���� ����.
		if (gameStat.score > 120 && gameStat.playerState == kFirst)
		{
			gameStat.playerState = kMidBoss;
			gameSystem.GenerateBossA();
			per = 85;
		}

		if (gameStat.score > 600 && gameStat.playerState == kSecond)
		{
			gameStat.playerState = kLastBoss;
			gameSystem.GenerateBossB();
		}

		// �÷��̾� ������.
		if (gameStat.playerLevelUp < gameStat.exp && gameStat.level <= 5)
		{
			gameStat.PlayerLevelUp();
		}
		cheatManager.Update();


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
			gameState = kEnding;
			gameStat.score += 1000;
		}
	}
	
	if (gameState == kEnding)
	{
		alpha += 3;
		if (alpha > 255)
		{
			alpha = 255;
			stageManager.LoadTimerStage();
			soundManager.sndFirstStageBGM->Stop();
		}
	}
}

void GameFirstStage::Render()
{
	background.Render();
	player.Render();
	gameSystem.Render();

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

		g_pFont->DrawText(NULL, L"Stage One", -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	{
		RECT fontRect;
		fontRect.left = WINDOW_WIDTH - 80;
		fontRect.top = 0;
		fontRect.right = 30;
		fontRect.bottom = 10;

		g_pFont->DrawText(NULL, L"Stage One", -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	{
		RECT fontRect;
		fontRect.left = WINDOW_WIDTH - 80;
		fontRect.top = 30;
		fontRect.right = 30;
		fontRect.bottom = 10;

		WCHAR buffer[128];
		swprintf_s(buffer, 128, L"EXP: %f", gameStat.exp);

		g_pFont->DrawText(NULL, buffer, -1, &fontRect, DT_NOCLIP,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (gameState == kFading)
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

	if (gameState == kEnding)
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