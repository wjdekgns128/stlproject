#include "cGame.h"
#include "cFrameMain.h"

cGame::cGame(cRePlayManager* RePlay)
{

	
		Boss = new cBoss(RePlay);
	
		Hero = new cHero(cFrameMain::getinstance()->GetWindownX(), cFrameMain::getinstance()->GetWindownY(), RePlay);
	
		UI = new cUI();
		UI->setLife(Hero->getLife());
		UI->setBoom(Hero->getBoom());
		UI->setScore(0);
		if (RePlay == NULL)
		{
			UI->setScoreX(20);
			UI->setTimeX(-1);
		}
		else
		{
			UI->setScoreX(48);
			UI->setTimeX(48);
		}
	CreateMonster();

}
cGame::~cGame()
{
	SAFE_DELETE(Boss);
	SAFE_DELETE(Hero);
	SAFE_DELETE(UI);
	for (auto m = MonsterList.begin(); m != MonsterList.end();)
	{
		SAFE_DELETE(*m);
		m++;
	}
	MonsterList.clear();
}
void cGame::CreateMonster()
{
	int type;
	int x;
	int y;
	long long time;
	ifstream fp("res/map/map.txt", ios::binary);
	while (!fp.eof())
	{
		fp.read((char*)&type, sizeof(int));
		fp.read((char*)&x, sizeof(int));
		fp.read((char*)&y, sizeof(int));
		fp.read((char*)&time, sizeof(long long));
		switch (type)
		{
		case 0:
			MonsterList.push_back(new cMonsterA(x, y, time));
			break;
		case 1:
			MonsterList.push_back(new cMonsterB(x, y, time));

		}
	}
	fp.close();
}
void cGame::HeroBoom()
{
	if (Hero->getBoomIng() && Hero->getState() == 1)
	{
		for (cBaseMonster* d : MonsterList)
		{
			if (d->getState() == 1)
			{
				d->Die();
				UI->setScore(UI->getScore() + 10);
			
			}
		}
		if (Boss->getState() == 1)
		{
			Boss->Die(20);
			UI->setScore(UI->getScore() + 100);
			UI->setBoom(Hero->getBoom());
			Boss->BulletClear();
		}
		UI->setBoom(Hero->getBoom());
		Hero->setBoomIng(false);
	}
}

void cGame::CollManager()
{
	//히어로총알 vs 몬스터 , 히어로 vs 몬스터
	for (cBaseMonster* d : MonsterList)
	{
		if (d->getState() != 1)
			continue;
		if (Hero->BulletColl(d->getX(), d->getY()))
		{
			d->Die();
			UI->setScore(UI->getScore() + 10);
		}
		if (Hero->getState() != 1)
			continue;
		else if (Hero->Coll(d->getX(), d->getY()))
		{
			d->Die();
			Hero->Die();
			UI->setLife(Hero->getLife());
		}
	}
	// 몬스터총알 vs 히어로
	for (cBaseMonster* d : MonsterList)
	{
		if (Hero->getState() != 1)
			continue;
		if (d->BulletColl(Hero->getX(), Hero->getY()))
		{
			Hero->Die();
			UI->setLife(Hero->getLife() );
		}
	}
	// 히어로 vs 보스, 히어로총알 vs 보스
	for (int i = 0; i < 24; ++i)
	{
		if (Hero->getState() != 1 || Boss->getState() != 1)
			continue;
		if (Hero->Coll(Boss->getBossXY(i).first, Boss->getBossXY(i).second))
		{
			Hero->Die();
			UI->setLife(Hero->getLife());
		}
		if (Hero->BulletColl(Boss->getBossXY(i).first, Boss->getBossXY(i).second))
		{
			Boss->Die(1);
			UI->setScore(UI->getScore() + 10);
		}
	}
	if (Boss->BulletColl(Hero->getX(), Hero->getY()))
	{
		if (Hero->getState() != 1)
			return;
		Hero->Die();
		UI->setLife(Hero->getLife());
	}
}

void cGame::Update(long long time)
{
	

	if (MonsterList.size() <= 0 && Boss->getState() == -1)
	{
		Boss->setState(0);
	}
	for (auto m = MonsterList.begin(); m != MonsterList.end();)
	{
		(*m)->Update(time);

		if ((*m)->getState() == 3)
		{
			SAFE_DELETE(*m);
			MonsterList.erase(m++);
		}
		else
			m++;
	}
	UI->Update(time);
	Boss->Update(time);
	Hero->Update(time);
	CollManager();
	HeroBoom();

}

void cGame::Render(cSprite* cDC)
{
	Hero->Render(cDC);
	UI->Render(cDC);
	Boss->Render(cDC);
	for ( cBaseMonster* m : MonsterList)
	{
		m->Render(cDC);
	}
	



}

bool cGame::KeyBoard()
{
		Hero->KeyBoard();
	return true;
}
