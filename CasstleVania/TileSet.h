#pragma once
#ifndef __TILESET_H__
#define __TILESET_H__

#include <string>
#include <vector>

#include "Global.h"
#include "Tile.h"
#include "SpriteManager.h"

#include "pugixml-1.7\src\pugixml.hpp"


class TileSet {
private:
	Sprite *_tileImage;
	int _widthtile;  // kích thước tile
	int _heighttile; // kích thước tile
	std::string _filename;
	int _columns;
	int _rows;
	std::vector<Tile*> _listTiles;

public:
	TileSet(tileID spriteId);

	int getWidthtile() const;
	void setWidthtile(const int &value);
	int getHeighttile() const;
	void setHeighttile(const int &value);

	void loadListTiles(pugi::xml_node& node);
	Sprite* getSprite();
	void draw( int id, GVector2 position, Viewport *viewport);


};
#endif // !__TILESET_H__
