#ifndef APPNETSTACK_H
#define APPNETSTACK_H

#ifndef _WIN32
#include <unistd.h>
#endif

#include <iostream>
#include <string>

#include "MainLogicTask.hpp"
#include "ZbyEvent.h"
#include "event_loop.h"

class AppNetStack;
class IAppStart
{
public:
    virtual bool Init(int argv, char* argc[], AppNetStack* ans) = 0;
    virtual bool StartWork(AppNetStack* ans) = 0;
    virtual bool AllowExit(AppNetStack* ans) = 0;
    virtual bool OnExit(AppNetStack* ans) = 0;
    virtual bool OnstackStart(AppNetStack* ans) = 0;
};

class AppNetStack : public event_loop
{
public:
    static AppNetStack* Instance();

    bool Init(int argv, char* argc[], IAppStart* ia);
    bool StartWork();
    void StopApp();

    bool OnStart(void* pBuf, int len);
    bool OnExit(void* pBuf, int len);


    void Kill();

    void SetPidFile(const std::string& _pidFile)
    {
        this->_pidFile = _pidFile;
    }

    void SetDaemon(bool _daemon)
    {
        this->_daemon = _daemon;
    }

    bool IsExit()
    {
        return this->_bExit;
    }

    template <typename type>
    int PushCammand(type* pIns, bool (type::*Handle)(void* pBuf, int len), void* pBuf, int len, bool bFlush = true)
    {
        int ret = _asyncCmmd.PushCammand<type>(pIns, Handle, pBuf, len);
        return ret;
    }

private:
    AppNetStack();
    ~AppNetStack();
    void SetSignal();
    void GenPidFileName(char* app);
    bool WritePid();
    pid_t ReadPid();

    static AppNetStack* s_ins;

    IAppStart* _iApp;

    std::string _pidFile;
    bool _daemon;
    bool _bExit;

    MainLogic _asyncCmmd;

    // ZbyEvent		_exitEvent;
    uv_signal_t INT_signal_watcher;
    uv_signal_t QUIT_signal_watcher;
    uv_signal_t TERM_signal_watcher;
};

#endif // APPNETSTACK_H
