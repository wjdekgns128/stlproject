#pragma once

#include "cBaseMonster.h"
class cMonsterB : public cBaseMonster
{
private:
	int timers;
public:
	cMonsterB(int x, int y, long long time);
	~cMonsterB();
public:
	void Update(long long time);
	void Render(cSprite* cDC);
	void Die();

public:
	inline bool BulletColl(int _x, int _y)
	{
		return false;
	}
};