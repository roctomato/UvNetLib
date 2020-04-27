#ifndef MWORKTHREAD_HPP
#define MWORKTHREAD_HPP

#include <thread>
#include <vector>

#include "UvSync.h"
#include "ThreadTask.hpp"
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
    UvMutex  _writeLock;
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

    bool Init(int count, int waitSecond,uv_loop_t* loop_, ThreadContext& context);
    bool Start(int idx);
    int PushTask( ThreadTask* p );

    
    int GetIdx(){
        return _threadIdx;
    }

    bool IsWorking(){
        return _working;
    }
    
    int GetUnHandleCount(){
        return _threadSideQueue.ReadCount();
    }
    
    virtual int Run();
    virtual void Stop();

    virtual void Dump();

private:
    bool _active;
    bool _working;
    
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
    void AddThread( std::shared_ptr<MWorkThread>& thrd );
    bool Start();
    void Stop();
    void Join();
    
    int PushTask( ThreadTask* p );
    int PushTask( int index, ThreadTask* p );
protected:
    int _curIdx;
    int _totalPush;
    int _okPush;
    std::vector<std::shared_ptr<MWorkThread>> _threadArray;
};
#endif // MWORKTHREAD_HPP
