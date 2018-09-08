#include "cRePlayGame.h"
#include "cFrameMain.h"
#include "cFileManager.h"
cRePlayGame::cRePlayGame()
{
	RePlayManager = NULL;
	Game = NULL;
	playing = true;
	end = false;
	moveing = false;
	cFrameMain::getinstance()->nowspeed = 1;
}
cRePlayGame::~cRePlayGame()
{
	SAFE_DELETE(RePlayManager);
	SAFE_DELETE(Game);
	datas.clear();
}
void cRePlayGame::Start()
{
	movetime = "";
	cFrameMain::getinstance()->nowspeed = 1;
	nowSpeed = 1;
	playing = true;
	MainSceenTime = 0;
	end = false;
	moveing = true;

	if (RePlayManager == NULL)
	{
		RePlayManager = new cRePlayManager();
		datas.reserve(5000);
		RePlayManager->LoadFile(cFileManager::getinstance()->NowLoadFileName, datas);
		now = datas.begin();
	}
	if (Game == NULL)
	{
		Game = new cGame(NULL);
	}
	endtime = datas[datas.size() - 1].getTime();
}
void cRePlayGame::DisposekeyData()
{

	for (; now != datas.end();)
	{
		if (RePlayManager->getTime() >= (*now).getTime())
		{
			if ((*now).getType() == HEROKEYDOWN)
			{
				Game->DisposekeyData((*now).getKey());
			}
			else if ((*now).getType() == BOSSPATTERN)
			{
				Game->CreateBullet((*now).getKey());
			}
			now++;
		}
		else
			break;
	}
	if (now == datas.end())
	{
		cFrameMain::getinstance()->nowspeed = 1;
		nowSpeed = 1;
		end = true;
		RePlayManager->setTime(endtime);
		playing = true;
	}
}
void cRePlayGame::Destroy()
{
	SAFE_DELETE(RePlayManager);
	SAFE_DELETE(Game);

}
void cRePlayGame::Update(long long time)
{
	if (moveing == false)
		return;
	if (playing == false)
		return;
	if (end == false)
		RePlayManager->Update(time);
	Game->Update(time);
	DisposekeyData();
	if (Game->GetNotClear() || Game->GetClear())
	{
		MainSceenTime += time;
		if (MainSceenTime > 3500)
		{
			cFrameMain::getinstance()->Trans("menu");
		}

	}

}
void cRePlayGame::Render(cSprite* cDC)
{
	cDC->Clear();
	Game->Render(cDC);
	ShowRePlayMenu(cDC);
	if (Game->GetNotClear() || Game->GetClear())
	{
		cDC->Render("리플레이가 끝났습니다.", 22, 10, LIGHT_YELLOW);
		cDC->Render("곧 메인화면으로 돌아갑니다", 22, 11, LIGHT_YELLOW);
	}
	if (moveing == false)
	{
		cDC->Render("이동할 시간을 입력 ( 1000 = 1초) : ", 1, 1);
		cDC->Render((char*)movetime.c_str(), 1, 2);

	}
	cDC->SwapBuffer();

}
void cRePlayGame::MoveTime(long long n)
{
	if (n < 0 || n > datas[datas.size() - 1].getTime())
		return;
	now = datas.begin();
	int n1 = n / 33;
	long long f = n % 33;
	RePlayManager->setTime(0);
	SAFE_DELETE(Game);
	if (Game == NULL)
	{
		Game = new cGame(NULL);
	}
		RePlayManager->Update(f);
		Game->Update(f);
		DisposekeyData();
		for (int i = 0; i < n1; i++)
		{
			RePlayManager->Update(33);
			Game->Update(33);
			DisposekeyData();
		}
	
}

bool cRePlayGame::KeyBoard()
{
	if (end)
		return true;
	if (!moveing)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c >= '0' && c <= '9')
				movetime += c;
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x0001)
		{
			moveing = true;
			MoveTime(atoll(movetime.c_str()));
			movetime = "";
		}
		else if ((GetAsyncKeyState(VK_BACK) & 0x0001) || (GetAsyncKeyState(VK_DELETE) & 0x0001))
		{
			if (movetime.size() > 0)
				movetime.erase(movetime.end() - 1, movetime.end());
		}
		else if (GetAsyncKeyState('M') & 0x0001 || GetAsyncKeyState('m') & 0x0001)
		{
			movetime = "";
			moveing = !moveing;

		}

	}
	else
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
		{
			cFrameMain::getinstance()->Trans("menu");
		}
		else if (GetAsyncKeyState('P') & 0x0001 || GetAsyncKeyState('p') & 0x0001)
		{
			playing = !playing;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
			SpeedCheck(0);
		else if (GetAsyncKeyState(VK_LEFT) & 0x0001)
			SpeedCheck(1);
		else if (GetAsyncKeyState('M') & 0x0001 || GetAsyncKeyState('m') & 0x0001)
		{
			moveing = false;
		}
	}


	return true;
}
void cRePlayGame::SpeedCheck(int n)
{
	if (n == 0)
	{
		if (nowSpeed < 8)
			nowSpeed *= 2;
	}
	else
	{
		if (nowSpeed > 1)
		{
			nowSpeed /= 2;
		}
	}
	cFrameMain::getinstance()->nowspeed = nowSpeed;
}
void cRePlayGame::ShowRePlayMenu(cSprite* cDC)
{
	cDC->Render("MENU", 41, 25);
	cDC->Render("|", 38, 26);
	cDC->Render("|", 38, 27);
	cDC->Render("|", 38, 28);
	cDC->Render("|", 38, 29);
	char c[256];
	sprintf(c, "%.3f", RePlayManager->getFloatTime());
	string s = c;
	s += " / ";
	sprintf(c, "%.3f", endtime * 0.001);
	s += c;

	cDC->Render((char*)s.c_str(), 40, 28);
	cDC->Render("상태: ", 40, 26);
	if (!playing)
	{
		cDC->Render("일시정지", 46, 26);
	}
	else
	{
		cDC->Render("실행중..", 46, 26);

	}
	cDC->Render("배속: ", 40, 27);
	sprintf(c, "%d.0", nowSpeed);
	cDC->Render(c, 46, 27);

	cDC->Render("이동: M", 57, 26);
	cDC->Render("배속: ◀,▶", 57, 27);
	cDC->Render("정지/시작: P", 57, 28);
	cDC->Render("종료: ESC", 57, 29);


}
