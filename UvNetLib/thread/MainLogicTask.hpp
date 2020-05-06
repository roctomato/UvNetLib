#ifndef MAINLOGICTASK_HPP
#define MAINLOGICTASK_HPP


#include <thread>
#include <vector>

#include "UvSync.h"
#include "ThreadTask.hpp"
#include "event_loop.h"
#include "normalbuff.h"

template<typename type>
class MainLogicTask: public ThreadTask
{
public:
    MainLogicTask(type* pIns, bool(type::*Handle)(void* pBuf, int len), void* pBuf, int len)
    :_pIns(pIns)
    ,_Handle(Handle)
    {
        if ( pBuf && len > 0 ){
            _buf.assign((char*)pBuf, len);
        }
    }
    
    ~MainLogicTask() override
    {
        
    }

    void Execute( int idx, ThreadContext* param ) override
    {
        int   len  = _buf.size();
        char* pBuf = len == 0 ? NULL: &_buf[0];
        if ( _pIns && _Handle ){
           // (_pIns->(*_Handle))(pBuf, len );
            (_pIns->*_Handle)(pBuf, len );
        }
    }
    
    type* _pIns;
    bool (type::*_Handle)(void* pBuf, int len);
    std::string _buf;
};



class MainLogic : public ThreadTaskListMgr
{
public:    
    MainLogic();

    bool Init(uv_loop_t* loop_, int cmdQueueCount);
    
    template<typename type>
    int PushCammand(type* pIns, bool(type::*Handle)(void* pBuf, int len),
                    void* pBuf, int len)
    {
        MainLogicTask<type>* pTask = new   MainLogicTask<type>(pIns, Handle, pBuf, len);
        return this->Push(pTask);
    }
    
    
    void ExecCmmd();
    void Trigger();

    int Push(ThreadTask* pData) override;

private:
    uv_async_t _asycHandle;
    UvMutex  _writeLock;
};

#endif // MAINLOGICTASK_HPP
