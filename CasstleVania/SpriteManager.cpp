#include "utils.h"

/*
HOW TO USE:
spritemanager is basic class to manage load and release sprite and texture.
It load all image you have, if you want to use sprite any where, just getSprite from SpriteManager.
if you dont want you use this image any more, you can call release.

everytime use this, you have to call SpriteManager::getInstance() first.
this is Singleton format.
Seemore about Singleton: http://www.stdio.vn/articles/read/224/singleton-pattern

you can call directly: SpriteManager::getInstance()->DOSOMETHING()
or reference it:
SpriteManager* _spritemanager;
...
_spritemanager = SpriteManager::getInstance();
...
_spritemanager->DOSOMETHING()

Next, you should call loadresource(LPD3DXSPRITE spriteHandle) in Game::loadresource().
It will load all your image from file to memory.
Remember: Insert your code to loadresource to load image from file.

If you want object reference to Sprite. call:
SpriteManager::getInstance()->getSprite(tileID::OBJECT_ID)
what is tileID::OBJECT_ID ?
in define.h you can insert element to tileID.

OK. Now you have sprite to draw.

If you dont want to use this sprite any more, call releaseSprite or releaseTexture
they often are called in object::release

Call SpriteManager::release() in game:release() to clean all memory.
*/
#include "SpriteManager.h"


SpriteManager* SpriteManager::_instance = nullptr;
SpriteManager::SpriteManager(void)
{
	// do nothing.
}

SpriteManager::~SpriteManager(void)
{
	for (auto spr = _listSprite.begin(); spr != _listSprite.end(); ++spr)
	{
		spr->second->release();		// release image
		delete spr->second;			// delete sprite
	}
	if (_listSprite.empty() == false)
		_listSprite.clear();		// remove all from MAP
}

