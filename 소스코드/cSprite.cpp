#include "cSprite.h"

void cSprite::CreateBuffer(int x,int y)
{
	nScreenIndex = 0;
	COORD size = { x,y }; //버퍼의 크기 관련 구조채
	SMALL_RECT rect; //창 크기 관련 구조체
	rect.Left = 0;
	rect.Right = windowsX - 1;
	rect.Top = 0;
	rect.Bottom = windowsY - 1;
	//첫번째 버퍼 생성
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[1], size);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hBuffer[0], &cci); // 1번 버퍼에 깜박이는 커서 지움
	SetConsoleCursorInfo(hBuffer[1], &cci); // 2번 버퍼에 깜박이는 커서 지움
}
void cSprite::Render(char* text, int x, int y, COLOR FontColor)
{
	if (nScreenIndex != 0 && nScreenIndex != 1)
		return;
	DWORD dw; 
	COORD CursorPosition = { x, y };  

	SetConsoleTextAttribute(hBuffer[nScreenIndex], FontColor);

	SetConsoleCursorPosition(hBuffer[nScreenIndex], CursorPosition);   
	WriteFile(hBuffer[nScreenIndex], text, strlen(text), &dw, NULL);   

}
void cSprite::Clear()
{

	COORD Coor = { 0, 0 }; //세번째 줄의 함수를 위한 구조체
	DWORD dw; //세번째 줄의 함수를 위한 구조체
	if (nScreenIndex != 0 && nScreenIndex != 1)
		return;
	FillConsoleOutputCharacter(hBuffer[nScreenIndex], ' ', (windowsX+1) * (windowsY+1), Coor, &dw);
}
