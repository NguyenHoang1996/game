#include "Input.h"
#include "Global.h" 

#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80)
int Init_DirectInput(HWND hwnd)
{
	//initialize DirectInput object
	HRESULT result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&G_DirectInput,
		NULL);
	if (result != DI_OK)
		return 0;
	//initialize the mouse
	result = G_DirectInput->CreateDevice(GUID_SysMouse, &G_Mouse, NULL);
	if (result != DI_OK)
		return 0;
		//initialize the keyboard
	result = G_DirectInput->CreateDevice(GUID_SysKeyboard, &G_KeyBoard, NULL);
	if (result != DI_OK)
		return 0;
	//clean return
	return 1;
}
int Init_Mouse(HWND hwnd)
{
	//set the data format for mouse input
	HRESULT result = G_Mouse->SetDataFormat(&c_dfDIMouse);
	if (result != DI_OK)
		return 0;
	//set the cooperative level
	//this will also hide the mouse pointer
	result = G_Mouse->SetCooperativeLevel(hwnd,
		DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
		return 0;
	//acquire the mouse
	result = G_Mouse->Acquire();
	if (result != DI_OK)
		return 0;
	//give the go-ahead
	return 1;
}
int Mouse_X()
{
	return mouse_state.lX;
}
int Mouse_Y()
{
	return mouse_state.lY;
}
int Mouse_Button(int button)
{
	return BUTTON_DOWN(mouse_state, button);
}
void Poll_Mouse()
{
	G_Mouse->GetDeviceState(sizeof(mouse_state), (LPVOID)&mouse_state);
}
void Kill_Mouse()
{
	if (G_Mouse != NULL)
	{
		G_Mouse->Unacquire();
		G_Mouse->Release();
		G_Mouse = NULL;
	}
}
int Init_Keyboard(HWND hwnd)
{
	//set the data format for mouse input
	HRESULT hresult = G_KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (hresult != DI_OK)
		return 0;
	//set the cooperative level
	hresult = G_KeyBoard->SetCooperativeLevel(hwnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (hresult != DI_OK)
		return 0;
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 256; // Arbitary buffer size
	hresult = G_KeyBoard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	//acquire the mouse
	hresult = G_KeyBoard->Acquire();
	if (hresult != DI_OK)
		return 0;
	//give the go-ahead
	return 1;
}
void Poll_Keyboard()
{
	G_KeyBoard->Acquire();
	G_KeyBoard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
}
int Key_Down(int key)
{
	return (keys[key] & 0x80);
}


void Kill_Keyboard()
{
	if (G_KeyBoard != NULL)
	{
		G_KeyBoard->Unacquire();
		G_KeyBoard->Release();
		G_KeyBoard = NULL;
	}
}

//Kiểm tra xem có phím vKey vừa thả ra ko

bool g_ArrKeys[256];
bool GIsKeyRelease(G_KEY vKey)
{
	bool res = false;

	if (vKey < 0 || vKey > 255)
		return false;

	if (GetKeyState(vKey) & 0xff00)
	{
		res = false;
		g_ArrKeys[vKey] = true;
	}
	else
	{
		if (g_ArrKeys[vKey] == true)
			res = true;
		else
			res = false;

		g_ArrKeys[vKey] = false;
	}

	return res;
}

