#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include "cSprite.h"
class cBaseMonster
{
protected:
	int x;
	int y;
	int type;
	long long createTime;
	long long moveTime;
	long long timer; // 타이머

	int	state; // 0 생성전 , 1 생성 , 2 터짐 이펙트  , 3 제거
public:
	cBaseMonster()
	{

	}
	virtual ~cBaseMonster()
	{

	}
public:
	virtual void Render(cSprite* cDC) = 0;
	virtual void Update(long long time) = 0;
	virtual inline bool BulletColl(int _x, int _y) = 0;
	virtual void Die() = 0;

public:
	
	inline void setState(int sel)
	{
		state = sel;
	}
	inline int getType() const
	{
		return type;
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
};