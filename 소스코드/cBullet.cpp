#include "cBullet.h"

cBullet::cBullet(int x, int y, int speed)
{
	
	this->x = x;
	this->y = y;
	this->speed = speed;
	state = 1;
	timer = 0;
}
cBullet::~cBullet()
{

}
void cBullet::Render(cSprite* cDC)
{
	if (state == 1)
	{
		if(speed == 1)
		cDC->Render("*", x, y );
		else
			cDC->Render("v", x, y,LIGHT_RED);

	}
}
void cBullet::Update(long long time)
{
	if (state == 1)
	{
		timer+= 1;
		if (timer >= 3)
		{
			y -= speed;
			timer = 0;
			if (y > 25 || y <= 0)
				state = 0;
		}
	}
}
