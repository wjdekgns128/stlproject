#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include "cScene.h"
#define MAXLIST 18
class cRePlayMenu : public cScene
{
private:
	int				Selete;
	int				Page;
	int				MaxSelete;
	int				MaxPage;
	vector<string> FileList;
public:
	cRePlayMenu();
	~cRePlayMenu();
public:
	void Start();
	void Destroy();
	void Update(long long time);
	void Render(cSprite* cDC);
	bool KeyBoard();

};