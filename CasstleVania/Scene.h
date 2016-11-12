#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include "Global.h"
#include "ViewPort.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	int virtual init() = 0;
	void virtual updateInput(float dt) = 0;
	void virtual update(float dt) = 0;
	void virtual draw() = 0;
	void virtual release() = 0;

	Viewport*  getViewport();
protected:
	Viewport* _viewport;
private:
};
#endif // !__SCENE_H__
