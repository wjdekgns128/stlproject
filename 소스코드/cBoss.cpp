#include "cBoss.h"
#include "cRePlayManager.h"

cBoss::cBoss(cRePlayManager* Re)
{
	RePlaye = Re;
	timer = 0;
	state = -1;
	Hp = 250;
	int count = 0;
	for (int i = 0; i < 4; ++i)
	{
		RenderPoint[i].first = 28 + i;
		RenderPoint[i].second = 4;
		RenderPoint[20 + i].first = 37 + i;
		RenderPoint[20 + i].second = 4;
	}
	for (int i = 4; i < 8; ++i)
	{
		RenderPoint[i].first = 32;
		RenderPoint[i].second = 2 + count;
		count++;
	}
	count = 0;
	for (int i = 8; i <= 11; ++i)
	{
		RenderPoint[i].first = 33 + count;
		RenderPoint[i].second = 2;
		count++;
	}
	count = 0;
	for (int i = 12; i < 16; ++i)
	{
		RenderPoint[i].first = 32 + count;
		RenderPoint[i].second = 6;
		count++;
	}
	count = 0;
	for (int i = 16; i <= 19; ++i)
	{
		RenderPoint[i].first = 36;
		RenderPoint[i].second = 3 + count;
		count++;
	}
}
cBoss::~cBoss()
{
}
void cBoss::Update(long long time)
{
	if (state == 0)
	{
		timer += 1;

		if (timer > 50)
		{
			timer = 0;
			state = 1;
		}
	}
	else if (state == 1)
	{
		timer += 1;
		if (timer > 55)
		{
			CreatePattern();
			timer = 0;
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
void cBoss::Render(cSprite* cDC)
{
	if (state == 0)
	{
		cDC->Render("....보스 등장....", 27, 8,LIGHT_WHITE);
	}
	if (state == 1)
	{
		for (cBullet& d : bullets)
		{
			d.Render(cDC);
		}
		for (int i = 0; i < 24; i++)
		{
			cDC->Render("@", RenderPoint[i].first, RenderPoint[i].second, LIGHT_BLUE);
		}
		char c[256];
		sprintf(c, "%d", Hp);
		cDC->Render(c, 33, 1, LIGHT_WHITE);
	}
}
void cBoss::CreatePattern()
{
	if (state == 0 || RePlaye == NULL)
		return;

	int type = rand() % 3 + 1;
	RePlaye->InputData(BOSSPATTERN, type);
	CreateBullet(type);
	
}
void cBoss::CreateBullet(int type)
{
	if (type == 1)
	{
		for (int i = 0; i < 4; ++i)
		{
			bullets.push_back(cBullet(RenderPoint[i].first, RenderPoint[i].second, -1));
			bullets.push_back(cBullet(RenderPoint[20 + i].first, RenderPoint[20 + i].second, -1));
		}
	}
	else if (type == 2)
	{
		for (int i = 12; i < 16; ++i)
		{
			bullets.push_back(cBullet(RenderPoint[i].first, RenderPoint[i].second, -1));

		}
		bullets.push_back(cBullet(RenderPoint[19].first, RenderPoint[19].second, -1));
	}
	else if (type == 3)
	{
		for (int i = 0; i < 27; ++i)
		{
			bullets.push_back(cBullet(i, 1, -1));
			bullets.push_back(cBullet(42 + i, 1, -1));

		}
	}
}