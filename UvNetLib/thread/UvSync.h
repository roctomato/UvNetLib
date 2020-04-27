#pragma once
#include "i_lock.h"
#include  "i_event.h"
#include "uv.h"


class UvMutex:public ILock
{
public: 
    UvMutex(){
        uv_mutex_init(&_mutex);
    }
    ~UvMutex(){
        uv_mutex_destroy(&_mutex);
    }
    virtual void Lock() {
        uv_mutex_lock(&_mutex);
    }
	virtual bool TryLock(){
        return 0 == uv_mutex_trylock(&_mutex);
    }
	virtual void Unlock(){
        uv_mutex_unlock(&_mutex);
    }
	virtual void UnlockEx(bool bYield = true) {
        Unlock();
    }
private:
    uv_mutex_t _mutex;
};



