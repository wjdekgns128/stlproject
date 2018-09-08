#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
template <class T>
class cSingleton
{
protected:
	cSingleton()
	{

	}
	virtual ~cSingleton()
	{

	}
public:
	static T* getinstance()
	{
		if (Instance == NULL)
			Instance = new T;
		return Instance;
	}
	static void DestroyInstance()
	{
		SAFE_DELETE(Instance)
	};
private:
	static T * Instance;
};
template <typename T> T * cSingleton<T>::Instance = 0;
