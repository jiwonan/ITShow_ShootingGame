#include "stdafx.h"
#include "title_stage.h"
#include "global.h"

TitleStage::TitleStage()
{
	btnX = WINDOW_WIDTH / 2 - 90;
	btnY = WINDOW_HEIGHT * 0.7 - 55;

	btnW = 180;
	btnH = 50;

	btnX2 = WINDOW_WIDTH / 2 - 90;
	btnY2 = WINDOW_HEIGHT * 0.7 + 35;

	btnW2 = 180;
	btnH2 = 50;

}

void TitleStage::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(gWindowHandle, &pt);

	if (inputManager.keyBuffer[VK_LBUTTON] == 0 &&
		inputManager.prevKeyBuffer[VK_LBUTTON] == 1)
	{
		if (pt.x > btnX&&pt.x<btnX + btnW &&
			pt.y>btnY&&pt.y < btnY + btnH)
		{
			stageManager.LoadGameFirstStage();
		}

		if (pt.x > btnX2&&pt.x<btnX2 + btnW2 &&
			pt.y>btnY2&&pt.y < btnY2 + btnH2)
		{
			stageManager.LoadHowtoStage();
		}
	}
}

void TitleStage::Render()
{
	// draw BG
	{
		TextureElement* newElement = textureManager.GetTexture(TITLE_SCREEN_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 640;
		srcRect.bottom = 480;

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

	// draw Btn
	{
		TextureElement* newElement = textureManager.GetTexture(TITLE_BTN_IMAGE);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 180;
		srcRect.bottom = 50;

		D3DXVECTOR3 pos(btnX, btnY, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}

	// draw Btn2
	{
		TextureElement* newElement = textureManager.GetTexture(TITLE_BTN_IMAGE_HOWTO);

		newElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = 180;
		srcRect.bottom = 50;

		D3DXVECTOR3 pos(btnX2, btnY2, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}
}