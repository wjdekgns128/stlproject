#pragma once
#include "cMyInclude.h"
#include "cMyDefine.h" 
class cSprite
{
	HANDLE hBuffer[2];  //버퍼 핸들
	int nScreenIndex;
	int windowsX;
	int windowsY;

public:
	cSprite()
	{
	
	}
	~cSprite()
	{
		CloseHandle(hBuffer[0]);    //버퍼 해제
		CloseHandle(hBuffer[1]);

	}
public:
	void CreateBuffer(int x,int y);
	void Render(char* text,int x, int y,COLOR FontColor = WHITE);
	void SwapBuffer()
	{
		if (nScreenIndex != 0 && nScreenIndex != 1)
			return;
		SetConsoleActiveScreenBuffer(hBuffer[nScreenIndex]);
		nScreenIndex = !nScreenIndex;
	}

	void Clear();
};