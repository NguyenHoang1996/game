#pragma once
#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__

#include "Global.h"
#include "Scene.h"
#include "GAudio.h"
#include "Map.h"
#include "d3d9.h"
#include "d3dx9.h"
class IntroScene : public Scene {
public:
	int init() override;
	void draw() override;
	void release() override;
	void updateInput(float dt) override;
	void update(float dt) override;
	GAudio	musicScene;
public:
	//IntroScene();
	//~IntroScene();
	LPDIRECT3DTEXTURE9	tileScreen;
	RECT rect;
	LPDIRECT3DTEXTURE9	bat;

};
#endif // !__INTROSCENE_H__
