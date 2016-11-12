#include "Device.h"


Device* Device::_instance = nullptr;

Device::Device(void)
{
	G_Device = NULL;
	G_DirectX = NULL;
	G_BackBuffer = NULL;
}

int Device::Init_Direct()
{
	if (G_hWnd == NULL)
		return 0;

	// khoi tao direct
	G_DirectX = Direct3DCreate9(D3D_SDK_VERSION);
	
	D3DPRESENT_PARAMETERS	l_preParameter;

	ZeroMemory(&l_preParameter, sizeof(l_preParameter));

	l_preParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//l_preParameter.Windowed = G_hWnd.isFullScreen() ? FALSE : TRUE;
	l_preParameter.hDeviceWindow = G_hWnd;
	l_preParameter.BackBufferFormat = D3DFMT_A8R8G8B8;
	l_preParameter.BackBufferCount = 1;
	l_preParameter.BackBufferHeight = G_ScreenHeight;
	l_preParameter.BackBufferWidth = G_ScreenWidth;
	G_DirectX->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		G_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&l_preParameter,
		&G_Device);

	if (G_Device == NULL)
		return 0;
		//throw new exception("Can not create device");

	G_Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &G_BackBuffer);

	return 1; // init success!!!
}

Device* Device::getInstance()
{
	if (_instance == NULL)
		_instance = new Device();

	return _instance;
}

Device::~Device(void)
{
	if (G_DirectX != NULL)
		G_DirectX->Release();
	if (G_Device != NULL)
		G_Device->Release();
	if (G_BackBuffer != NULL)
		G_BackBuffer->Release();
}

void Device::release()
{
	delete _instance;
	_instance = NULL;
}

void Device::present()
{
	G_Device->Present(0, 0, 0, 0);
}


void Device::clearScreen()
{
	G_Device->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
}

LPDIRECT3DDEVICE9 Device::getDevice()
{
	return G_Device;
}

LPDIRECT3DSURFACE9 Device::getSurface()
{
	return G_BackBuffer;
}
