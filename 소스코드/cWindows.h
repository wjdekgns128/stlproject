#pragma once

#include "cMyDefine.h"
#include "cMyInclude.h"


class cWindows
{
public:
	int nowspeed;
private:
	int xSize;
	int ySize;
protected:
	cWindows(const char* Name = "MAIN", const int xSize = 80, const int ySize = 30);
	virtual ~cWindows();
public:
	int GetWindownX() { return xSize; }
	int GetWindownY() { return ySize; }

};
