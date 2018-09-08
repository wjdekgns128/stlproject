#include "cSceneManager.h"`

cSceneManager::cSceneManager()
{
	nowscene = NULL;
	vScene.clear();
}
cSceneManager::~cSceneManager()
{
	for (int i = 0; i < vScene.size(); i++)
	{
		SAFE_DELETE(vScene[i].Scene);
	}
	nowscene = NULL;
	vScene.clear();
}
void cSceneManager::Entry(cScene* Scene, string Name)
{
	vScene.emplace_back(Scene, Name);
}
void cSceneManager::Trans(string Name)
{
	for (int i = 0; i < vScene.size(); i++)
	{
		if (vScene[i].Name == Name)
		{
			if (nowscene != NULL)
				nowscene->Destroy();
			nowscene = vScene[i].Scene;
			nowscene->Start();
			break;
		}
	}
}