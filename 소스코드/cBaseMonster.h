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
	long long timer; // Ÿ�̸�

	int	state; // 0 ������ , 1 ���� , 2 ���� ����Ʈ  , 3 ����
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