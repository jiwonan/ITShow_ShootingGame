#include "stdafx.h"
#include "game_background.h"
#include "global.h"

GameBackground::GameBackground()
{
	BackgroundY = 0;
}

void GameBackground::Update()
{
	BackgroundY += 3;

	BackgroundY = (int)BackgroundY % 680;
}

void GameBackground::Render()
{
	TextureElement* newElement = textureManager.GetTexture(GAME_BACKGROUND_IMAGE);

	newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 640;
	srcRect.bottom = 680;

	D3DXVECTOR3 pos(0, round(BackgroundY), 0);
	newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	pos = D3DXVECTOR3(0, BackgroundY - 680, 0);
	newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	newElement->sprite->End();
}