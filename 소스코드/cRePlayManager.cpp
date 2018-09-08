#include "cRePlayManager.h"
#include "cFileManager.h" 
cRePlayManager::cRePlayManager()
{
	ReSet();
}
cRePlayManager::~cRePlayManager()
{
	datas.clear();

}
void cRePlayManager::Update(long long time)
{
	NowTime += time;
}
void cRePlayManager::InputData(int type, int key)
{
	datas.push_back(cRePlayData(type, key, NowTime));
}
void cRePlayManager::InputData(cRePlayData data)
{
	datas.push_back(data);
}
void cRePlayManager::SaveFile()
{
	ReSet();
	state = GAME;
	int Count = cFileManager::getinstance()->GetFoderInFileCount("res/save", ".txt");
	string FileName = "Replay" + to_string(Count) + ".txt";

	ofstream in("res/save/" + FileName,ios::binary);

	for (int i = 0; i < datas.size(); ++i)
	{
		in << datas[i];
	}
	in.close();
}
void cRePlayManager::LoadFile(const string& name, vector<cRePlayData>& temp)
{
	ReSet();

	state = REPLAY;
	string FileName = name + ".txt";

	ifstream in("res/save/" + FileName, ios::binary);
	cRePlayData data;
	while (in >> data )
	{
		temp.emplace_back(data.getType(),data.getKey(), data.getTime());
	}
	in.close();
}