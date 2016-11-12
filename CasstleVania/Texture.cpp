#include "Texture.h"
#include "utils.h"

Texture::Texture()
{
	trace("create Texture", 0);
}

Texture::~Texture()
{
}

void Texture::release()
{
	this->_texture->Release();
}

HRESULT Texture::loadFromFile( LPWSTR filePath, D3DXCOLOR color, D3DXCOLOR colorkey)
{
	if (G_Device == NULL || G_SpriteHandler == NULL)
		return 0;


	HRESULT			result;

	result = D3DXGetImageInfoFromFile(filePath, &this->_imageInfo);
	if (result != D3D_OK)
	{
		return result;
	}

	G_SpriteHandler->GetDevice(&G_Device);

	result = D3DXCreateTextureFromFileEx(
		G_Device,
		filePath,
		this->_imageInfo.Width,
		this->_imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorkey,
		&this->_imageInfo,
		nullptr,
		&this->_texture);

	_color = color;

	return result;
}

void Texture::render( const RECT * rect, const GVector3 * center, const GVector3 * position)
{
	G_SpriteHandler->Draw(
		this->_texture,
		rect,
		center,
		position,
		_color);
}

void Texture::render( RECT * srcRect, GVector2 position, GVector2 scale, float rotate, GVector2 origin, float zIndex)
{
	D3DXMATRIX matFinal;
	D3DXMATRIX matTransformed;
	D3DXMATRIX matOld;

	// origin in position
	GVector3 center = GVector3(abs(srcRect->right - srcRect->left) * origin.x, abs(srcRect->top - srcRect->bottom) * (1 - origin.y), zIndex);

	// get matrix texture
	G_SpriteHandler->GetTransform(&matOld);

	D3DXMatrixTransformation2D(
		&matTransformed,						// ma tran ket qua sau transform
		&position,								// goc toa do / diem neo
		0.0f,
		&scale,									// ti le scale
		&position,								// goc toa do / diem neo
		D3DXToRadian(rotate),					// góc xoay theo radian
		0										// vi trí
	);

	matFinal = matTransformed * matOld;

	//set matrix transformed
	G_SpriteHandler->SetTransform(&matFinal);

	// BEGIN
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE);

	G_SpriteHandler->Draw(
		this->_texture,
		srcRect,
		&center,
		&GVector3(position.x, position.y, zIndex),
		_color);

	G_SpriteHandler->SetTransform(&matOld);

	// END
	G_SpriteHandler->End();
}

void Texture::render( RECT * srcRect, Viewport viewport, GVector2 position, GVector2 scale, float rotate, GVector2 origin, float zIndex)
{
	GVector3 positionViewport;
	positionViewport = viewport.getPositionInViewport(&GVector3(position.x, position.y, zIndex));
	// ver 05/10/2015 - 7ung : ép kiêu về int. để tránh trường hợp bị hụt pixel 
	render(srcRect, GVector2((int)positionViewport.x, (int)positionViewport.y), scale, rotate, origin, positionViewport.z);

}

void Texture::setColor(D3DXCOLOR color)
{
	this->_color = color;
}

D3DXCOLOR Texture::getColor()
{
	return _color;
}

int Texture::getWidth()
{
	return _imageInfo.Width;
}

int Texture::getHeight()
{
	return _imageInfo.Height;
}