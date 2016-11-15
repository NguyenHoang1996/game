
#include "Global.h"



#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

//
//GLOBAL CONSTANT
//

// tieu nun
int G_CurForm;
// tieu nun
int G_NextForm;

bool		G_IsInitedDX = false;
int			G_GameDepth;
char*		G_GameName = "Sample TH";
LPCWSTR		G_GameTitle = L"Castle Vania";
int			G_FrameRate = 60;
int			G_ColorMode;
bool		G_IsFullScreen = false;
D3DFORMAT	G_BackBufferFormat;

bool		G_HasBackgroundSound = true;
bool		G_HasEffectSound = true;

int			G_MapWidth;
int			G_MapHeight;

int			G_MaxSize;
int			G_MinSize;

RECT		G_WindowSize;
int			G_ScreenWidth = 512; //640;	//640	//1024	//1366
int			G_ScreenHeight = 384; //480;	//480	//768	//768
int			G_WindowWidth = 512;
int			G_WindowHeight = 512;

//
//GLOBAL VARIANT
//


// GRAPHIC PARAMETERS
HINSTANCE					G_hInstance;		// Handle of the game instance
HWND						G_hWnd;				// Handle of the Game Window

// DIRECT3D  PARAMETERS
LPDIRECT3D9					G_DirectX;
LPDIRECT3DDEVICE9			G_Device;
LPDIRECT3DSURFACE9			G_BackBuffer;

LPD3DXSPRITE				G_SpriteHandler;	// spriteHandler to draw texture


// INPUT PARAMETERS
LPDIRECTINPUTDEVICE8		G_Mouse;
char						keys[256];
float	fpTime = 0;
float	curTime;
float	dtTime;
Timer	*g_Timer = NULL;
float	g_DeltaTime = 0;
int		g_FPS = 0;
void SetFPS(int _FPS)
{
	g_FPS = _FPS;
}
GVector2	G_GRAVITY = GVector2(0,10);
int	G_GroundHeight = 435;

DIMOUSESTATE				mouse_state;
LPDIRECTINPUT8				G_DirectInput;		// The DirectInput object         
LPDIRECTINPUTDEVICE8		G_KeyBoard;			// The keyboard devic

