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
		cDC->Render("�������� Ŭ���� ����", 23, 9, LIGHT_YELLOW);
		cDC->Render("���̺� ������ save ������ �ڵ�����˴ϴ�", 16, 10, LIGHT_YELLOW);
		cDC->Render("�� ����ȭ������ ���ư��ϴ�", 22, 11, LIGHT_YELLOW);
	}
	if (Game->GetClear())
	{
		cDC->Render("�������� Ŭ���� !!!", 23, 9, LIGHT_YELLOW);
		cDC->Render("���̺� ������ save ������ �ڵ�����˴ϴ�", 16, 10, LIGHT_YELLOW);
		cDC->Render("�� ����ȭ������ ���ư��ϴ�", 22, 11, LIGHT_YELLOW);
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
