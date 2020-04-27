#ifndef ZBYEVENT_H
#define ZBYEVENT_H

#include "i_event.h"
#include <mutex>          // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable


class ZbyEvent:public IEvent
{
public:
    ZbyEvent();
    ~ZbyEvent();
    
    virtual bool WaitEvent(int timeout_ = -1);
    virtual int SetEventEx(bool broadcast);
    virtual void SetEvent() ;
	virtual void ResetEvent();
private:
    std::mutex  _mtx; 
    std::condition_variable _cv;
};

#endif // ZBYEVENT_H
