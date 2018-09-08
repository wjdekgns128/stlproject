#include "cMonsterA.h"


cMonsterA::cMonsterA(int x, int y, long long time) 
{
	type = 0;
	this->x = x;
	this->y = y;
	createTime = time;
	state = 0;
	timer = 0;
	moveTime = 10;
	bulletTimer = 0.0;
	timers = 0;
}
cMonsterA::~cMonsterA()
{
}

void cMonsterA::Update(long long time)
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
		bulletTimer += 1;
		if (timers >= moveTime)
		{
			timers = 0;
			y++;
			if (y >= 25)
				state = 3;
		}
		if (bulletTimer >= 55)
		{
			bulletTimer = 0;
			bullets.push_back(cBullet(x, y + 1, -1));
		}
	}
	else if (state == 2)
	{
		timers += 1;
		if (timers >= 20)
		{
			timers = 0;
			state = 3;
		}
	}
	for (auto m = bullets.begin(); m != bullets.end();)
	{
		(*m).Update(time);
		if ((*m).getState() == 0)
			bullets.erase(m++);
		else
			m++;
	}
}
void cMonsterA::Die()
{
	state = 2;
	timer = 0;
	timers = 0;
}
void cMonsterA::Render(cSprite* cDC)
{
	if (state == 1)
	{
		cDC->Render("M", x, y, JADE);
	}
	else if (state == 2)
	{
			cDC->Render("***", x-1, y, JADE);
			cDC->Render("***", x-1, y - 1, JADE);
			cDC->Render("***", x-1, y + 1, JADE);
	}
	for (cBullet& m : bullets)
		m.Render(cDC);
}