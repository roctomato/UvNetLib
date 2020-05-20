#include "MWorkThread.hpp"
#include <assert.h>

#define WAIT_SECONDS 5

ThreadSide::ThreadSide()
    : _isBlock(false)
    , _waitSecond(WAIT_SECONDS)
{
}

ThreadSide::ThreadSide(int n)
    : ThreadTaskListMgr(n)
    , _isBlock(false)
    , _waitSecond(WAIT_SECONDS)
{
}

void ThreadSide::SetWaitSeconds(int seconds)
{
    _waitSecond = seconds;
}

int ThreadSide::Push(ThreadTask* pData)
{
    CAutoLocker lock(&_writeLock);
    int ret = ThreadTaskListMgr::Push(pData);
    if(ret == 0 && _isBlock) {
        _event.SetEventEx(true);
    }
    return ret;
}

int ThreadSide::Pop(ThreadTask*& data)
{
    int ret = -1;
    do {
        if(this->IsEmpty()) {
            _isBlock = true;
            if(!_event.WaitEvent(_waitSecond)) {
                ret = enumTimeOut;
                break;
            } else {
                _isBlock = false;
            }
        }
        ret = ThreadTaskListMgr::Pop(data);
    } while(false);
    return ret;
}
void ThreadSide::Trigger()
{
    _event.SetEventEx(true);
}
/////////////////////////////////////////////////////////////////

LogicSide::LogicSide()
{
    _asycHandle.data = this;
}

bool LogicSide::Init(uv_loop_t* loop_, int cmdQueueCount)
{
    this->Resize(cmdQueueCount);
    uv_async_init(loop_, &_asycHandle, [](uv_async_t* handle) {
        LogicSide* p = (LogicSide*)(handle->data);
        if(p) {
            p->ExecCmmd();
        }
    });
    return true;
}

int LogicSide::Push(ThreadTask* pData)
{
    int ret = ThreadTaskListMgr::Push(pData);
    if(0 == ret) {
        uv_async_send(&_asycHandle);
    } else {
        DB_ERR("push err %d", ret);
    }

    return ret;
}

void LogicSide::ExecCmmd()
{
    do {
        ThreadTask* p = NULL;
        int ret = Pop(p);
        if(p && ret == 0) {
            p->DoHandleResult();
            if(p->AutoDelete()) {
                delete p;
            }
        } else {
            break;
        }
    } while(true);
}

void LogicSide::Trigger()
{
    uv_async_send(&_asycHandle);
}

/////////////////////////////////////////////////////////////
void MWorkThread::StartThread(MWorkThread* p)
{
    p->_blockEvt.SetEventEx(true);
    p->_active = true;
    p->Run();
}

MWorkThread::MWorkThread()
    : _active(false)
    , _working(false)
    ,_stop(true)
{
}

MWorkThread::~MWorkThread()
{
}

bool MWorkThread::Start(int idx)
{
    if ( NULL == this->_context ){
        DB_ERR("context null");
        return false;
    }
    
    this->_threadIdx = idx;
    std::thread& thisThrd = (*this);
    thisThrd = std::thread(StartThread, this);
    _blockEvt.WaitEvent();
    return _active;
}

bool MWorkThread::Init(ThreadContext* pcontext, uv_loop_t* loop_)
{
    if ( NULL == pcontext){
         DB_ERR("context null");
        return false;
    }
    int count = pcontext->QueueCount();
    int waitSecond = pcontext->WaitSeconds();
    
    _threadSideQueue.Resize(count);
    _threadSideQueue.SetWaitSeconds(waitSecond);

    _logicSideQueue.Init(loop_, count);
    _context = pcontext;
    return pcontext->Init(*this, loop_);
}

