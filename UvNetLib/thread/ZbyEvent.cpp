#include "ZbyEvent.h"
#include <chrono> 

ZbyEvent::ZbyEvent()
{
}

ZbyEvent::~ZbyEvent()
{
}

bool ZbyEvent::WaitEvent(int timeout_)
{
    bool ret;
    std::unique_lock<std::mutex> lck(_mtx);
    if(-1 == timeout_) {
        _cv.wait(lck);
        ret = true;
    }else{
        ret = _cv.wait_for(lck,std::chrono::seconds(timeout_)) == std::cv_status::no_timeout;
    }   
    return ret;
}

int ZbyEvent::SetEventEx(bool broadcast)
{
    if(broadcast) {
        _cv.notify_all();
    } else {
        _cv.notify_one();
    }
    return 0;
}


void ZbyEvent::SetEvent()
{
    SetEventEx(false);
}

void ZbyEvent::ResetEvent()
{
}
