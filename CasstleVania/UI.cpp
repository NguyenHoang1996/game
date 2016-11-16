#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void UI::CreateFontUI()
{
	font = NULL;
	HRESULT hr = D3DXCreateFont(G_Device, 22, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"emulogic", &font);
	fRectangle1 = { 280, 20, 350, 70 };
}
void UI::WriteFont(int i)
{
	itoa(i,time,10);
	messageFront = time;
	if (font)
	{
		font->DrawTextA(NULL, this->messageFront.c_str(), -1, &fRectangle1, DT_LEFT, D3DCOLOR_XRGB(255, 255,255));
		return;
	}
}