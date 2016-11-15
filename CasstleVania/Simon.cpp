#include "Simon.h"
#include "Input.h"
#include "utils.h"
void Simon::Update(float dt)
{
	
	if (!isJumping && Key_Down(DIK_LEFT))	// go to left
	{
		
		this->Direction = 1;

		this->velocity.x = -20;
		this->_position.x -= 2;

		this->timeFrameStart += dt;
		if (this->timeFrameStart >= this->timePerImage)
		{
			this->timeFrameStart = 0.0f;

			if (this->_index >= 24) {
				this->_index = 0;
			}
			else if (this->_index >= 3)
			{
				this->_index = 0;
			}
			else
			{
				this->_index++;
			}
			this->setScaleX(1);
			this->setIndex(this->_index);
			//this->_currentFrame;
			



		}
		trace("current frame = ", this->_index);
	}
	if (!isJumping && Key_Down(DIK_RIGHT))	// go to left
	{

		this->Direction = -1;

		this->velocity.x = 20;
		this->_position.x += 2;

		this->timeFrameStart += dt;
		if (this->timeFrameStart >= this->timePerImage)
		{
			this->timeFrameStart = 0.0f;

			if (this->_index >= 24) {
				this->_index = 0;
			}
			else if (this->_index >= 3)
			{
				this->_index = 0;
			}
			else
			{
				this->_index++;
			}
			this->setScaleX(-1);
			this->setIndex(this->_index);

		}
		trace("current frame = ", this->_index);
	}

	//if (!isJumping && Key_Down(DIK_RIGHT))	// go to right
	//{
	//	this->Direction = -1;
	//	this->velocity.x = 20;

	//	this->timeFrameStart += dt;
	//	if (this->timeFrameStart >= this->timePerImage)
	//	{
	//		this->timeFrameStart = 0.0f;

	//		if (this->_index <= 24) {
	//			this->_index = 28;
	//		}
	//		else if (this->_index >= 31)
	//		{
	//			this->_index = 28;
	//		}
	//		else
	//		{
	//			this->_index++;
	//		}
	//		this->setIndex(this->_index);
	//		this->_currentFrame;
	//	}

	//	
	//	this->_position.x += 3;
	//}
	if (this->flag == 0)
	{
		this->_index = 0;
		this->setIndex(this->_index);
		this->_currentFrame;
		this->flag = 1;
	}
	if (!isJumping && Key_Down(DIK_DOWN))  // sit
	{
		this->flag = 0;
		if (this->Direction == 1)
		{
			this->_index = 4;
			this->setScaleX(1);
		}
		else if (this->Direction == -1)
		{
			this->_index = 4;
			this->setScaleX(-1);
		}
		this->setIndex(this->_index);
		this->_currentFrame;
	}

	// right release
	if( GIsKeyRelease(G_KEY::KEY_RIGHT) || GIsKeyRelease(G_KEY::KEY_LEFT))
	{
		this->velocity.x = 0;
		if (this->Direction == 1)
		{
			this->_index = 0;
			this->setScaleX(1);
			this->setIndex(this->_index);
		}
		else if (this->Direction == -1)
		{
			this->_index = 0;
			this->setScaleX(-1);
			this->setIndex(this->_index);
		}
	}
	

	if ( Key_Down(DIK_X)) // jump
	{
		clock_t start = clock();
		if (this->Direction == 1)
		{
			this->_index = 4;
			this->setScaleX(1);
		}
		else if (this->Direction == -1)
		{
			this->_index = 4;
			this->setScaleX(-1);
		}
		/*this->_position.y = this->_position.y+ this->velocity.y*dtTime;
		this->velocity.y= this->velocity.y + this->gravity.y*dtTime;
		this->setIndex(this->_index);
		this->_currentFrame;*/
		
		if (!this->isJumping) // Only jump if it is not yet currently jumping
		{
			
			timeJumpStart = 0;
			this->timeFromStart = 0.0f;

			lastPos = this->_position;
			lastSpeed= this->velocity;

			lastSpeed.y += this->speedJump;
			lastSpeed.y += this->velocity.y;
			this->isJumping = true;
		}
	}

	// jump
	if (this->isJumping)
	{
		// chuyển frame
		this->setIndex(this->_index);
		this->_currentFrame;

		this->timeFromStart += 8 * dt;

		// jump
		// deltaY = - G_GRAVITY.y * deltaTime * deltaTime + lastSpeed.y * deltaTime;  // tuong duong voi phuong trinh: -2X^2 + 50X
		// - gravity  * X^2  +   speed * X
		// -2 X^2  + 90X
		this->_position.y = lastPos.y - (- G_GRAVITY.y * this->timeFromStart * this->timeFromStart + lastSpeed.y * this->timeFromStart);
		this->_position.x = lastPos.x + lastSpeed.x * this->timeFromStart;
		trace("JUMPINGggggggggggg\npos x = ",this->velocity.x);

		/*trace("this->timeFromStart =				 ", this->timeFromStart);
		trace("speed0 * t =		 ", lastSpeed.y * this->timeFromStart);
		trace("Gravity * t * t = ", G_GRAVITY.y * this->timeFromStart * this->timeFromStart);
		trace("last pos y =			 ", lastPos.y);
		trace("pos y =			 ", _position.y);
		*/
		/*if (this->_position.y + G_GRAVITY.y*4 < lastPos.y  )
		{
			if (this->Direction == 1)
			{
				this->_index = 0;
				this->setScaleX(1);

			}
			else if (this->Direction == -1)
			{
				this->_index = 0;
				this->setScaleX(-1);
			}
		}*/
		deltaTime += 2;

		// Kiểm tra xem simom quat trở lại mặt đất chưa?
		if (this->_position.y > G_GroundHeight)
		{
			this->_position.y = G_GroundHeight;
			this->isJumping = false;
			this->deltaTime = 10;
			this->timeFromStart = 0;
			if (this->Direction == 1)
			{
				this->_index = 0;
				this->setScaleX(1);

			}
			else if (this->Direction == -1)
			{
				this->_index = 0;
				this->setScaleX(-1);
			}
			this->setIndex(this->_index);
			// sau khi nhảy xong sẽ lại frame đầu ( t k biết làm)
			// phải xét hướng trái hoặc phải trước khi nhảy để sau khi nhảy nó đứng đúng hướng đó
			//......
		}

	}
	if (!this->isJumping && Key_Down(DIK_Z))
	{
		
				if (this->Direction == 1)
				{
					this->roi->setPosition(this->_position.x + 67, this->_position.y + 10, 1.0f);
					this->roi->setScaleX(1);
					this->timeFrameStart += dt;
					if (this->timeFrameStart >= this->timePerImage)
					{
						this->timeFrameStart = 0.0f;
						if (this->_index < 5)
						{
							this->_index = 5;
						}else if (this->_index >= 7)
						{
							this->_index = 5;
							this->roi->_texture.loadFromFile(L"roi3.png");
							this->roi->render();
						}
						else 
						{
							this->_index++;
							this->roi->_texture.loadFromFile(L"roi1.png");
							this->roi->render();
						}
					}
					this->setIndex(this->_index);
					this->setScaleX(1);
				}
				else
				{
					this->roi->setPosition(this->_position.x - 67, this->_position.y + 10, 1.0f);
					this->roi->setScaleX(-1);
					this->_index = 5;
					this->setIndex(this->_index);
					this->setScaleX(-1);
				}
	}
}

void Simon::jump(GVector2 pos0, GVector2 speed0, float t0)
{
	/*float now = GetCurrentTime();

	//float t = now - t0;
	float deltaY = -G_GRAVITY.y * deltaTime * deltaTime + speed0.y * deltaTime;  // 2X^2 + 50X
	this->_position.y = pos0.y - deltaY ;
	this->_position.x = pos0.x + speed0.x * deltaTime;

	
	trace("deltaTime =				 ", deltaTime);
	//trace("t1 =				 ", now);

	trace("speed0 * t =		 ", speed0.y * deltaTime);
	trace("Gravity * t * t = ", G_GRAVITY.y * deltaTime * deltaTime);
	deltaTime += 2;

	trace("last pos y =			 ", pos0.y);

	trace("pos y =			 ", _position.y);

	// Kiểm tra xem simom quat trở lại mặt đất chưa?
	if (this->_position.y > G_GroundHeight)
	{
		this->_position.y = G_GroundHeight;
		this->isJumping = false;
		this->deltaTime = 1;
	}*/

}

