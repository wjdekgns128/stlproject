#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include "cScene.h"
#include "cFrameMain.h"
class cMenu : public cScene
{
private:
	int		Selete;
public:
	cMenu();
	~cMenu();
public:
	void Start();
	void Destroy();
	void Update(long long time);
	void Render(cSprite* cDC);
	bool KeyBoard();

private:
	void RenderGameName(cSprite* cDC);
	void SeleteMenu(cSprite* cDC);
};