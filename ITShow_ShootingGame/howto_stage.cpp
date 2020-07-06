#include "stdafx.h"
#include "howto_stage.h"
#include "global.h"

HowtoStage::HowtoStage()
{

}

void HowtoStage::Update()
{

	if (inputManager.keyBuffer[VK_LBUTTON] == 0 &&
		inputManager.prevKeyBuffer[VK_LBUTTON] == 1)
	{
		stageManager.LoadTitleStage();
	}
}

void HowtoStage::Render()
{
	// draw BG
	{
		TextureElement* newElement = textureManager.GetTexture(HOWTOPLAY_SCREEN_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 800;
		srcRect.bottom = 600;

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

}