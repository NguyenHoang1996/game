#include "TileScreen.h"

TileScreen::TileScreen(){}

TileScreen::~TileScreen(){}

int TileScreen::init()
{

	blackBoard = new Sprite(L"Resources\\TileScreen\\TileScreen.png", 1, 1);
	blackBoard->setPosition(260, 250, 1.0f);

	return 1;
}


void TileScreen::update(float dt)
{

}
void TileScreen::draw()
{
	updateInput(1);

	if (isPressS)
	{
		this->startTimeDelay += 0.2f;
		if (this->timeToViewStageDelay <= this->startTimeDelay)
		{

			// choi game
			this->viewEnd = true;
			this->release();
			G_Device->ColorFill(G_BackBuffer, NULL, D3DXCOLOR(0, 0, 0,1.0f));
		}
	}
	else
	{

		if (G_Device->BeginScene())
		{
			if (isDisplay == false)
			{
				blackBoard->render();
				//this->isDisplay = true;
			}
			G_Device->EndScene();
			G_Device->Present(NULL, NULL, NULL, NULL);
		}
	}

}
void TileScreen::release()
{
	blackBoard->release();
	
}
void TileScreen::updateInput(float dt)
{
	if (Key_Down(DIK_S))
	{
		// start game
		blackBoard->_texture.loadFromFile(L"Resources\\TileScreen\\BlackBoard.png");
		isPressS = true;
	}
}
