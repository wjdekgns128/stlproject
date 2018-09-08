#include "cWindows.h"


cWindows::cWindows(const char* Name, const int xSize, const int ySize)
{
	this->xSize = xSize;
	this->ySize = ySize;
	nowspeed = 1.0;
	char data[100] = { 0, };
	sprintf_s(data, sizeof(data), "mode con:cols=%d lines=%d", xSize, ySize);
	system(data);
	sprintf_s(data, sizeof(data), "title %s", Name);
	system(data);
}
cWindows::~cWindows()
{

}
