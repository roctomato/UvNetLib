#pragma once

#include <stddef.h>

template <typename T>
class SingletonT
{
protected:
	SingletonT(){}
	virtual ~SingletonT(){}

public:
	static T *Instance()
	{
		if (!ms_pInstance)
		{
			ms_pInstance = new T();
		}
		return ms_pInstance;
	}
	
	static void Destroy()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}

private:
	static T* ms_pInstance;
};

template<class T>
T* SingletonT<T>::ms_pInstance = NULL;