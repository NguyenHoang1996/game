#include "Game.h"
#include "Global.h"
#include "Input.h"
#include "utils.h"
#include "GAudio.h"
long start = GetTickCount();

Game::Game()
{
	stage3 = new Stage3();
}

Game::~Game()
{}

int Game::Game_Init(HWND hWnd)
{
	Init_DirectInput(hWnd);
	Init_Keyboard(hWnd);
	
	g_Timer = new Timer();
	g_FPS = 60;
	simon = new Simon(L"Simon.png", 24, 8);
	simon->setPosition(400, G_GroundHeight, 1.0f);
	simon->roi = new Sprite(L"roi0.png", 1, 1);
	simon->_index = 0;
	
	return stage3->init();
}

void Game::Game_Run(HWND hWnd)
{	
	/*fpTime = curTime;
	curTime = GetCurrentTime();
	dtTime = curTime - fpTime;
	if (dtTime > 0.15f)
		dtTime = 0.15f;
	simon->Update(dtTime);
	trace("dtTime = ", dtTime);*/
	g_DeltaTime = g_Timer->Tick();
	if (g_DeltaTime > 1.0f / (float)g_FPS)
	{
		g_Timer->FreshTime();
		simon->Update(g_DeltaTime);
		Poll_Keyboard();
		/*if (GetTickCount() - start >= 60)
		{
			start = GetTickCount();
			
		}*/
		if (G_Device->BeginScene())
		{
			if (stage3 != NULL)
				stage3->draw();
			simon->render();
			simon->roi->render();
			G_Device->EndScene();
		}
	}
	G_Device->Present(NULL, NULL, NULL, NULL);
}

void Game::Game_End(HWND hWnd)
{
	stage3->release();
}