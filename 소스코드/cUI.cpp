#include "cUI.h"
#include "cRePlayManager.h"
cUI::cUI()
{
	frameTime = 0;
	score = 0;
	life = 0;
	boom = 0;
}
cUI::~cUI()
{

}
void cUI::Update(long long time)
{
	frameTime += time;
}
void cUI::Render(cSprite* cDC)
{
	cDC->Render("----------------------------------------------------------------------", 0, 25);

	cDC->Render("LIFE : ", 3, 26);
	cDC->Render("BOOM : ", 3, 28);
	if(TimeX != -1)
	cDC->Render("TIME  : ", TimeX, 28);

	cDC->Render("SCORE : ", ScoreX, 26);

	for (int i = 0; i < life; ++i)
		cDC->Render("H", 10 + i * 3, 26, LIGHT_RED);

	for (int i = 0; i < boom; ++i)
		cDC->Render("B", 10 + i * 3, 28, LIGHT_YELLOW);
	char c[256];
	sprintf(c, "%d", score);
	cDC->Render(c, ScoreX+8, 26, LIGHT_WHITE);
	if (TimeX != -1)
	{
		sprintf(c, "%f", frameTime * 0.001);
		cDC->Render(c, TimeX + 8, 28, LIGHT_WHITE);
	}

}