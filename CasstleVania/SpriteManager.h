#pragma once
#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__
#include <map>
#include <fstream>
#include <string>
#include "pugixml-1.7\src\pugixml.hpp"
#include "Global.h"
#include "Sprite.h"

class SpriteManager {
public:
	static SpriteManager* getInstance();
	static void release();

	void loadResource();
	Sprite* getSprite(tileID id);

	RECT getSourceRect(tileID id, std::string name);
	void loadSpriteInfo(tileID id, const char* fileInfoPath);

	// release Sprite, dont release Texture, keep Texture to use in another Sprite.
	void releaseSprite(tileID id);

	// release Texture, and Sprite, only use releaseTexture if this is the last sprite.
	// - cẩn thận khi dùng hàm này. nhiều sprite có thể tham chiếu đến cùng một texture
	// - nếu release texture mà vẫn còn thể hiện nào đó tham chiếu đến thì sẽ bị lỗi.
	void releaseTexture(tileID id);	// dù dễ bị lỗi nhưng hàm này vẫn cần thiết để giải phóng texture khi không còn đối tượng nào nữa.

	~SpriteManager(void);
private:
	SpriteManager(void);
	static SpriteManager* _instance;
	std::map<tileID, Sprite*> _listSprite;
	std::map<tileID, std::map<std::string, RECT> > _sourceRectList;

	Sprite* loadXMLDoc( LPWSTR path);
};
#endif // !__SPRITEMANAGER_H__
