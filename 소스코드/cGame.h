#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include "cHero.h"
#include "cUI.h"
#include "cBaseMonster.h"
#include "cMonsterA.h"
#include "cMonsterB.h"
#include "cBoss.h"
#include "cRePlayManager.h"
class cGame 
{
private:
	cBoss*		Boss;
	cHero*		Hero;
	cUI*		UI;
	list<cBaseMonster*> MonsterList;
public:
	cGame(cRePlayManager* RePlay);
	 ~cGame();
private:
	void CreateMonster();
	void CollManager();
	void HeroBoom();
	
public:
	void Update(long long time);
	void Render(cSprite* cDC);
	bool KeyBoard();
	void DisposekeyData(int key)
	{
		Hero->DisposekeyData(key);
	}
	void CreateBullet(int key)
	{
		Boss->CreateBullet(key);
	}
	bool GetNotClear()
	{
		return ( (Hero->getState() == 2));
	}
	bool GetClear()
	{
		return (Boss->getState() == 2);
	}
};