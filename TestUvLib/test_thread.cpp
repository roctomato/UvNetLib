#include "ThreadTask.hpp"
#include "MWorkThread.hpp"

extern event_loop loop;

class TestTask: public ThreadTask
{
public:    
    void Execute( int idx, ThreadContext* param) override
    {
        DB_DEBUG("DO %d", _index);
        if ( _index % 3 == 2){
            throw "hello";
        }
    }
	void HandleResult(bool excuteOk ) override
    {
        DB_DEBUG("handle result  %d excute %s", _index, excuteOk?"ok":"failed");
    }                    
    
    TestTask( int n ):_index(n){
        this->SetAutoDelete();
    }
    
    ~TestTask()
    {
        DB_DEBUG("dector %d", _index);
    }
    
    int _index;
};

class TContext: public ThreadContext
{
public:
    bool Init(MWorkThread& thread, uv_loop_t* loop_) override
    { 
        DB_INFO("INIT");
        return true;
    }
    void OnStart() override{
        DB_INFO("START");
    }
    
    void OnEnd() override{
        DB_INFO("END");
    }
    
    void OnWaitTimeout(int timeoutTimes) override{
        //DB_INFO("timeout %d",timeoutTimes);
    }
};
MWorkThreadMgr thrd;
TContext cnxt;

void test_thread()
{
    int count = 3;
    for( int i =0; i < count; i ++ ){
        std::shared_ptr<MWorkThread> p(new MWorkThread() );
        p.get()->Init(2,2, loop.loop(), cnxt);
        thrd.AddThread(p);
    }
    
     for( int i = 0; i < count +3; i ++ ){
        int r = thrd.PushTask( new TestTask(i));
        DB_DEBUG("push %d result %d", i, r );
    }
    
    thrd.Start();
    //thrd.Stop();
}
void test_thread_old()
{
    int count = 3;
    ThreadTaskListMgr t(count);
    ThreadTaskListMgr t2(count);
    
    for( int i = 0; i < count +3; i ++ ){
        int r = t.Push( new TestTask(i));
        DB_DEBUG("push %d result %d", i, r );
    }
    
    do{
        ThreadTask* p  = NULL;
        int ret = t.Pop(p);
        DB_DEBUG("ret %d", ret );
        if (ret == 0 ){
            if ( p ){
                p->DoExecute(1, &cnxt);
                t2.Push(p);
            
            }
        }else{
            break;
        }
    }while(true );
    
     do{
        ThreadTask* p  = NULL;
        int ret = t2.Pop(p);
        DB_DEBUG("ret %d", ret );
        if ( p && ret == 0 ){
            p->DoHandleResult( );
            delete p;
        }else{
            break;
        }
    }while(true );
}