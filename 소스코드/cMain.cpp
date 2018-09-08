#include "cMyInclude.h"
#include "cFrameMain.h" 
#include "cSprite.h"
#include "cFileManager.h"
#define _CRTDBG_MAP_ALLOC 
bool Handler(DWORD type); // 종료 메세지
void CloseGame();
bool gameing = true;
cFrameMain* framemain = cFrameMain::getinstance();
cSprite*	sprite = new cSprite;
void UpdateFPS();
int main()
{
	bool exitcheck = SetConsoleCtrlHandler((PHANDLER_ROUTINE)Handler, TRUE);
	framemain->Init();
	sprite->CreateBuffer(framemain->GetWindownX(), framemain->GetWindownY());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cFileManager::getinstance()->GetFoder("res/save");


	int FPS = 30;
	int loops = 0;
	long long FPSTime = 1000.0/(float)FPS;
	auto next_tick = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	gameing = true;
	
	while (gameing)
	{
		loops = 0;
		long long now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		while (now >= next_tick && loops <= 10)
		{
			framemain->GetScene()->Update(FPSTime);
			if (!framemain->GetScene()->KeyBoard())
			{
				gameing = false;
				break;
			}
			next_tick += (long long)(FPSTime/framemain->nowspeed);
			loops++;
		}
		framemain->GetScene()->Render(sprite);
	}
	CloseGame();

}
bool Handler(DWORD type)
{
	switch (type)
	{
	case CTRL_LOGOFF_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		gameing = false;
		return TRUE;
	}

	return FALSE;
}
void CloseGame()
{

	cFrameMain::DestroyInstance();
	SAFE_DELETE( sprite);
	cFileManager::DestroyInstance();

}
void UpdateFPS()
{
	static DWORD frameCount = 0;           
	static float timeElapsed = 0.0f;      
	static DWORD lastTime = GetTickCount();  
	DWORD curTime = GetTickCount();    
	float timeDelta = (curTime - lastTime)*0.001f;     
	timeElapsed += timeDelta;
	frameCount++;
	if (timeElapsed >= 1.0f)    
	{
		float fps = (float)frameCount / timeElapsed;
		char c[256];
		sprintf(c, "FPS %f\n", fps);
		OutputDebugStringA(c);
		frameCount = 0;
		timeElapsed = 0.0f;
	}
	lastTime = curTime;
}


