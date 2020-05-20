#ifndef MWORKTHREAD_HPP
#define MWORKTHREAD_HPP

#include <thread>
#include <vector>

#include "ThreadTask.hpp"
#include "UvSync.h"
#include "event_loop.h"

class ThreadSide : public ThreadTaskListMgr
{
public:
    ThreadSide();
    ThreadSide(int n);

    void SetWaitSeconds(int seconds);
    void Trigger();

    int Push(ThreadTask* pData) override;
    int Pop(ThreadTask*& data) override;

private:
    bool _isBlock;

    int _waitSecond;

    ZbyEvent _event;
    UvMutex _writeLock;
};

class LogicSide : public ThreadTaskListMgr
{
public:
    LogicSide();

    bool Init(uv_loop_t* loop_, int cmdQueueCount);
    void ExecCmmd();
    void Trigger();

    int Push(ThreadTask* pData) override;

private:
    uv_async_t _asycHandle;
};

class MWorkThread : public std::thread
{
    static void StartThread(MWorkThread* p);

public:
    MWorkThread();
    ~MWorkThread();

    bool Init(ThreadContext* pcontext, uv_loop_t* loop_);
    bool Start(int idx);
    int PushTask(ThreadTask* p);

    int GetIdx()
    {
        return _threadIdx;
    }

    bool IsWorking()
    {
        return _working;
    }

    bool IsStop()
    {
        return _stop;
    }
    int GetUnHandleCount()
    {
        return _threadSideQueue.ReadCount();
    }

    virtual int Run();
    virtual void Stop();

    virtual void Dump();

private:
    bool _active;
    bool _working;
    bool _stop;

    int _threadIdx;
    ZbyEvent _blockEvt;

    ThreadSide _threadSideQueue;
    LogicSide _logicSideQueue;
    ThreadContext* _context;
};

class MWorkThreadMgr
{
public:
    MWorkThreadMgr();
    template <typename T, typename... P> bool Init(int thread_count, uv_loop_t* loop_, P... args)
    {
        bool ret = true;
        do {
            for(int i = 0; i < thread_count; i++) {
                std::shared_ptr<MWorkThread> p(new MWorkThread());
                T* pCxt = new T( args...);
                if(!p.get()->Init(pCxt, loop_)) {
                    ret = false;
                    break;
                }
                this->AddThread(p);
            }
        } while(false);

        return ret;
    }
    
     template <typename T, typename... P> int PushTaskEx(int index,  P... args)
    {
        int ret = -1;
        do {
            T * pTask = new T( args ...);
            pTask->SetAutoDelete();
            if ( 0 == index ){
                PushTask(pTask);
            }else{
                PushTask(index, pTask);
            }
        } while(false);
        return ret;
    }
    
    void AddThread(std::shared_ptr<MWorkThread>& thrd);

    bool Start();
    void Stop();
    void Join();
    bool IsAnyRunning();
    int PushTask(ThreadTask* p);
    int PushTask(int index, ThreadTask* p);

protected:
    int _curIdx;
    int _totalPush;
    int _okPush;
    std::vector<std::shared_ptr<MWorkThread>> _threadArray;
};
#endif // MWORKTHREAD_HPP
