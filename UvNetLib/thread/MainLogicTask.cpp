#include "MainLogicTask.hpp"


/////////////////////////////////////////////////////////////////

MainLogic::MainLogic()
{
    _asycHandle.data = this;
}

bool MainLogic::Init(uv_loop_t* loop_, int cmdQueueCount)
{
    this->Resize(cmdQueueCount);
    uv_async_init(loop_, &_asycHandle, [](uv_async_t* handle) {
        MainLogic* p = (MainLogic*)(handle->data);
        if(p) {
            p->ExecCmmd();
        }
    });
    return true;
}

int MainLogic::Push(ThreadTask* pData)
{
    CAutoLocker lock(&_writeLock);
    int ret = ThreadTaskListMgr::Push(pData);
    if(0 == ret) {
        uv_async_send(&_asycHandle);
    } else {
        DB_ERR("push err %d", ret);
    }

    return ret;
}

void MainLogic::ExecCmmd()
{
    do {
        ThreadTask* p = NULL;
        int ret = Pop(p);
        if(p && ret == 0) {
            p->DoExecute(0, NULL);
            delete p;
        } else {
            break;
        }
    } while(true);
}

void MainLogic::Trigger()
{
    uv_async_send(&_asycHandle);
}

/////////////////////////////////////////////////////////////
