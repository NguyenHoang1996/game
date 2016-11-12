
#ifndef _GLOBAL_H_
#define _GLOBAL_H_


#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Timer.h"
//GLOBAL CONSTANT

//view mode(used in contructor of game class)
#define GL_RESOLUTION_640_480_24	0
#define GL_RESOLUTION_800_600_24	1
#define GL_RESOLUTION_1024_768_24	2
//
#define GL_RESOLUTION_640_480_32	10
#define GL_RESOLUTION_800_600_32	11
#define GL_RESOLUTION_1024_768_32	12
#define FULLSCREEN 640;
//
//size of key buffer(used in game class to save key state
#define GL_KEY_BUFFER_SIZE	1024

//
//GLOBAL VARIANT
//

extern int G_CurForm;
extern int G_NextForm;

extern bool			G_IsInitedDX;		//check if dx is inited
extern int			G_GameDepth;		//depth in game class (i dont know
extern char*		G_GameName;		//name of game, view in caption
extern LPCWSTR		G_GameTitle;		//name of game, view in caption
extern int			G_FrameRate;		//frame rate(30 -> 60)
extern int			G_ColorMode;		//color mode to init dx
extern bool			G_IsFullScreen;	//check if windows or fullscreen
extern D3DFORMAT	G_BackBufferFormat;//backbuffer format, used in initing dx

extern bool			G_HasBackgroundSound;		//check if background music is on
extern bool			G_HasEffectSound;	//check if sound effect is on

extern int			G_MapWidth;			//count the tiles in map width, 1 tile 50px
extern int			G_MapHeight;			//count the tiles in map height, 1 tile 50px

extern int			G_ScreenWidth;			//width of game screen
extern int			G_ScreenHeight;			//height of game screen

extern int			G_MaxSize;
extern int			G_MinSize;

extern RECT			G_WindowSize;			//size of game screen

extern HINSTANCE					G_hInstance;		// Handle of the game instance
extern HWND							G_hWnd;			// Handle of the Game Window

extern LPDIRECT3D9					G_DirectX;			//handle dx
extern LPDIRECT3DDEVICE9			G_Device;			//dx device
extern LPDIRECT3DSURFACE9			G_BackBuffer;		//backbuffer

extern LPD3DXSPRITE					G_SpriteHandler;	// spriteHandler to draw texture
extern LPDIRECTINPUTDEVICE8			G_Mouse;
extern char							keys[256];

extern	float	fpTime;
extern	float	curTime;
extern	float	dtTime;
extern float	g_DeltaTime ;
extern int		g_FPS ;
extern Timer	*g_Timer ;



extern DIMOUSESTATE					mouse_state;
extern LPDIRECTINPUT8				G_DirectInput;		// The DirectInput object         
extern LPDIRECTINPUTDEVICE8			G_KeyBoard;			// The keyboard devic

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;


extern	GVector2	G_GRAVITY;	// trọng lực
extern	int	G_GroundHeight;		// chiều cao của land

#define VECTOR2ZERO GVector2(0.0f, 0.0f)
#define VECTOR2ONE  GVector2(1.0f, 1.0f)

enum tileID
{
	BILL = 0,			// Main character.
	REDCANNON = 1,
	SOLDIER = 2,
	FALCON = 3,
	AIRCRAFT = 4,
	EXPLOSION = 5,
	RIFLEMAN = 6,
	BRIDGE = 7,
	QUADEXPLODE = 8,
	MAPSTAGE1 = 9,
	BULLET = 10,
	WALL_TURRET = 11,
	LAND = 12,				// Đất đi được.
	CREATOR = 13,

	// Từ 14 đến 16 dùng cho intro
	BLANK = 14,
	MENU = 15,
	YELLOWFALCON = 16,

	ITEM = 17,
	BOSS_STAGE1 = 18,
	BOSS_GUN = 19,
	BOSS_SHIELD = 20,
	ROCKFLY = 21,
	LIFE_ICON = 22,

	FIRE = 25,
	ROCKFALL = 26,

	BEGIN_STAGE3 = 27,
	GAME_OVER_SCENE = 28,
	SCUBASOLDIER = 29,
	FONTEX = 30,
	FONTFULL = 31,
	MAPSTAGE3 = 32,
	ROCKCREATOR = 33,
	SHADOW_BEAST = 34,
	SHADOW_ARM = 35,
	SHADOW_MOUTH = 36,
	TUT_LAYER = 37,

	MAP_STAGE4 = 38,
	MAPSTAGE4 = 39
};

//Keys
typedef enum G_KEY
{
	KEY_X = 0x58,
	KEY_Z = 0x5A,
	KEY_LEFT = VK_LEFT,
	KEY_RIGHT = VK_RIGHT,
	KEY_DOWN = VK_DOWN,
	KEY_ESC = VK_ESCAPE
} G_KEY;

//GLOBAL METHOD



#endif