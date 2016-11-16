#ifndef __GAME_H__
#define __GAME_H__
#include "Global.h"
#include "Device.h"
#include "DGraphic.h"
#include "Stage3.h"
#include "Sprite.h"
#include "Simon.h"
#include "GAudio.h"
#include "IntroScene.h"
#include "TileScreen.h"
#include "UI.h"
class Game {
private:
	Stage3 *stage3;
	Simon* simon;
	IntroScene *intro;
	TileScreen* tileScreen;
	UI* uI;
	bool isIntroFinished = false;
public:
	Game();
	~Game();

	int Game_Init(HWND hWnd);
	void Game_Run(HWND hWnd);
	void Game_End(HWND hWnd);
};

#endif // !__GAME_H__
