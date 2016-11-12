#pragma once
#ifndef __MAP_H__
#define __MAP_H__
/*
Map là class quản lý việc vẽ map bằng tiles.

một tileset được lưu như resource hình ảnh bao gồm nhiều ô nhỏ chứa một phần nhỏ của map.
vị trí các tile được lưu như một ma trận 2 chiều trên một file text. với giá trị các phần tử trên ma trận là (index của tile + 1). 0 = no tile here

file text được load bằng phương thức init, truyền vào đường dẫn tương đối của file
hình ảnh được load như sprite thông qua sprte manager.

MOST BASIC:
khi vẽ map. ta duyệt từ đầu đến cuối _mapIndex, kiểm tra index hiện tại là gì, sau đó set index cho sprite
_sprite->setIndex(_mapIndex[i] - 1)
khi đã biết i, từ i ta xác định vị trí cần vẽ map. (Mặc định map bắt đầu ở vị trí 0,0 và phát triển theo hệ toạ độ đề các)
pos.x =	i % * _framewidth;
pos.y = (_height - i / _width) * _frameheight;						// nếu có viewport thì dùng height - i / widht để lật toạ độ
//pos.y = (i / _width) * (_frameheight - 1);						// không có viewport
_sprite->setPosition(pos);

UPGRADE LEVEL 1:
duyệt mảng từ 0 đến _widht * _height có thể phát sinh đển hàng ngàn lần vẽ
ta giới hạn lại số lần vẽ bằng cách check nếu position vẽ nằm ngoài màn hình thì không vẽ
PSEDUE CODE:
for int i : _widht * _height
if (bound.right < screenRect.left)
	continue;
if (bound.bottom > screenRect.top)
	continue;
if (bound.left > screenRect.right)
	continue;
if (bound.top < screenRect.bottom)
	continue;
draw here


*/
#include <vector>
#include <string>
#include "pugixml-1.7\src\pugixml.hpp"
#include "Global.h"
#include "TileSet.h"

class Map {

public:

	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	/*
	Load dữ liệu từ một file xml.
	path: file tiledmap xml được định nghĩa cấu trúc sẵn.
	eID: sprite id được đăng kí ở sprite manager.
	*/
	static Map* LoadFromFile(const std::string path, tileID spriteId);

	/*
	Lấy kich thước map.
	*/
	GVector2 getWorldSize();
	Map();
	~Map();

private:

	int _framewidth;	// độ rộng một frame (độ rộng của tile)
	int _frameheight;	// độ cao một frame (độ cao của tile)

						// Kích thước map tính theo số ô Tile.
	GVector2 _mapSize;

	// Ma trận Tile id.
	// Id trong ma trận này được so sánh với Id của Tile trong TileSet.listTile
	int** _mapIndex;

	// Chứa list tile.
	TileSet* _tileSet;

	/*
	[Function Helper]
	Lấy thông tin một attribute từ một node. Sử dụng pugi framework
	node: một element chứa attribute cần tìm.
	attributename: tên của attribute muốn tìm.
	*/
	static pugi::xml_attribute getAttributeValue(const pugi::xml_node& node, std::string attributename);

	/*
	[Function Helper]
	Đọc dữ liệu một mảng tile id
	node: một element chứa mảng id cần tìm.
	matrix: tham chiếu đến ma trận index.
	*/
	static void  getElementMatrixIndex(pugi::xml_node& node, int** matrix);


};
#endif // !__MAP_H__
