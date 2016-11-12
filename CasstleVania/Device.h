#pragma once
#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Global.h"
#include "DGraphic.h"
/*
Device: khoi tao, quan ly DirectX, Device, Surface

*/

class Device {
public:
	~Device(void);
	static Device* getInstance();
	static void release();
	static int Init_Direct();

	void clearScreen();
	void present();
	

	LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DSURFACE9 getSurface();

private:
	static Device* _instance;
	
	Device(void);




};



#endif // !__DEVICE_H__

