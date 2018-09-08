#pragma once

#include "cBaseMonster.h"
#include <list>
#include "cBullet.h"
class cMonsterA : public cBaseMonster
{
private:
	list<cBullet> bullets;
	int timers;
	int bulletTimer;

public:
	cMonsterA(int x, int y, long long time) ;
	~cMonsterA();
public:
	void Update(long long time);

	void Render(cSprite* cDC);
	void Die();

public:
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
};