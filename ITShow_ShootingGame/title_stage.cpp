#include "stdafx.h"
#include "title_stage.h"
#include "global.h"

TitleStage::TitleStage()
{
	btnW = 230;
	btnH = 60;

	btnX = WINDOW_WIDTH / 2 - btnW / 2 + 100;
	btnY = WINDOW_HEIGHT * 0.7 - 55;

	btnW2 = 230;
	btnH2 = 60;

	btnX2 = WINDOW_WIDTH / 2 - btnW2 / 2 + 100;
	btnY2 = WINDOW_HEIGHT * 0.7 + 55;

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
		srcRect.right = 800;
		srcRect.bottom = 600;

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
		srcRect.right = btnW;
		srcRect.bottom = btnH;

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
		srcRect.right = btnW2;
		srcRect.bottom = btnH2;

		D3DXVECTOR3 pos(btnX2, btnY2, 0);

		newElement->sprite->Draw(newElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		newElement->sprite->End();
	}
}