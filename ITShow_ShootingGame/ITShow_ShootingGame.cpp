// ITShow_ShootingGame.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <Windows.h>
#include "framework.h"
#include "ITShow_ShootingGame.h"

#include "global.h"

#define MAX_LOADSTRING 100


HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

HWND gWindowHandle;
LPDIRECT3D9         g_pD3D;
LPDIRECT3DDEVICE9   g_pd3dDevice;
ID3DXFont* g_pFont;

float deltaTime = 0.3f;

DWORD prevTime;

bool GameRunning;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

TextureManager textureManager;
InputManager inputManager;
StageManager stageManager;
GameStat gameStat;
GameSystem gameSystem;
CheatManager cheatManager;


void EngineUpdate()
{
	if (inputManager.keyBuffer[VK_ESCAPE] == 0 &&
		inputManager.prevKeyBuffer[VK_ESCAPE] == 1)
	{
		GameRunning = false;
	}
	DWORD cur = GetTickCount();
	DWORD diff = cur - prevTime;
	deltaTime = diff / 1000.0f;
	if (deltaTime > 0.016)
	{
		deltaTime = 0.016;
	}

	prevTime = cur;

	stageManager.Update();
	inputManager.Update();
}

VOID EngineRender()
{
	if (NULL == g_pd3dDevice)
		return;

	// Clear the backbuffer to a blue color
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		stageManager.Render();
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void InitMySound(HWND hWnd)
{
	/*soundManager.Initialize(hWnd, DSSCL_NORMAL);
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sfx/epic_end.wav");
		soundManager.Create(&soundManager.sndPlayerBullet, fileName, DSBCAPS_CTRLVOLUME);
	}*/
}

void InitMyStuff()
{
	textureManager.LoadTexture(L"backgrounds/title.png", TITLE_SCREEN_IMAGE);
	textureManager.LoadTexture(L"ui/ui_btn_gamestart.png", TITLE_BTN_IMAGE);
	textureManager.LoadTexture(L"backgrounds/gameover.png", GAMEOVER_SCREEN_IMAGE);
	textureManager.LoadTexture(L"ui/ui_btn_totitle.png", GAMEOVER_BTN_IMG);
	textureManager.LoadTexture(L"ui/ui_btn_howto.png", TITLE_BTN_IMAGE_HOWTO);
	textureManager.LoadTexture(L"backgrounds/howtoplay.png", HOWTOPLAY_SCREEN_IMAGE);
	textureManager.LoadTexture(L"backgrounds/fade.png", FADE_SCREEN);

	textureManager.LoadTexture(L"backgrounds/bg.png", GAME_BACKGROUND_IMAGE);
	textureManager.LoadTexture(L"player/player.png", GAME_PLAYER_BODY_IMAGE);
	textureManager.LoadTexture(L"player/player_bullet.png", GAME_PLAYER_BULLET_IMAGE);
	textureManager.LoadTexture(L"player/player_bullet_g.png", GAME_PLAYER_BULLET_G_IMAGE);

	textureManager.LoadTexture(L"enemies/enemy_a.png", GAME_ENEMY_A_BODY_IMAGE);
	textureManager.LoadTexture(L"enemies/boss_a.png", GAME_BOSS_A_BODY_IMAGE);
	textureManager.LoadTexture(L"enemies/boss_bullet_a.png", GAME_BOSS_BULLET_A_IMAGE);
	textureManager.LoadTexture(L"enemies/boss_b.png", GAME_BOSS_B_BODY_IMAGE);

	textureManager.LoadTexture(L"backgrounds/background_2.png", GAME_BACKGROUND_IMAGE_2);
	textureManager.LoadTexture(L"enemies/stage2_mid_boss.png", GAME_STAGE_2_MID_BOSS_IMAGE);
	textureManager.LoadTexture(L"enemies/stage2_final_boss.png", GAME_STAGE_2_FINAL_BOSS_IMAGE);
	textureManager.LoadTexture(L"enemies/enemy_b.png", GAME_ENEMY_B_BODY_IMAGE);
	textureManager.LoadTexture(L"enemies/enemy_c.png", GAME_ENEMY_C_BODY_IMAGE);
	textureManager.LoadTexture(L"enemies/enemy_d.png", GAME_ENEMY_D_BODY_IMAGE);

	textureManager.LoadTexture(L"ui/hp_bar.png", GAME_HP_UI);
	textureManager.LoadTexture(L"ui/hp_bg.png", GAME_HP_BG_UI);
	textureManager.LoadTexture(L"ui/exp_bar.png", GAME_EXP_UI);
	textureManager.LoadTexture(L"ui/door.png", GAME_DOOR_UI);
	textureManager.LoadTexture(L"ui/ui_spread_bullet.png", GAME_PLAYER_BULLET_SPREAD_TOGLE);
	textureManager.LoadTexture(L"ui/ui_direct_bullet.png", GAME_PLAYER_BULLET_DIRECT_TOGLE);
	textureManager.LoadTexture(L"ui/boss_hp.png", GAME_BOSS_HP_UI);
	textureManager.LoadTexture(L"ui/boss_hp_bg.png", GAME_BOSS_HP_BG_UI);

	textureManager.LoadTexture(L"effects/enemies_explosion_a.png", GAME_ENEMY_EXPLOSION_A);

	textureManager.LoadTexture(L"ui/item_hp.png", GAME_ITEM_HP);
	textureManager.LoadTexture(L"ui/item_level.png", GAME_ITEM_LEVEL);
	textureManager.LoadTexture(L"ui/item_reset.png", GAME_ITEM_RESET);

	textureManager.LoadTexture(L"ui/skill_shield.png", GAME_SKILL_SHIELD);
	textureManager.LoadTexture(L"ui/player_info_bar.png", GAME_PLAYER_INFO_BAR);
	textureManager.LoadTexture(L"ui/skill_shield_cool.png", GAME_SKILL_SHIELD_COOL);
	textureManager.LoadTexture(L"ui/skill_cool_box.png", GAME_SKILL_COOL_BOX);

	textureManager.LoadTexture(L"ui/level1.png", GAME_PLAYER_LEVEL_ONE);
	textureManager.LoadTexture(L"ui/level2.png", GAME_PLAYER_LEVEL_TWO);
	textureManager.LoadTexture(L"ui/level3.png", GAME_PLAYER_LEVEL_THREE);
	textureManager.LoadTexture(L"ui/level4.png", GAME_PLAYER_LEVEL_FOUR);
	textureManager.LoadTexture(L"ui/level5.png", GAME_PLAYER_LEVEL_FIVE);

	stageManager.LoadTitleStage();

	prevTime = GetTickCount();
	GameRunning = true;
}

HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	// windowed.
	/*
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	*/
	// full Screen.
	
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	return S_OK;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ITSHOWSHOOTINGGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ITSHOWSHOOTINGGAME));

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT && GameRunning == true)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			EngineUpdate();
			EngineRender();
		}
	}

	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ITSHOWSHOOTINGGAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	gWindowHandle = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

	if (!gWindowHandle)
	{
		return FALSE;
	}

	InitD3D(gWindowHandle);
	InitMyStuff();
	InitMySound(gWindowHandle);

	ShowWindow(gWindowHandle, nCmdShow);
	UpdateWindow(gWindowHandle);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		inputManager.keyBuffer[wParam] = 1;
		break;
	}
	case WM_KEYUP:
	{
		inputManager.keyBuffer[wParam] = 0;
		break;
	}
	case WM_LBUTTONDOWN:
	{
		inputManager.keyBuffer[VK_LBUTTON] = 1;
		break;
	}
	case WM_LBUTTONUP:
	{
		inputManager.keyBuffer[VK_LBUTTON] = 0;
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}