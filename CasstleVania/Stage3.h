#pragma once
#ifndef __STAGE3_H__
#define __STAGE3_H__

#include "Global.h"
#include "Scene.h"

#include "Map.h"

class Stage3 : public Scene {
public:
	Stage3();
	~Stage3();

	void setViewport(Viewport* viewport);

	// override parent methods
	int init() override;
	void updateInput(float dt) override;
	void update(float dt) override;
	void draw() override;
	void release() override;


private:
	Map *background;



};
#endif // !__STAGE3_H__
