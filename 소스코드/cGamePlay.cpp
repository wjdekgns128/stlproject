#include "cGamePlay.h"
#include "cFrameMain.h"

cGamePlay::cGamePlay()
{
	RePlayManager = NULL;
	Game = NULL;
}
cGamePlay::~cGamePlay()
{
	SAFE_DELETE(RePlayManager);
	SAFE_DELETE(Game);

}
void cGamePlay::Start()
{
	MainSceenTime = 0;
	if (RePlayManager == NULL)
	{
		RePlayManager = new cRePlayManager();
	}
	if (Game == NULL)
	{
		Game = new cGame(RePlayManager);
	}



}
void cGamePlay::Destroy()
{
	SAFE_DELETE(RePlayManager);
	SAFE_DELETE(Game);

}
void cGamePlay::Update(long long time)
{
	RePlayManager->Update(time);
	Game->Update(time);
	if (Game->GetNotClear() || Game->GetClear())
	{
		MainSceenTime += time;
		if (MainSceenTime > 3500)
		{
			RePlayManager->SaveFile();
			cFrameMain::getinstance()->Trans("menu");
		}

	}
}
void cGamePlay::Render(cSprite* cDC)
{
	cDC->Clear();
	Game->Render(cDC);
	if (Game->GetNotClear())
	{
		cDC->Render("스테이지 클리어 실패", 23, 9, LIGHT_YELLOW);
		cDC->Render("세이브 파일은 save 폴더에 자동저장됩니다", 16, 10, LIGHT_YELLOW);
		cDC->Render("곧 메인화면으로 돌아갑니다", 22, 11, LIGHT_YELLOW);
	}
	if (Game->GetClear())
	{
		cDC->Render("스테이지 클리어 !!!", 23, 9, LIGHT_YELLOW);
		cDC->Render("세이브 파일은 save 폴더에 자동저장됩니다", 16, 10, LIGHT_YELLOW);
		cDC->Render("곧 메인화면으로 돌아갑니다", 22, 11, LIGHT_YELLOW);
	}
	cDC->SwapBuffer();


}
bool cGamePlay::KeyBoard()
{
	if (Game->GetNotClear() || Game->GetClear())
	{
		return true;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x001)
	{
		cFrameMain::getinstance()->Trans("menu");
	}
	else
	{
		Game->KeyBoard();
	}
	return true;
}