int MWorkThread::Run()
{
    assert(_context);
    _stop = false;
    int timeOutTimes = 0;
    this->_context->OnStart();
    while( !(!this->_active && _logicSideQueue.IsEmpty())) {
        try {
            ThreadTask* pTask = NULL;
            int ret = this->_threadSideQueue.Pop(pTask);
            if(ThreadTaskListMgr::enumTimeOut == ret) {
                int no_trigger = this->_logicSideQueue.ReadCount();
                if ( no_trigger > 0 ){
                    DB_WARN("lost msg count %d", no_trigger );
                    _logicSideQueue.Trigger();
                }else{
                    timeOutTimes++;
                    this->_context->OnWaitTimeout(timeOutTimes);
                }
            } else if(pTask) {
                _working = true;
                pTask->DoExecute( this->_threadIdx, this->_context );
                _logicSideQueue.Push(pTask);
                _working = false;
            }
        } catch(...) {
            DB_ERR("thread %d other err", _threadIdx);
            _working = false;
        }
    }
    _stop = true;
    this->_context->OnEnd();
    return 0;
}

void MWorkThread::Stop()
{
    this->_active = false;
    this->_threadSideQueue.Trigger();
}



void MWorkThread::Dump()
{
}
int MWorkThread::PushTask(ThreadTask* p)
{
    return _threadSideQueue.Push(p);
}
////////////////////////////////////////////////////////////////
MWorkThreadMgr::MWorkThreadMgr()
    : _curIdx(0)
    , _totalPush(0)
    , _okPush(0)
{
}

void MWorkThreadMgr::AddThread(std::shared_ptr<MWorkThread>& thrd)
{
    this->_threadArray.push_back(thrd);
}

bool MWorkThreadMgr::Start()
{
    bool ret = true;
    int threadCount = _threadArray.size();
    for(int i = 0; i < threadCount; i++) {
        MWorkThread* pThrd = _threadArray[i].get();
        if(!pThrd->Start(i)) {
            ret = false;
            break;
        }
    }
    return ret;
}

void MWorkThreadMgr::Stop()
{
    int threadCount = _threadArray.size();
    for(int i = 0; i < threadCount; i++) {
        MWorkThread* pThrd = _threadArray[i].get();
        pThrd->Stop();
    }
}

void MWorkThreadMgr::Join()
{
    int threadCount = _threadArray.size();
    for(int i = 0; i < threadCount; i++) {
        MWorkThread* pThrd = _threadArray[i].get();
        pThrd->join();
    }
}

int MWorkThreadMgr::PushTask(ThreadTask* p)
{
    int threadCount = _threadArray.size();
    int tryTimes = threadCount + 1;
    int ret = -1;
    int select = -1;

    int minIndex = -1;
    int minWaitQueue = 0;

    do {
        if(0 == threadCount) {
            SYS_ERR("no thread now");
            break;
        }

        if(_curIdx < 0 || _curIdx >= threadCount)
            _curIdx = _curIdx % threadCount;

        for(int i = _curIdx; i < _curIdx + threadCount; i++) {
            int cur = i < threadCount ? i : i - threadCount;
            MWorkThread* pThrd = _threadArray[cur].get();
            if(!pThrd->IsWorking()) {
                select = cur;
                break;
            } else {
                if(minIndex == -1 || pThrd->GetUnHandleCount() < minWaitQueue) {
                    minIndex = cur;
                    minWaitQueue = pThrd->GetUnHandleCount();
                }
            }
        }

        if(select > -1) {
            _curIdx = select;
        } else {
            _curIdx = minIndex;
        }

        MWorkThread* pDoThrd = _threadArray[_curIdx].get();

        ret = pDoThrd->PushTask(p);
        if(0 == ret) {
            _okPush++;
        } else {
            SYS_ERR("push data to thread %d err %d", _curIdx, ret);
            tryTimes--;
        }

        _curIdx++;
    } while(ret && tryTimes > 0);
    _totalPush++;
    return ret;
}

int MWorkThreadMgr::PushTask(int index, ThreadTask* p)
{
    index = index % _threadArray.size();
    return _threadArray[index].get()->PushTask(p);
}
bool MWorkThreadMgr::IsAnyRunning()
{
    bool ret = false;
    int threadCount = _threadArray.size();
    for(int i = 0; i < threadCount; i++) {
        MWorkThread* pThrd = _threadArray[i].get();
        if ( !pThrd->IsStop() ){
            ret = true;
            break;
        }
    }
    return ret;
}
