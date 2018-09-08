#include "cHero.h"
#include "cRePlayManager.h"

cHero::cHero(int WindowsX, int WindowsY, cRePlayManager* Re)
{
	RePlaye = Re;
	life = 3;
	boom = 3;
	winX = WindowsX;
	winY = WindowsY;
	ReSetting();
	BoomIng = false;

}
cHero::~cHero()
{

}
void cHero::Render(cSprite* cDC)
{
	if (state == 1)
		cDC->Render("H", x, y, LIGHT_RED);

	for (cBullet& m : bullets)
		m.Render(cDC);
}
void cHero::Update(long long time)
{
	if (state == 0)
	{
		frame++;
		if (frame > 20)
		{
			frame = 0;
			BoomIng = true;
			ReSetting();
		}
	}
	else
	{
		BulletsCreate += 1;
		BoomTime += 1;
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
void cHero::DisposekeyData(int key)
{
	if (state == 1)
	{
		if (key == VK_RIGHT)
		{
			x++;
			x = min(winX - 1, x);
		}
		else if (key == VK_LEFT)
		{
			x--;
			x = max(0, x);
		}
		else if (key == VK_UP)
		{
			y--;
			y = max(0, y);
		}
		else if (key == VK_DOWN)
		{
			y++;
			y = min(winY - 6, y);
		}
		else if (key == VK_SPACE)
		{
			if (BulletsCreate > 2)
			{

				bullets.push_back(cBullet(x, y - 1, 1));
				BulletsCreate = 0;
			}
		}
		else if (key == VK_CONTROL)
		{
			if (BoomTime > 10)
			{
				if (BoomIng == false)
				{
					if (boom > 0)
					{
						BoomIng = true;
						boom--;
					}
				}
				BoomTime = 0;
			}
		}
	}
}
bool cHero::KeyBoard()
{
	if (state == 1 )
	{
		if (KEYDOWN(VK_RIGHT))
		{
			DisposekeyData(VK_RIGHT);
			RePlaye->InputData(HEROKEYDOWN, VK_RIGHT);

		}
		if (KEYDOWN(VK_LEFT))
		{
			DisposekeyData(VK_LEFT);
			RePlaye->InputData(HEROKEYDOWN, VK_LEFT);

		}
		if (KEYDOWN(VK_UP))
		{
			DisposekeyData(VK_UP);
			RePlaye->InputData(HEROKEYDOWN, VK_UP);
		}
		if (KEYDOWN(VK_DOWN))
		{
			DisposekeyData(VK_DOWN);
			RePlaye->InputData(HEROKEYDOWN, VK_DOWN);
		}
		if (KEYDOWN(VK_SPACE))
		{
			DisposekeyData(VK_SPACE);
			RePlaye->InputData(HEROKEYDOWN, VK_SPACE);

		}
		if (KEYDOWN(VK_CONTROL))
		{
			DisposekeyData(VK_CONTROL);
			RePlaye->InputData(HEROKEYDOWN, VK_CONTROL);
		}

	}
	return true;
}