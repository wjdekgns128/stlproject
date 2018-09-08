#pragma once
#include "cSprite.h"
class cScene
{
public:
	cScene() { ; }
	virtual ~cScene() { ; }

public:
	void virtual Destroy() = 0;
	void virtual Update(long long time) = 0;
	void virtual Render(cSprite* cDC) = 0;
	void virtual Start() = 0;
	bool virtual KeyBoard() = 0;

};