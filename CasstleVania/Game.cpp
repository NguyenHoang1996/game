#include "Game.h"
#include "Global.h"
#include "Input.h"
#include "utils.h"
#include "GAudio.h"
#include "IntroScene.h"
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


	//init 
	tileScreen = new TileScreen();
	tileScreen->init();
	
	g_Timer = new Timer();
	g_FPS = 60;
	stage3->init();
	simon = new Simon(L"Simon.png", 24, 8);
	simon->setPosition(400, G_GroundHeight, 1.0f);
	simon->roi = new Sprite(L"roi0.png", 1, 1);
	simon->_index = 0;
	
	return 1;
}

void Game::Game_Run(HWND hWnd)
{

	g_DeltaTime = g_Timer->Tick();
	if (g_DeltaTime > 1.0f / (float)g_FPS)
	{
		g_Timer->FreshTime();
		Poll_Keyboard();
		//simon->roi->render();
		if (isIntroFinished == false){
			tileScreen->draw();
			if (tileScreen->viewEnd)
			{
				tileScreen = NULL;
				isIntroFinished = true;
			}
		}
		else if (isIntroFinished){
			simon->Update(g_DeltaTime);
			if (G_Device->BeginScene())
			{
				if (stage3 != NULL)
					stage3->draw();
				simon->render();
				G_Device->EndScene();
			}
		}

		G_Device->Present(NULL, NULL, NULL, NULL);
		/*if (tileScreen->viewEnd){
			simon->Update(g_DeltaTime);
			if (G_Device->BeginScene())
			{
			stage3->draw();
			simon->render();
			G_Device->EndScene();
			}
			G_Device->Present(NULL, NULL, NULL, NULL);
			}
			else{
			tileScreen->draw();
			}*/
	}
}
void Game::Game_End(HWND hWnd)
{
	stage3->release();
}

