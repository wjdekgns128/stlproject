#pragma once
#include "cSceneManager.h"
#include "cWindows.h"
#include "cSingleton.h"
#include "cMenu.h"
#include "cRePlayMenu.h"
#include "cGamePlay.h"
#include "cRePlayGame.h"
class cFrameMain :public cSingleton<cFrameMain>, public cSceneManager,public cWindows
{
public:
	cFrameMain();
	~cFrameMain();

public:
	void Init();
};
