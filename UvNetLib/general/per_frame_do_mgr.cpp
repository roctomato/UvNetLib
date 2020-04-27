#include "per_frame_do_mgr.h"
#include "zby_debug.h"

#include <vector>

#define MIN_ID 1
#define MAX_ID 0XFFFF

PerFrameDoMgr::PerFrameDoMgr()
    : _curID(MIN_ID, MAX_ID)
    , _inIt(false)
    , _bStart(false)
{
}

PerFrameDoMgr::~PerFrameDoMgr()
{
}


LsUInt32 PerFrameDoMgr::AddHandler(IRunPerFrame* pHandler)
{
    if(NULL == pHandler)
        return 0;

    LsUInt32 id = this->_curID.GenID();
    RunPerFrameItem d = { id, pHandler };
    this->_runPerFrameItemMap.insert(RunPerFrameItemMap::value_type(id, d));
    if(!this->_bStart) {
        this->Start();
    }
    return id;
}

bool PerFrameDoMgr::RemoveHandler(LsUInt32 nID)
{
    bool ret = false;
    do {
        if(_inIt) {
            SYS_ERR("in iterator remove %d failed", nID);
            break;
        }
        RunPerFrameItemMap::iterator it = _runPerFrameItemMap.find(nID);
        if(it == _runPerFrameItemMap.end()) {
            SYS_ERR("not find remove %d failed", nID);
            break;
        }
        (it->second).OnRemove();
        _runPerFrameItemMap.erase(it);
        ret = true;
        CheckStop();
    } while(false);

    return ret;
}

void PerFrameDoMgr::CheckStop()
{
    if(_runPerFrameItemMap.empty()) {
        this->stop();
    }
}

void PerFrameDoMgr::DoPerFrame()
{
    _inIt = true;
    std::vector<int> clear;
    auto it = _runPerFrameItemMap.begin();
    for(; it != _runPerFrameItemMap.end(); it++) {
        RunPerFrameItem& d = it->second;
        bool doNextFrame = d.DoIt();
      
        if(!doNextFrame) {
            d.OnRemove();
            clear.push_back(it->first);
        }
    }
    for(auto i = clear.begin(); i != clear.end(); i++) {
        _runPerFrameItemMap.erase(*i);
    }
    _inIt = false;
    CheckStop();
}

void PerFrameDoMgr::Start()
{
    if(!_bStart) {
        SYS_INFO("IDLE STart");
        //this->init_idle(loop)
        this->start();
        _bStart = true;
    }
}

void PerFrameDoMgr::Stop()
{
    if(_bStart) {
        this->stop();
        SYS_INFO("IDLE STOP");
        _bStart = false;
    }
}
 
void PerFrameDoMgr::on_idle()
{
    DoPerFrame();
}
