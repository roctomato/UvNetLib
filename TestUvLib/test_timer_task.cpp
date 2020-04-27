
#include "event_loop.h"
#include "TaskBase.h"
#include "zby_debug.h"

extern event_loop loop;


class TTask : public TaskBase
{
public:
    virtual void OnStart() {      
        SYS_INFO("start");
    }
	virtual void OnFinish(int reason, bool byServer) {
        LsTimeVal t;
        t.GetNow();
        SYS_INFO("real end time ");
        //loop.stop();
    }
};
  TimerTaskManager tt;
  TTask t2;
void test_task()
{
   
    //tt.Start(loop.loop());
    //TTask t;
    //tt.AddTimerTaskSecond(&t, 0);
   
   
    tt.AddTimerTaskSecond(&t2, 10);
    //loop.run();
}