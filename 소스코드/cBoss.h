#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include "cSprite.h"
#include "cBullet.h"
#include "cRePlayManager.h"

class cBoss
{
	cRePlayManager*		RePlaye;
	list<cBullet> bullets;
	int timer;
	int state;
	int Hp;
	pair<int, int> RenderPoint[24];
public:
	cBoss(cRePlayManager* Re = NULL);
	~cBoss();

public:
	void Update(long long time);
	void Render(cSprite* cDC);
public:
	inline int getState() const
	{
		return state;
	}
	inline void setState(int s)
	{
		state = s;
	}
	inline pair<int, int> getBossXY(int num) const
	{
		return RenderPoint[num];
	}
	inline void BulletClear() 
	{
		bullets.clear();
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
	inline void Die(int hp)
	{
		Hp -= hp;
		if (Hp <= 0)
		{
			Hp = 0;
			state = 2;
		}
	}
public:
	void CreateBullet(int type);

private:
	void CreatePattern();
};