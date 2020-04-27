#include "event_loop.h"
#include "TaskBase.h"
#include "zby_debug.h"
#include "per_frame_do_mgr.h"

extern event_loop loop;

class TestPerframe: public IRunPerFrame
{
public:
    TestPerframe(){count=100;}
    virtual bool Execute(LsUInt32 id)
    {
        SYS_DEBUG("%d %d", id, count);
        count --;
        return count;
    }
private:
    int count;
};

PerFrameDoMgr pg;
TestPerframe tp;
void test_per_frame()
{
    SYS_INFO("TEST per frame");
    pg.init_idle(loop);
    pg.AddHandler(&tp);
}