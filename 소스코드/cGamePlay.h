#pragma once

#include "cGame.h"
#include "cScene.h"
#include "cRePlayManager.h"
class cGamePlay : public cScene
{
private:
	cRePlayManager*	RePlayManager;
	cGame*		Game;
	long long MainSceenTime;

public:
	cGamePlay();
	 ~cGamePlay();
public:
	void Start();
	void Destroy();
	void Update(long long time);
	void Render(cSprite* cDC);
	bool KeyBoard();

};