void SpriteManager::loadResource()
{
	trace("load resoure in sprite manager", 0);
	/* if you have any image, load them with this format */
	// [psedue code]
	// sp = new SPRITE(...)
	// this->_listSprite.insert(pair<tileID, Sprite*>(tileID::ENUMOBJECT, sp));

	//Sprite* sp = new Sprite(spriteHandle, L"Flower.png", 4, 4);
	//this->_listSprite.insert(pair<tileID, Sprite*>(tileID::FLOWER, sp));

	//sp = new Sprite(spriteHandle, L"mario.png", 5, 5);
	//this->_listSprite.insert(pair<tileID, Sprite*>(tileID::MARIO, sp));

	Sprite* sp = NULL;

	/*sp = new Sprite( L"Resources//Images//Soldier.png");
	this->_listSprite.insert(std::pair<tileID, Sprite*>(tileID::SOLDIER, sp));
	this->loadSpriteInfo(tileID::SOLDIER, "Resources//Images//soldier_animation.txt");

	sp = new Sprite( L"Resources//Images//Falcon.png");
	this->_listSprite.insert(std::pair<tileID, Sprite*>(tileID::FALCON, sp));
	this->loadSpriteInfo(tileID::FALCON, "Resources//Images//falcon_animation.txt");

	sp = new Sprite( L"Resources//Images//Cannon_all.png", 15, 5);
	//this->_listSprite.insert(pair<eID, Sprite*>(eID::REDCANON, sp));
	this->_listSprite[tileID::REDCANNON] = sp;
	this->loadSpriteInfo(tileID::REDCANNON, "Resources//Images//cannon_animation.txt");


	sp = new Sprite( L"Resources//Images//wall_turret_all.png", 42, 9);
	this->_listSprite[tileID::WALL_TURRET] = sp;
	this->loadSpriteInfo(tileID::WALL_TURRET, "Resources//Images//Wall_turret_animation.txt");



	sp = new Sprite( L"Resources//Images//aircraft.png", 10, 10);
	this->_listSprite[tileID::AIRCRAFT] = sp;
	this->loadSpriteInfo(tileID::AIRCRAFT, "Resources//Images//aircraft_animation.txt");

	sp = new Sprite( L"Resources//Images//falcon.png", 7, 7);
	this->_listSprite[tileID::FALCON] = sp;
	this->loadSpriteInfo(tileID::FALCON, "Resources//Images//falcon_animation.txt");

	sp = new Sprite( L"Resources//Images//explosion.png");
	this->_listSprite[tileID::EXPLOSION] = sp;
	this->loadSpriteInfo(tileID::EXPLOSION, "Resources//Images//explosion_animation.txt");


	Sprite* bill = new Sprite( L"Resources//Images//bill_animation.png");
	this->_listSprite[tileID::BILL] = bill;
	this->loadSpriteInfo(tileID::BILL, "Resources//Images//bill_animation.txt");

	sp = new Sprite( L"Resources//Images//rifleman.png");
	this->_listSprite[tileID::RIFLEMAN] = sp;
	this->loadSpriteInfo(tileID::RIFLEMAN, "Resources//Images//rifleman_animation.txt");

	sp = new Sprite( L"Resources//Images//boss_stage1.png");
	this->_listSprite[tileID::BOSS_STAGE1] = sp;
	this->loadSpriteInfo(tileID::BOSS_STAGE1, "Resources//Images//boss_stage1_animation.txt");

	sp = new Sprite( L"Resources//Images//bridge.png", 6, 3);
	this->_listSprite[tileID::BRIDGE] = sp;

	auto bl = new Sprite( L"Resources//Images//Bullets.png");
	this->_listSprite[tileID::BULLET] = bl;
	this->loadSpriteInfo(tileID::BULLET, "Resources//Images//bullets_type.txt");

	sp = new Sprite( L"Resources//Images//stage3_elements.png", 5, 5);
	this->_listSprite[tileID::ROCKFLY] = sp;
	this->loadSpriteInfo(tileID::ROCKFLY, "Resources//Images//rockfly_animation.txt");

	this->_listSprite[tileID::SHADOW_ARM] = sp;
	this->loadSpriteInfo(tileID::SHADOW_ARM, "Resources//Images//shadowarm_animation.txt");


	sp = new Sprite( L"Resources//Images//Life.png");
	this->_listSprite[tileID::LIFE_ICON] = sp;
	this->loadSpriteInfo(tileID::LIFE_ICON, "Resources//Images//life_info.txt");

	sp = new Sprite( L"Resources//Images//boss_stage3.png");
	this->_listSprite[tileID::SHADOW_MOUTH] = sp;
	this->loadSpriteInfo(tileID::SHADOW_MOUTH, "Resources//Images//shadowbeast_animation.txt");

	sp = new Sprite( L"Resources//Images//ScubaSoldier.png");
	this->_listSprite[tileID::SCUBASOLDIER] = sp;
	this->loadSpriteInfo(tileID::SCUBASOLDIER, "Resources//Images//scubasoldier_animation.txt");

	sp = new Sprite( L"Resources//Images//fire.png");
	this->_listSprite[tileID::FIRE] = sp;
	this->loadSpriteInfo(tileID::FIRE, "Resources//Images//fire_animation.txt");

	sp = new Sprite( L"Resources//Images//rockfall.png", 4, 4);
	this->_listSprite[tileID::ROCKFALL] = sp;
	this->loadSpriteInfo(tileID::ROCKFALL, "Resources//Images//rockfall_animation.txt");

	sp = new Sprite( L"Resources//Fonts//fontEx.png", 30, 10);
	this->_listSprite[tileID::FONTEX] = sp;

	sp = new Sprite( L"Resources//Fonts//fontFull.png", 54, 6);
	this->_listSprite[tileID::FONTFULL] = sp;

	sp = new Sprite( L"Resources//Images//BeginState3.png");
	this->_listSprite[tileID::BEGIN_STAGE3] = sp;

	sp = new Sprite( L"Resources//Images//GameOver.png");
	this->_listSprite[tileID::GAME_OVER_SCENE] = sp;

	sp = new Sprite( L"Resources//Images//blank.png");
	this->_listSprite[tileID::BLANK] = sp;

	sp = new Sprite( L"Resources//Images//intro.png");
	this->_listSprite[tileID::MENU] = sp;

	sp = new Sprite( L"Resources//Images//yellowfalcon.png");
	this->_listSprite[tileID::YELLOWFALCON] = sp;

	sp = new Sprite( L"Resources//Images//tuts_layer.png");
	this->_listSprite[tileID::TUT_LAYER] = sp;

	// Đọc file xml để tạo đối tượng sprite
	sp = loadXMLDoc(L"Resources//Map//stage1.xml");
	sp->setOrigin(VECTOR2ZERO);
	this->_listSprite[tileID::MAPSTAGE1] = sp;
	*/
	sp = loadXMLDoc( L"Resources//Map//stage3.xml");
	sp->setOrigin(VECTOR2ZERO);
	this->_listSprite[tileID::MAPSTAGE3] = sp;
	
	sp = loadXMLDoc(L"Resources//Map//stage4.xml");
	sp->setOrigin(VECTOR2ZERO);
	this->_listSprite[tileID::MAPSTAGE4] = sp;
}

