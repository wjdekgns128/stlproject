#include "cMonsterB.h"


cMonsterB::cMonsterB(int x, int y, long long time)
{
	type = 1;
	this->x = x;
	this->y = y;
	createTime = time;
	state = 0;
	timer = 0;
	moveTime = 5;
	timers = 0;

}
cMonsterB::~cMonsterB()
{

}

void cMonsterB::Update(long long time)
{
	if (state == 0)
	{
		timer += time;
		if (timer >= createTime)
		{
			timer = 0;
			state = 1;
		}
	}
	else if (state == 1)
	{
		timers += 1;
		if (timers >= moveTime)
		{
			timers = 0;
			y++;
			if (y >= 25)
				state = 3;
		}
	}
	else if (state == 2)
	{
		timers += 1;
		if (timers >= 25)
		{
			timers = 0;
			state = 3;
		}
	}

}
void cMonsterB::Die()
{
	state = 2;
	timer = 0;
	timers = 0;
}
void cMonsterB::Render(cSprite* cDC)
{
	if (state == 1)
	{
		cDC->Render("M", x, y, LIGHT_GREEN);
	}
	else if (state == 2)
	{

		cDC->Render("***", x-1, y, LIGHT_GREEN);
		cDC->Render("***", x-1, y - 1, LIGHT_GREEN);
		cDC->Render("***", x-1, y + 1, LIGHT_GREEN);
	}
}