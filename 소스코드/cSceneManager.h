#pragma once


#include "cScene.h"
#include "cMyInclude.h"
#include "cMyDefine.h"
struct cSceneData
{
	cScene* Scene;
	string	Name;

	cSceneData(cScene* s, string n)
	{
		Scene = s;
		Name = n;
	}
};
class cSceneManager
{
	cScene* nowscene;
	vector<cSceneData> vScene;
public:
	cSceneManager();
	virtual ~cSceneManager();
public:
	cScene* GetScene() { return nowscene; }
protected:
	void Entry(cScene* Scene, string Name);
public:
	void Trans(string Name);
};