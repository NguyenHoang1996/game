#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "Sprite.h"

class Animation
	{
	private:
		float waitNextImage; //Chờ chuyển hình
		int widthOfFrame; //Chiều rộng
		int heightOfFrame; //Chiều cao
		int numImageInRow; //Số hình trên một hàng
		int numImageInColumn; //Số hình trên một cột

	public:
		int index; //Chỉ số hình
		float timePerImage; //Thời gian chuyển hình
		RECT rect; //Hình chữ nhật trong hình
		Animation();
		Animation(int _numImageInRow, int _numImageInColumn, float _timePerImage, Sprite*
			sprite);
		~Animation();
		void Update(int indexFirstImage, int indexLastImage, float TPF);
};