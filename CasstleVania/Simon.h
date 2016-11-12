#pragma once
#include "Sprite.h"
#include "d3d9.h"
#include "d3dx9.h"
class Simon : public Sprite
{
public:
	Simon();
	Simon(LPWSTR filePath, int totalFrames = 1, int cols = 1):Sprite(filePath, totalFrames, cols) {
	
	};
public:
	int flag = 1;
	bool isRun;
	int Direction = 1;
	GVector2 velocity = GVector2(0,20);
	GVector2 gravity = GVector2(0,-90);
	GVector2 position = GVector2(0,0);
	void Update(float dt);
	float timePerImage = 0.1f;
	float timeFrameStart = 0.0f;
	bool isJumping = false;
	
	void jump(GVector2 pos0, GVector2 speed0, float t0);

	GVector2 lastPos;
	GVector2 lastSpeed;


private:
	float timeJumpStart;
	float deltaTime = 10;
	int speedJump = 30;

	float timeFromStart = 0.0f;

};