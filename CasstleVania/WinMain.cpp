#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include "DGraphic.h"
#include <stdio.h>
#include "Global.h"
#include "Game.h"
#include "utils.h"

RECT wr = { 0, 0, G_WindowWidth	,G_WindowHeight };

Game* game = new Game();

/*Window event callback function*/
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		/*Release the Direct3D device*/
		if (G_Device != NULL)
			G_Device->Release();
		/*Release the Direct3D object*/
		if (G_DirectX != NULL)
			G_DirectX->Release();
		/*Call the "Front-end" shutdown function*/
		game->Game_End(G_hWnd);
		/*Tell the windows to kill this program*/
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*Helper function to set up the window properties*/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	/*Fill the struct with info*/
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = G_GameTitle;
	wc.lpszMenuName = NULL;

	/*Set up the window with the class info*/
	return RegisterClassEx(&wc);

}

/*Entry point for a Windows program*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	DWORD frame_start = GetTickCount();
	int _FrameRate = 60;
	DWORD tick_per_frame = 1000 / _FrameRate;

	/*Register the class*/
	MyRegisterClass(hInstance);

	/*Set up the screen in windowed or fullscreen mode*/

	G_hWnd = CreateWindow(
		G_GameTitle,
		G_GameTitle,
		WS_OVERLAPPEDWINDOW,	
		360,
		150,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	/*Was there an error creating the window*/
	if (!G_hWnd)
	{
		return FALSE;
	}

	/*Display the window*/
	ShowWindow(G_hWnd, nCmdShow);
	UpdateWindow(G_hWnd);

	if (Init_Direct3D(G_hWnd, wr.right - wr.left, wr.bottom - wr.top) == 0)
	{
		return 0;
	}

	/*Initialize the game*/
	if (!game->Game_Init(G_hWnd))
	{
		MessageBox(G_hWnd, L"Error initializing the game.", L"Error", MB_OK);
		return 0;
	}

	/*Main message loop*/
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/*Look for quit message*/
			if (msg.message == WM_QUIT)
				done = 1;
			/*Decode and pass message to the WndProc*/
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		/*Process game loop (prevents running after window is closed)*/
		game->Game_Run(G_hWnd);
	}
	return msg.wParam;
}
	