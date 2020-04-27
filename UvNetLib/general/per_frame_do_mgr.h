#ifndef PERFRAMEDOMGR_H
#define PERFRAMEDOMGR_H

#include "event_loop.h"
#include "tidfactory.h"
#include "z_typedef.h"
#include "z_idle_handler.h"

class IRunPerFrame
{
public:
    virtual bool Execute(LsUInt32 id) = 0; // return false will remove this handler
    virtual void OnRemove()
    {
    } // call after remove
};

struct RunPerFrameItem {
    LsUInt32 _nID;
    IRunPerFrame* _pHandler;
    bool DoIt()
    {
        if(_pHandler)
            return _pHandler->Execute(_nID);
        return false;
    }
    void OnRemove()
    {
        if(_pHandler)
            _pHandler->OnRemove();
    }
};

typedef std::map<LsUInt32, RunPerFrameItem> RunPerFrameItemMap;

class PerFrameDoMgr : public z_idle_handler
{
public:
    PerFrameDoMgr();
    ~PerFrameDoMgr();

    LsUInt32 AddHandler(IRunPerFrame* pHandler);
    bool RemoveHandler(LsUInt32 nID);
  
    void Start();
    void Stop();
    void DoPerFrame();
    virtual void on_idle();

private:
    void CheckStop();
    LsUInt32 GenID();

  


private:
    TGenID<LsUInt32> _curID;
    RunPerFrameItemMap _runPerFrameItemMap;
    bool _inIt;
    bool _bStart;
};

#endif // PERFRAMEDOMGR_H
