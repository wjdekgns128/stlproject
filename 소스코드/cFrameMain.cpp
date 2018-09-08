#include "cFrameMain.h"

cFrameMain::cFrameMain() : cWindows("GAME",70,30)
{

}
cFrameMain::~cFrameMain()
{

}
void cFrameMain::Init()
{
	Entry(new cMenu, "menu");
	Entry(new cGamePlay, "game");
	Entry(new cRePlayMenu, "replay");
	Entry(new cRePlayGame, "regame");

	Trans("menu");
}