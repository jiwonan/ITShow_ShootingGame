#pragma once

#include <d3d9.h>

#include "texture_manager.h"
#include "input_manager.h"
#include "stage_manager.h"
#include "game_stat.h"
#include "game_system.h"
#include "cheat_manager.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define TITLE_SCREEN_IMAGE 1000
#define TITLE_BTN_IMAGE 1001
#define GAMEOVER_SCREEN_IMAGE 1002
#define GAMEOVER_BTN_IMG 1003
#define TITLE_BTN_IMAGE_HOWTO 1004
#define HOWTOPLAY_SCREEN_IMAGE 1005

#define GAME_BACKGROUND_IMAGE 2000
#define GAME_PLAYER_BODY_IMAGE 2001
#define GAME_PLAYER_BULLET_IMAGE 2002
#define GAME_PLAYER_BULLET_G_IMAGE 2003

#define GAME_ENEMY_A_BODY_IMAGE 3000
#define GAME_BOSS_A_BODY_IMAGE 3001
#define GAME_BOSS_BULLET_A_IMAGE 3002
#define GAME_BOSS_B_BODY_IMAGE 3003
#define GAME_ENEMY_B_BODY_IMAGE 3004

#define GAME_BACKGROUND_IMAGE_2 4000
#define GAME_STAGE_2_MID_BOSS_IMAGE 4001
#define GAME_STAGE_2_FINAL_BOSS_IMAGE 4002
#define GAME_ENEMY_C_BODY_IMAGE 4003
#define GAME_ENEMY_D_BODY_IMAGE 4004

#define GAME_HP_BG_UI 5001
#define GAME_HP_UI 5002
#define GAME_EXP_UI 5003
#define GAME_DOOR_UI 5004
#define GAME_PLAYER_INFO_BAR 5005
#define GAME_PLAYER_BULLET_SPREAD_TOGLE 5006
#define GAME_PLAYER_BULLET_DIRECT_TOGLE 5007
#define GAME_BOSS_HP_BG_UI 5008
#define GAME_BOSS_HP_UI 5009

#define GAME_ENEMY_EXPLOSION_A 6000

#define GAME_ITEM_HP 7000
#define GAME_ITEM_LEVEL 7001
#define GAME_ITEM_RESET 7002

#define GAME_SKILL_SHIELD 8000
#define GAME_SKILL_BOMB 8001
#define GAME_SKILL_SHIELD_COOL 8002
#define GAME_SKILL_BOMB_COOL 8003
#define GAME_SKILL_COOL_BOX 8004

#define GAME_PLAYER_LEVEL_ONE 9001
#define GAME_PLAYER_LEVEL_TWO 9002
#define GAME_PLAYER_LEVEL_THREE 9003
#define GAME_PLAYER_LEVEL_FOUR 9004
#define GAME_PLAYER_LEVEL_FIVE 9005

extern HWND gWindowHandle;
extern LPDIRECT3D9         g_pD3D;
extern LPDIRECT3DDEVICE9   g_pd3dDevice;
extern ID3DXFont* g_pFont;

extern float deltaTime;

extern TextureManager textureManager;
extern InputManager inputManager;
extern StageManager stageManager;
extern GameStat gameStat;
extern GameSystem gameSystem;
extern CheatManager cheatManager;