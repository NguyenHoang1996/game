#include "IntroScene.h"
#include "DGraphic.h"
int IntroScene::init()
{
	tileScreen = LoadTexture(L"Resources\\TileScreen\\TileScreen.png", NULL);
	_viewport = new Viewport(2048, 384, G_ScreenWidth, G_ScreenHeight);
	rect = { 0, 0, G_WindowWidth, G_WindowHeight };
	return 1;
}
void IntroScene::draw()
{
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	G_SpriteHandler->Draw(tileScreen, &rect, NULL, new D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
	G_SpriteHandler->End();
}
void IntroScene::update(float dt)
{

}
void IntroScene::updateInput(float dt)
{

}
void IntroScene::release()
{

}