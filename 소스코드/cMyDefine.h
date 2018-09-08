#pragma once

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{if(p) {delete (p);     (p)=NULL;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)			{if(p) {delete[] (p);     (p)=NULL;}}


#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0))
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1))
#define RIGHT  77
#define LEFT 75
#define UP 72
#define DOWN 80
#define ENTER 13
#define SPACEBAR 32

enum REPLAYSTATE
{
	GAME = 0,
	REPLAY 
};
#define HEROKEYDOWN 0
#define HEROKEYUP 1
#define BOSSPATTERN 2
enum COLOR {
	BLACK = 0, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE
};
#endif

