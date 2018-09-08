#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include "cSprite.h"
#include "cBullet.h"
#include "cRePlayManager.h"
class cHero
{
private:
	cRePlayManager*		RePlaye;
	int x;
	int y;
	int life;
	int boom;
	int winX;
	int winY;
	int state;
	int frame;
	bool BoomIng;
	list<cBullet> bullets;

	int BulletsCreate;
	int BoomTime;
public:
	cHero(int WindowsX, int WindowsY, cRePlayManager* Re = NULL);
	~cHero();
public:
	void Render(cSprite* cDC);
	void Update(long long time);
	bool KeyBoard();
	void DisposekeyData(int key);
public:

public:

	inline bool getBoomIng() const // 필살기 사용했는지..
	{
		return BoomIng;
	}
	inline void setBoomIng(bool b)
	{
		BoomIng = b;
	}
	inline bool Coll(int _x, int _y) // 히어로 충돌
	{
		return((x == _x) && (y == _y));
	}
	inline bool BulletColl(int _x, int _y) 
	{
		for (cBullet& m : bullets)
		{
			if (m.getState() == 0)
				continue;
			if ((m.getX() == _x) && (m.getY() == _y))
			{
				m.setState(0);
				return true;

			}
		}
		return false;
	}
	inline void ReSetting() 
	{

		BoomTime = 200;
		BulletsCreate = 70;
		bullets.clear();
		x = 34;
		y = 23;
		state = 1;
		frame = 0;
	}
	inline void Die()
	{
		life--;
		if (life < 0)
		{
			life = 0;
			state = 2;
		}
		else
			state = 0;
	}
	inline int getState() const
	{
		return state;
	}
	inline int getX() const
	{
		return x;
	}
	inline int getY()const
	{
		return y;
	}
	inline int getLife()const
	{
		return life;
	}
	inline int getBoom()const
	{
		return boom;
	}
	inline void setBoom(int n)
	{
		boom = n;
	}
};