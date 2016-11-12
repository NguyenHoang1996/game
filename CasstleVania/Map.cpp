﻿
#include "Map.h"
#include "utils.h"

Map::Map()
{
	_mapIndex = NULL;
	trace("create Map", 0);

}

Map::~Map()
{

}

void Map::release()
{
	//if (_mapIndex != NULL)
	//{
	//	delete[_width * _height] _mapIndex;
	//	_mapIndex = NULL;
	//}
	//_sprite->release();
	//delete _sprite;
}


void Map::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	RECT screenRectEx =
	{
		viewport->getPositionWorld().x,
		viewport->getPositionWorld().y,
		viewport->getPositionWorld().x + viewport->getWidth(),
		viewport->getPositionWorld().y - viewport->getHeight()
	};	// top lớn hơn bottom (sử dụng hệ toạ độ đề các)

	int iBegin = max(screenRectEx.left / _framewidth, 0);
	int iEnd = min(screenRectEx.right / _framewidth + 1, _mapSize.x);
	int jBegin = _mapSize.y - min(screenRectEx.top / _frameheight + 1, _mapSize.y);
	int jEnd = _mapSize.y - max(screenRectEx.bottom / _frameheight, 0);
	
	GVector2 pos;

	for (int i = iBegin; i < iEnd; i++)
	{
		for (int j = jBegin; j < jEnd; j++)
		{
			pos.x = i * _framewidth;
			pos.y = (_mapSize.y - j - 1) * _frameheight;				// nếu có viewport 
			this->_tileSet->draw( this->_mapIndex[j][i], pos, viewport);

			/*
			this->_mapIndex[j][i]: id của tile tại cột i, hàng j
			pos:
			
			*/
		}
	}
}

GVector2 Map::getWorldSize()
{
	GVector2 result;
	result.x = this->_mapSize.x * this->_framewidth;
	result.y = this->_mapSize.y * this->_frameheight;
	return result;
}

Map* Map::LoadFromFile(const std::string path, tileID spriteId)
{
	pugi::xml_document doc;

	// Mở file và đọc
	pugi::xml_parse_result result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return nullptr;
	}
	Map* map = new Map();


	/*
	Đọc dữ liệu từ element Tilesmap
	cấu trúc:
	<Tilesmap columns="1" rows="2">
	....
	</Tilesmap>
	*/
	pugi::xml_node tilemap = doc.child("Tilesmap");
	if (tilemap == NULL)
		return nullptr;
	map->_mapSize.x = getAttributeValue(tilemap, "columns").as_int();
	map->_mapSize.y = getAttributeValue(tilemap, "rows").as_int();

	// Khởi tạo mảng hai chiều.
	map->_mapIndex = new int*[int(map->_mapSize.y)];
	for (int i = 0; i < map->_mapSize.y; i++)
	{
		map->_mapIndex[i] = new int[(int)map->_mapSize.x];
	}

	/*
	Đọc ma trận id từ xml.
	Cấu trúc:
	<MatrixIndex>
	<Rows id="0"> .... <Rows>
	<Rows id="1"> .... <Rows>
	</MatrixIndex>
	*/
	pugi::xml_node matrixindex = tilemap.child("MatrixIndex");
	if (matrixindex == NULL)
		return nullptr;
	getElementMatrixIndex(matrixindex, map->_mapIndex);

	/*
	Đọc tileset từ xml.
	Cấu trúc:
	<TileSet>
	<FileName> stage1.xml </FileName>
	<Tiles>
	<Tile> ... </Tile>
	<Tile> ... </Tile>
	<Tiles>
	</TileSet>
	*/
	pugi::xml_node tileset = tilemap.child("TileSet");
	map->_tileSet = new TileSet(spriteId);
	map->_tileSet->loadListTiles(tileset);

	// Lưu lại framewidth frameheight của mỗi tile. Để phụ vụ cho việc vẽ map.
	map->_framewidth = map->_tileSet->getSprite()->getFrameWidth();
	map->_frameheight = map->_tileSet->getSprite()->getFrameHeight();

	return map;
}

void Map::getElementMatrixIndex(pugi::xml_node& node, int** matrix)
{
	/*
	Hàm này thực hiện duyệt tất cả Row của MatrixIndex
	Cấu trúc có dạng:
	<MatrixIndex>
	<Row id="0">1	1	1	6	66	..	3	3	3	3	3	3	3	3</Row>
	<Row id="1">67	63	69	72	69	..	69	72	75	76	3	3	3	3</Row>
	<Row id="2">64	60	64	60	64	..	64	60	64	60	64	60	64	60</Row>
	</MatrixIndex>
	Sau khi kết thúc hàm này ta sẽ có ma trận index đầy đủ của một tiled map.
	*/

	pugi::xml_node child = node.first_child();
	// Chuỗi giá trị từ node
	std::string indexStr;

	// Cặp giá trị [i][j] của mảng.
	int i = 0, j = 0;

	//char *temp = NULL;
	//char *pch = NULL;

	while (child != nullptr)
	{
		char *temp = NULL;
		char *pch = NULL;

		// Lấy chuỗi giá trị của một element <Row>.
		//indexStr = child.first_child().text().as_string();
		indexStr = child.text().as_string();


		// Lấy attribute Id của node Row, nó cũng là giá trị lớp thứ nhất trong mảng hai chiều.
		i = child.attribute("id").as_int();

		auto str = splitString(indexStr, '\t');
		int j = 0;

		for (std::string tmp : str)
		{
			matrix[i][j] = atoi(tmp.c_str());
			j++;
		}

		child = child.next_sibling();
		str.clear();

		
	}

}
pugi::xml_attribute Map::getAttributeValue(const pugi::xml_node& node, std::string attributename)
{
	return node.find_attribute(
		[&](pugi::xml_attribute att) -> bool
	{
		if (std::string(att.name()).compare(attributename) == 0)
			return true;
		return false;
	});
}
