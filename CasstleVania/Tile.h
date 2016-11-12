#pragma once
#ifndef __TILE_H__
#define __TILE_H__
#include "Global.h"
#include "Sprite.h"

class Tile {
private:
	int _id;
	RECT _srcRect;

	Sprite* _refSprite; // ảnh gồm nhiều tile. khi vẽ cắt bằng srcRect như Sprite

public:

	const int &getId() const;

	Tile(Sprite *refSprite, RECT srcRect, int id);
	void draw(GVector2 position, Viewport *viewport = NULL);





};


#endif // !__TILE_H__

