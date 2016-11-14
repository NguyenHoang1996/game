#include "Stage3.h"
#include "utils.h"

Stage3::Stage3()
{

}

Stage3::~Stage3()
{
	delete _viewport;
	_viewport = nullptr;
}

void Stage3::setViewport(Viewport* viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

int Stage3::init()
{
	trace("init game",0);
	background = Map::LoadFromFile("Resources//Map//stage4.xml", tileID::MAPSTAGE4);
	_viewport = new Viewport( 3200, 600, G_ScreenWidth, G_ScreenHeight);
	this->musicStage3.Init_DirectSound(G_hWnd);
	this->musicStage3.LoopSound(this->musicStage3.LoadSound(L"Resources\\Sounds\\music\\Stage4.wav"));
	return 1;
}

void Stage3::draw()
{
	//trace("draw", 0);
	background->draw(G_SpriteHandler, _viewport);
}

void Stage3::release()
{
	background->release();
}

void Stage3::update(float dt)
{

}

void Stage3::updateInput(float dt)
{

}
void Stage3::ChayAmThanh()
{
	
}