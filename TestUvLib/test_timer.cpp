
#include "event_loop.h"
#include "TimerHandler.h"
#include "zby_debug.h"

extern event_loop loop;

class TestTimer:public TimerHandler
{
public:
    TestTimer():_n(0){}
    
      virtual bool OnTime(uint64_t now) { 
          _n++;
        SYS_DEBUG("now %lu %d", now, _n);
           if ( _n > 30){
               this->Stop();
           }
            return true;
      }
      
      int _n ;
};

TestTimer t;
void test_timer()
{
    t.Start(loop.loop(), 100, 100 );
}