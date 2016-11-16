#include "Simon.h"
#include "Input.h"
#include "utils.h"
void Simon::Update(float dt)
{

	if (Key_Down(DIK_LEFT) && st == status::STAND && !isAction)	// go to left
	{ 
		isWalking = true;
		st = status::STAND;
		isAction = false;
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
		}
	}
	if (Key_Down(DIK_RIGHT) && st == status::STAND && !isAction)	// go to left
	{
		isWalking = true;
		st = status::STAND;

		isAction = false;
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
	}

	if (Key_Down(DIK_DOWN) && st == status::STAND)  // sit
	{
		st = status::SIT;
		this->flag = 0;
		isSitting = true;
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
	if (GIsKeyRelease(G_KEY::KEY_DOWN))
	{
		st = status::STAND;
		isAction = false;
		this->_index = 0;
		this->setIndex(this->_index);
		this->_currentFrame;
		isSitting = false;
		isStanding = true;
		isJumping = false;
	}
	
	// right release
	if (GIsKeyRelease(G_KEY::KEY_RIGHT) || GIsKeyRelease(G_KEY::KEY_LEFT))
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
		isWalking = false;
	}

	if (Key_Down(DIK_X)) // jump
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
		if (st != status::JUMP) // Only jump if it is not yet currently jumping
		{

			timeJumpStart = 0;
			this->timeFromStart = 0.0f;

			lastPos = this->_position;
			lastSpeed = this->velocity;

			lastSpeed.y += this->speedJump;
			lastSpeed.y += this->velocity.y;
			this->isJumping = true;
			st = status::JUMP;
		}
	}

	// jump
	if (st == status::JUMP)
	{
		// chuyển frame
		this->setIndex(this->_index);
		this->_currentFrame;

		this->timeFromStart += 8 * dt;

		// jump
		// deltaY = - G_GRAVITY.y * deltaTime * deltaTime + lastSpeed.y * deltaTime;  // tuong duong voi phuong trinh: -2X^2 + 50X
		// - gravity  * X^2  +   speed * X
		// -2 X^2  + 90X
		this->_position.y = lastPos.y - (-G_GRAVITY.y * this->timeFromStart * this->timeFromStart + lastSpeed.y * this->timeFromStart);
		this->_position.x = lastPos.x + lastSpeed.x * this->timeFromStart;

		deltaTime += 2;

		// Kiểm tra xem simom quat trở lại mặt đất chưa?
		if (this->_position.y > G_GroundHeight)
		{
			this->_position.y = G_GroundHeight;
			this->isJumping = false;
			isAction = false;
			st = status::STAND;
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
		}

	}
	if (GIsKeyRelease(G_KEY::KEY_Z))
	{
		isZPress = false;
	}
	if (Key_Down(DIK_Z) && !isZPress)
	{
		isAction = true;
		isZPress = true;
	}
	if (isAction)
	{
		this->timeFrameStartAction += dt;
		if (this->timeFrameStartAction >= this->timePerImage)
		{
			this->timeFrameStartAction = 0;
			switch (st)
			{
			case status::JUMP:
				if (this->_index < 5)
				{
					this->_index = 5;
				}
				else if (this->_index >= 7)
				{
					this->_index = 0;
					isAction = false;
				}
				else
				{
					this->_index++;
				}
				break;
			case status::SIT:

				if (this->_index < 15)
				{
					this->_index = 15;
				}
				else if (this->_index >= 17)
				{
					this->_index = 4;
					isAction = false;
				}
				else
				{
					this->_index++;
				}
				break;
			case status::STAND:

				if (this->_index < 5)
				{
					this->_index = 5;
				}
				else if (this->_index >= 7)
				{
					this->_index = 0;
					isAction = false;
				}
				else
				{
					this->_index++;
				}

				break;
			}
			this->setIndex(this->_index);
			if (this->Direction == 1)
			{
				this->setScaleX(1);

			}
			else if (this->Direction == -1)
			{
				this->setScaleX(-1);
			}

		}
	}
}


