#include "cSprite.h"

void cSprite::CreateBuffer(int x,int y)
{
	nScreenIndex = 0;
	COORD size = { x,y }; //������ ũ�� ���� ����ä
	SMALL_RECT rect; //â ũ�� ���� ����ü
	rect.Left = 0;
	rect.Right = windowsX - 1;
	rect.Top = 0;
	rect.Bottom = windowsY - 1;
	//ù��° ���� ����
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
	SetConsoleCursorInfo(hBuffer[0], &cci); // 1�� ���ۿ� �����̴� Ŀ�� ����
	SetConsoleCursorInfo(hBuffer[1], &cci); // 2�� ���ۿ� �����̴� Ŀ�� ����
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

	COORD Coor = { 0, 0 }; //����° ���� �Լ��� ���� ����ü
	DWORD dw; //����° ���� �Լ��� ���� ����ü
	if (nScreenIndex != 0 && nScreenIndex != 1)
		return;
	FillConsoleOutputCharacter(hBuffer[nScreenIndex], ' ', (windowsX+1) * (windowsY+1), Coor, &dw);
}
