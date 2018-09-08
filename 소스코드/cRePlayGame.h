#pragma once

#include "cGame.h"
#include "cScene.h"
#include "cRePlayManager.h"

class cRePlayGame :  public cScene
{
private:
	cGame*		Game;
	cRePlayManager*	RePlayManager;
	vector<cRePlayData> datas;
	vector<cRePlayData>::iterator now;
	bool end;
	long long endtime;
	long long MainSceenTime;
	bool		playing;
	int		nowSpeed;

	bool		moveing;
	string      movetime;
public:
	cRePlayGame();
	~cRePlayGame();
public:
	void Start();
	void Destroy();
	void Update(long long time);
	void Render(cSprite* cDC);
	bool KeyBoard();
public:
	void DisposekeyData();
	void ShowRePlayMenu(cSprite* cDC);
	void SpeedCheck(int n);
	void MoveTime(long long n);
};