Sprite* SpriteManager::loadXMLDoc( LPWSTR path)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path, pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		OutputDebugString(L"Khong tim thay file xml");
		return nullptr;
	}
	pugi::xml_node root = doc.first_child();
	pugi::xml_node tileset_node = root.child("TileSet");
	// Tìm tên file.
	// Cắt từ chuỗi path ra để tìm thư mục.
	// Sau đó ghép với tên file ảnh được lấy từ file xml để load ảnh.
	std::string filename = tileset_node.attribute("FileName").as_string();   // get filename from xml node
	std::wstring L_filename = std::wstring(filename.begin(), filename.end());		// convert to wstring.

	std::wstring strpath = std::wstring(path);									// convert to wstring.
	int index = strpath.find_last_of(L'//');							// cut to find path
	strpath = strpath.substr(0, index);
	strpath += L"/" + L_filename;										// concat string.  Final string is strpath.
																		// Tìm số dòng
	int rows = tileset_node.attribute("Rows").as_int();
	int columns = tileset_node.attribute("Columns").as_int();
	return new Sprite( (LPWSTR)strpath.c_str(), rows * columns, columns);
}
Sprite* SpriteManager::getSprite(tileID id)
{
	if (this->_listSprite.size() == 0)
	{
		loadResource();
	}
	Sprite *it = this->_listSprite.find(id)->second;
	
	return new Sprite(*it);			// get the copy version of Sprite
}

RECT SpriteManager::getSourceRect(tileID id, std::string name)
{
	//return _sourceRectList[id].at(name);
	return _sourceRectList[id][name];
}

void SpriteManager::loadSpriteInfo(tileID id, const char* fileInfoPath)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	if (file)
	{
		while (!feof(file))
		{
			RECT rect;
			char name[100];
			fgets(name, 100, file);

			fscanf(file, "%s %d %d %d %d", &name, &rect.left, &rect.top, &rect.right, &rect.bottom);

			_sourceRectList[id][std::string(name)] = rect;
		}
	}

	fclose(file);
}

void SpriteManager::releaseSprite(tileID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	delete it;							// delete the sprite only, dont relase image
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
void SpriteManager::releaseTexture(tileID id)
{
	Sprite *spr = this->_listSprite.find(id)->second;
	spr->release();						// release image
	delete spr;
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
SpriteManager* SpriteManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new SpriteManager();
	return _instance;
}

void SpriteManager::release()
{
	delete _instance;			// _instance is static attribute, only static function can delete it.
	_instance = nullptr;
}
