#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include <deque>
class cRePlayData
{
private:
	int type; // 히어로? 보스?
	int key; // 입력키
	long long time; // 자기시간
public:
	cRePlayData()
	{

	}
	cRePlayData(int type,int key,int time) : type(type),key(key),time(time)
	{
		

	}
	~cRePlayData()
	{

	}
public:
	void setType(int type)
	{
		this->type = type;
	}
	void setKey(int key)
	{
		this->key = key;
	}
	void setTime(long long time)
	{
		this->time = time;
	}
	int getType() const
	{
		return type;
	}
	int getKey() const
	{
		return key;
	}
	long long getTime() const
	{
		return time;
	}
public:
	friend ofstream& operator<<(ofstream& os, const cRePlayData& data)
	{
		int type = data.getType();
		int key = data.getKey();
		long long time = data.getTime();
		os.write((char*)&type, sizeof(type));
		os.write((char*)&key, sizeof(key));
		os.write((char*)&time, sizeof(time));
		return os;
	}
	friend ifstream& operator>>(ifstream& os,  cRePlayData& data)
	{
		int type;
		int key;
		long long time;
		os.read((char*)&type, sizeof(type));
		os.read((char*)&key, sizeof(key));
		os.read((char*)&time, sizeof(time));
		data.setKey(key);
		data.setType(type);
		data.setTime(time);
		return os;
	}
};
class cRePlayManager
{
private:
	vector<cRePlayData>	datas;
	long long		NowTime;
	REPLAYSTATE		state;
public:
	cRePlayManager();
	~cRePlayManager();
public:
	void ReSet()
	{
		state = GAME;
		NowTime = 0;
	}
	
public:
	void Update(long long time);


public:
	void InputData(int type, int key);
	void InputData(cRePlayData data);
public:
	void SaveFile();
	void LoadFile(const string& name,vector<cRePlayData>& temp);
	inline long long getTime() const
	{
		return NowTime;
	}
	inline float getFloatTime()
	{
		return (float)NowTime / 1000.0;
	}
	inline void setTime(long long set)
	{
		NowTime = set;
	}
	inline vector<cRePlayData> getDatas() //전체 반환
	{
		return datas;
	}
};