#include "stdafx.h"
#include "player.h"
#include "global.h"
#include "item.h"

Player::Player()
{
	playerX = WINDOW_WIDTH / 2;
	playerY = WINDOW_HEIGHT * 0.7;

	weaponType = kSpread;

	shootTime = 0;

	isInvincible = false;
	invincibleTimer = 0;
}

void Player::Update()
{
	if (isInvincible)
	{
		invincibleTimer -= deltaTime;

		if (invincibleTimer < 0)
		{
			isInvincible = false;
			invincibleTimer = 0;
		}
	}

	if (gameStat.cheatInvincible)
		isInvincible = true;


	if (inputManager.keyBuffer[VK_LEFT] == 1)
	{
		playerX -= gameStat.speed * deltaTime;
	}
	if (inputManager.keyBuffer[VK_RIGHT] == 1)
	{
		playerX += gameStat.speed * deltaTime;
	}
	if (inputManager.keyBuffer[VK_UP] == 1)
	{
		playerY -= gameStat.speed * deltaTime;
	}
	if (inputManager.keyBuffer[VK_DOWN] == 1)
	{
		playerY += gameStat.speed * deltaTime;
	}

	if (playerX < 0)
		playerX = 0;
	if (playerX > WINDOW_WIDTH - 13)
		playerX = WINDOW_WIDTH - 13;
	if (playerY < 0)
		playerY = 0;
	if (playerY > WINDOW_HEIGHT - 21)
		playerY = WINDOW_HEIGHT - 21;

	// ���� Ű ��ȯ.
	if (inputManager.prevKeyBuffer['K'] == 1 &&
		inputManager.keyBuffer['K'] == 0)
	{
		if (weaponType == kSpread)
			weaponType = kGeneral;
		else weaponType = kSpread;
	}

	shootTime += deltaTime;
	if (inputManager.prevKeyBuffer['Z'] == 1 &&
		inputManager.keyBuffer['Z'] == 0 && weaponType == kSpread)
	{
		gameSystem.GeneratePlayerBulletSpread(playerX, playerY);
	}

	if (shootTime > gameStat.shootDelay)
	{
		if (inputManager.keyBuffer['Z'] == 1 && weaponType == kGeneral)
		{
			gameSystem.GeneratePlayerBulletGeneral(playerX, playerY);
		}
		shootTime = 0;
	}
}

void Player::Render()
{
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_PLAYER_BODY_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 27;
		srcRect.bottom = 42;

		D3DXVECTOR3 pos(playerX - 13, playerY - 21, 0);

		D3DCOLOR color;

		if (isInvincible)
		{
			if (rand() % 100 < 50)
			{
				color = D3DCOLOR_ARGB(0, 0, 0, 0);
			}
			else
			{
				color = D3DCOLOR_XRGB(255, 255, 255);
			}
		}
		else
		{
			color = D3DCOLOR_XRGB(255, 255, 255);
		}

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, color);

		newElement->sprite->End();
	}
	// Player HP BG
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_HP_BG_UI);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = gameStat.fullHP;
		srcRect.bottom = 10;

		D3DXVECTOR3 pos(playerX - (gameStat.fullHP / 2), playerY + 30, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}

	// Player HP
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_HP_UI);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = gameStat.hp;
		srcRect.bottom = 10;

		D3DXVECTOR3 pos(playerX - (gameStat.fullHP / 2), playerY + 30, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}

	// Player EXP BG
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_HP_BG_UI);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = gameStat.playerLevelUp;
		srcRect.bottom = 10;

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - gameStat.playerLevelUp / 2, 470, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}

	// Player EXP
	{
		TextureElement* newElement = textureManager.GetTexture(GAME_EXP_UI);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = gameStat.exp;
		srcRect.bottom = 10;

		D3DXVECTOR3 pos(WINDOW_WIDTH / 2 - gameStat.playerLevelUp / 2, 470, 0);
		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
		newElement->sprite->End();
	}

}

D3DXVECTOR2 Player::GetPosition()
{
	return D3DXVECTOR2(playerX, playerY);
}

float Player::GetRadius()
{
	return 13.0f;
}

void Player::Hit(float damage)
{
	gameStat.hp -= damage;
	if (gameStat.hp <= 0)
	{
		gameStat.hp = 0;
		stageManager.LoadGameoverStage();
	}
	isInvincible = true;
	invincibleTimer = 3.0f;
}

void Player::HitByItem(int type)
{
	switch (type)
	{
	case kHp:
		gameStat.hp *= 1.1;
		break;
	case kLevelUp:
		gameStat.PlayerLevelUp();
		break;
	case kResetCoolTime:
		gameSystem.ResetSkillCoolTime();
		break;
	}
}