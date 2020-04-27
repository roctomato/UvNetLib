#include "TimerHandler.h"

TimerHandler::TimerHandler()
{
    _timerWatcher.data = this;
}

TimerHandler::~TimerHandler()
{
}
int TimerHandler::Start(uv_loop_t* _loop, uint64_t repeat, uint64_t timeout)
{  
    if ( 0 == timeout){
        timeout = repeat;
    }
    uv_timer_init  (  _loop, &_timerWatcher  );
  
    int ret = uv_timer_start ( &_timerWatcher
    ,[](uv_timer_t* handle)->void{
        uint64_t cur = uv_now( handle->loop);
        TimerHandler* p = (TimerHandler*)(handle->data);
        p->OnTime(cur);
    },
     timeout, repeat  );
    
    return ret;
}

int TimerHandler::Stop()
{
    return uv_timer_stop(&_timerWatcher);
}
