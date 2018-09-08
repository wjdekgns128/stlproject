#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include "cSprite.h"
#include "cRePlayManager.h"

class cUI
{
private:
	long long frameTime;
	int score;
	int	life;
	int	boom;

	int ScoreX;
	int TimeX;
public:
	cUI();
	~cUI();

public:
	void Update(long long time);
	void Render(cSprite* cDC);
public:
	inline void setScoreX(int x)
	{
		ScoreX = x;
	}
	inline void setTimeX(int x)
	{
		TimeX = x;
	}
	inline void setScore(int s)
	{
		score = s;
	}
	inline void setLife(int l)
	{
		life = l;
	}
	inline void setBoom(int b)
	{
		boom = b;
	}
	inline int getScore() const
	{
		return score;
	}
	inline int getLife() const
	{
		return life;
	}
	inline int getBoom() const
	{
		return boom;
	}
};