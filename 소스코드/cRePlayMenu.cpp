#include "cRePlayMenu.h"
#include "cFrameMain.h"
#include "cFileManager.h"

cRePlayMenu::cRePlayMenu()
{
	FileList.clear();
	Selete = 0;
	Page = 0;
	MaxSelete = 0;
	MaxPage = 0;
}
cRePlayMenu::~cRePlayMenu()
{
	FileList.clear();

}
void cRePlayMenu::Start()
{
	vector<string> TempList;
	Selete = 0;
	Page = 0;
	TempList = cFileManager::getinstance()->GetFoderInFileList("res/save", ".txt");
	FileList.reserve(TempList.size());
	for (int i = 0; i < TempList.size(); ++i)
	{
		FileList.push_back(TempList[i].substr(0,TempList[i].find('.')));
	}
	FileList.size() > MAXLIST ? MaxSelete = MAXLIST : MaxSelete = FileList.size();
	MaxPage = FileList.size() / MAXLIST;
}
void cRePlayMenu::Destroy()
{
	FileList.clear();

}
void cRePlayMenu::Update(long long time)
{

}
void cRePlayMenu::Render(cSprite* cDC)
{
	cDC->Clear();
	cDC->Render("---------------목 록---------------", 8, 3,LIGHT_WHITE);
	cDC->Render("-----------------------------------", 8, 5);
	for (int i = 0; i < MAXLIST;i++)
	cDC->Render("|", 8, 6+i);

	for (int i = 0; i < MAXLIST; ++i)
	{
		if (FileList.size() <= i + (MAXLIST*Page))
			continue;
		cDC->Render(const_cast<char*>( FileList[i + (MAXLIST*Page)].c_str()), 15, 6 + i);
		cDC->Render(const_cast<char*>(to_string((i+1) + (MAXLIST*Page)).c_str()),12, 6 + i);
	}
	cDC->Render("-----------------------------------", 8, 24);
	for (int i = 0; i < MAXLIST; i++)
		cDC->Render("|", 43, 6 + i);

	cDC->Render("▶", 9, 6+ Selete);
	cDC->Render("---------조작법------", 47, 10);
	cDC->Render("이동 : 위아래방향키",48,12);
	cDC->Render("선택 : 엔터키", 48, 14);
	cDC->Render("메뉴로 이동 : ESC키", 48, 16);

	cDC->Render("---------------------", 47, 17);
	char c[256];

	sprintf(c, "%d / %d", Page+1, MaxPage+1);
	cDC->Render(c, 24, 25);
	cDC->SwapBuffer();
}

bool cRePlayMenu::KeyBoard()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x001)
	{
		cFrameMain::getinstance()->Trans("menu");
	}
	if (FileList.size() == 0)
		return true;
	if (GetAsyncKeyState(VK_UP) & 0x001)
	{
		Selete--;
		if (Selete < 0)
		{
			
			if (Page == 0)
			{
				if (FileList.size() < MAXLIST)
				{
				
					Selete = FileList.size()-1;
					FileList.size() > MAXLIST ? MaxSelete = MAXLIST : MaxSelete = FileList.size();
				}
				else
				{
					Page = MaxPage;
					Selete = FileList.size() - (Page * MAXLIST) - 1;
					MaxSelete = FileList.size() - (Page * MAXLIST);
				}
			}
			else
			{
				Page--;
				Selete = MAXLIST-1;
				if(Page == 0)
				FileList.size() > MAXLIST ? MaxSelete = MAXLIST : MaxSelete = FileList.size();
				else
				{
						MaxSelete = MAXLIST;
						if (Page == MaxPage)
						{
							MaxSelete = FileList.size() % (MAXLIST*Page);
						}
				}
			}
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x001)
	{
		Selete++;
		if (Selete >= MaxSelete)
		{
			Selete = 0;
			if (MaxPage > Page)
			{
				Page++;
				MaxSelete = MAXLIST;
				if (Page == MaxPage)
				{
					MaxSelete = FileList.size() % (MAXLIST*Page);
				}
			}
			else
			{
				FileList.size() > MAXLIST ? MaxSelete = MAXLIST : MaxSelete = FileList.size();
				Page = 0;
			}

		}
	}
	
	else if (GetAsyncKeyState(VK_RETURN) & 0x001)
	{
		if (FileList.size() == 0)
			return true;
		cFileManager::getinstance()->NowLoadFileName = FileList[Selete + (MAXLIST*Page)];
		cFrameMain::getinstance()->Trans("regame");

	}
	return true;
}
