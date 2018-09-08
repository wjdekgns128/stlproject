#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include "cSprite.h"
class cBullet
{
private:
	int x;
	int y;
	int speed;
	int state;
	int timer;
public:
	cBullet(int x, int y, int speed);
	~cBullet();

public:
	void Render(cSprite* cDC);
	void Update(long long time);
public:
	inline void setState(int sel)
	{
		state = sel;
	}
	inline int getState() const
	{
		return state;
	}
	inline int getX() const
	{
		return x;
	}
	inline int getY() const
	{
		return y;
	}
	inline bool Coll(int _x, int _y)
	{
		return((x == _x) && (y == _y));
	}
};