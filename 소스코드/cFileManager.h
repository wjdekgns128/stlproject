#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include "cSingleton.h"
#include <io.h> 
#include <direct.h>
class cFileManager :public cSingleton<cFileManager>
{
public:
	string NowLoadFileName;
public:
	cFileManager()
	{
		NowLoadFileName = "";
	}
	~cFileManager()
	{

	}
public:
	bool GetFoder(const char* name) // Ư�� �����ִ��� Ȯ�� ������ ����
	{
		int nResult = _access(name, 0);

		if (nResult == 0)
			return true;
		else
		{
			_mkdir(name);
			return false;
		}
	}
	int GetFoderInFileCount(const string& name,const string& da = ".txt") // Ư�� ������  ���ڰ���da (.txt) Ȯ������ ����
	{
		return GetFoderInFileList(name, da).size();
	}
	vector<string> GetFoderInFileList(const string& name, const string& da = ".txt") // Ư�� ������ Ư�� Ȯ���� ����Ʈ ��ȯ
	{
		vector<string> outV;
		_finddata_t fd;
		long handle;
		int result = 1;
		string find = name + "/*" + da + "*";
		handle = _findfirst(find.c_str(), &fd);
		if (handle == -1)
		{
			_findclose(handle);
			return outV;

		}
		while (result != -1)
		{
			outV.push_back(fd.name);
			result = _findnext(handle, &fd);
		}

		_findclose(handle);
		return outV;
	}
};