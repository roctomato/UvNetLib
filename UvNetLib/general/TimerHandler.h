#ifndef TIMERHANDLER_H
#define TIMERHANDLER_H
#include <uv.h>

class TimerHandler
{
public:
    TimerHandler();
    virtual ~TimerHandler();

    /*
     * Start the timer. timeout and repeat are in milliseconds.
     * If timeout is zero, the callback fires on the next event loop iteration. If repeat is non-zero, 
     * the callback fires first after timeout milliseconds and then repeatedly after repeat milliseconds.
     */
    int Start(uv_loop_t* _loop, uint64_t repeat, uint64_t timeout=0);
    
    int Stop();
    
    virtual bool OnTime(uint64_t now) = 0;
private:
    uv_timer_t  _timerWatcher;
};

#endif // TIMERHANDLER_H
