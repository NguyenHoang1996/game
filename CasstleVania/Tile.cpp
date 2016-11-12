#include "Tile.h"
#include "utils.h"

Tile::Tile(Sprite *refSprite, RECT srcRect, int id)
{
	trace("create Tile", 0);
	this->_id = id;
	this->_srcRect = srcRect;
	this->_refSprite = refSprite;

}

void Tile::draw( GVector2 position, Viewport *viewport)
{
	if (_refSprite == NULL)
	{
		trace("_refSprite is NULL",0);
		return;
	}

	_refSprite->setPosition(position);
	_refSprite->setFrameRect(this->_srcRect);
	//_refSprite->setIndex(_id - 1);
	if (viewport == NULL)
	{
		_refSprite->render();
	}
	else
	{
		_refSprite->render(viewport);
	}
}

const int& Tile::getId() const
{
	return this->_id;
}
