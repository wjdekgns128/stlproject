#include "cMenu.h"

cMenu::cMenu()
{
	Selete = 0;
}
cMenu::~cMenu()
{

}
void cMenu::Start()
{

}
void cMenu::Destroy()
{

}
void cMenu::Update(long long time)
{
	
}
void cMenu::Render(cSprite* cDC)
{
	
	cDC->Clear();

	RenderGameName(cDC);
	SeleteMenu(cDC);
	cDC->SwapBuffer();
}

bool cMenu::KeyBoard()
{
	if (GetAsyncKeyState(VK_UP) & 0x0001)
	{
		Selete--;
		if (Selete < 0)
			Selete = 2;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	{
		Selete++;
		Selete = Selete % 3;
	}
	else if (GetAsyncKeyState(VK_RETURN)  & 0x0001)
	{
		if (Selete == 2)
			return false;
		else if(Selete == 1)
			cFrameMain::getinstance()->Trans("replay");
		else if (Selete == 0)
			cFrameMain::getinstance()->Trans("game");
	}
	return true;
}
void cMenu::RenderGameName(cSprite* cDC)
{
	for (int i = 0; i < 11; ++i)
	{
		cDC->Render("-", 8 + i, 5);
		cDC->Render("-", 8 + i, 10);
		cDC->Render("-", 8 + i, 15);


		cDC->Render("-", 22 + i, 5);
		cDC->Render("-", 22 + i, 15);


		cDC->Render("-", 51 + i, 5);

	}
	for (int i = 0; i < 4; ++i)
	{
		cDC->Render("|", 18, 6 + i);
		cDC->Render("|", 8, 11 + i);

		cDC->Render("|", 22, 6 + i);
		cDC->Render("|", 22, 10 + i);

		cDC->Render("|", 32, 6 + i);
		cDC->Render("|", 32, 10 + i);

		cDC->Render("|", 42, 6 + i);
		cDC->Render("|", 42, 10 + i);


		cDC->Render("|", 61, 6 + i);
		cDC->Render("|", 61, 10 + i);
	}
	cDC->Render("|", 22, 14);
	cDC->Render("|", 32, 14);
	cDC->Render("|", 42, 14);
	cDC->Render("|", 61, 14);
}

void cMenu::SeleteMenu(cSprite* cDC)
{
	cDC->Render("게      임      시      작", 21, 18, LIGHT_YELLOW);
	cDC->Render("리      플      레      이", 21, 22, LIGHT_YELLOW);
	cDC->Render("게      임      종      료", 21, 26, LIGHT_YELLOW);
	cDC->Render("▶", 17, 18 + (Selete * 4), LIGHT_WHITE);


}
