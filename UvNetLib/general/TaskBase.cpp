#include "TaskBase.h"
#include "zby_debug.h"

TaskBase::TaskBase()
{
	_pManager = NULL;
    _state = TimerTaskBase_State_Stop;
}

TaskBase::~TaskBase()
{
    if ( this->IsStart() ){
        this->Cancel(3);
        SYS_ERR("%s deconstruct but no finish", this->_taskTag.c_str());
    }
}

bool TaskBase::Cancel(int reason)
{
	bool ret = false;
	do {
		if (this->_state != TaskBase::TimerTaskBase_State_Start) {
			SYS_ERR("STATE err %d", this->_state);
			break;
		}
		if (this->_pos == TimerTaskBase_Pos_Now) {
			SYS_ERR("already fire err");
			break;
		}
		if (_pManager) {
			_pManager->RemoveTask(this);
		}
		this->_state = TaskBase::TimerTaskBase_State_Stop;
		this->OnCancel(reason);
		ret = true;
	} while (false);
	return ret;
}

bool TaskBase::FinishNow(int reason)
{
	bool ret = this->DoFinish(reason, false);
	if (ret && _pManager) {
		this->_endTime.tv_sec = 0;
		_pManager->RemoveTask(this);
	}
	return ret;
}

bool TaskBase::ForceFinish(int reason)
{
	this->_state = TaskBase::TimerTaskBase_State_Start;
	this->OnFinish(reason, false);
	if (_pManager) {
		_pManager->RemoveTask(this);
	}
	return true;
}

bool TaskBase::ChangeEndTime(int64_t changeMs)
{
	bool ret = true;
	do {
		if (this->_state != TaskBase::TimerTaskBase_State_Start) {
			SYS_ERR("STATE err %d", this->_state);
			break;
		}
		if (this->_pos == TimerTaskBase_Pos_Now) {
			SYS_ERR("already fire err");
			break;
		}
		if (NULL == _pManager) {
			SYS_ERR("manager null");
			break;
		}
		ret = this->_pManager->ChangeEndTime(this, changeMs);
	} while (false);
	return ret;
}

int64_t TaskBase::GetLeftTime()
{
	LsTimeVal now;
	now.GetNow();
	return _endTime - now;
}

bool TaskBase::DoFinish(int reason, bool byServer)
{
	bool ret = false;
	do {
		
		if (this->_state != TaskBase::TimerTaskBase_State_Start) {
			SYS_ERR("STATE err %d tag %s", this->_state, this->_taskTag.c_str());
			break;
		}
		//SYS_DEBUG("Do finish %s", this->_taskTag.c_str());
		this->_state = TaskBase::TimerTaskBase_State_Stop;
		this->OnFinish(reason, byServer);
		ret = true;
	} while (false);
	return ret;
}

void TaskBase::DoStart()
{
	this->_taskTag = typeid(*this).name();
	this->OnStart();
}



////////////////////////////////////////////////////////////////////////////////
TaskBaseMgr::TaskBaseMgr(int periodTime, int totalperiodTime, int tasksPerFrame, TimerTaskBase_Pos pos, int passTimeout)
	: _periodTime(periodTime), _totalperiodCount(totalperiodTime), _tasksPerFrame(tasksPerFrame), _pos(pos), _passTimeout(passTimeout)
{
	this->_totalPeriod = periodTime * totalperiodTime;
	this->_vecCurTask.resize(totalperiodTime);
	memset(&(this->_vecCurTask[0]), 0, sizeof(TaskBase*)*totalperiodTime);
	_pExchangeSet = new SetTaskBase();
	_timerWatcher.data = this;
    
    this->_curTime.GetNow();
    this->_nextTriggerTime = this->_curTime;
    this->_nextTriggerTime += _periodTime;
    this->_nextTriggerIndex = 0;

}

bool TaskBaseMgr::Start(uv_loop_t * loop)
{
	bool ret = false;
	do {
		if (NULL == loop) {
			SYS_ERR("loop null");
			break;
		}
		uv_timer_init(loop, &_timerWatcher);

		uv_timer_start(&_timerWatcher
			, [](uv_timer_t* handle)->void {
				uint64_t cur = uv_now(handle->loop);
				LsTimeVal now;
				now.GetNow();
				TaskBaseMgr* p = (TaskBaseMgr*)(handle->data);
				p->OnTimer(cur, now);
			}
			,this->_periodTime
			, this->_periodTime
			);
		this->_curTime.GetNow();
		this->_nextTriggerTime = this->_curTime;
		this->_nextTriggerTime += _periodTime;
		this->_nextTriggerIndex = 0;
		//SYS_DEBUG("%ld", uv_hrtime()/1000000);
		ret = true;
	} while (false);
	return ret;
}

void TaskBaseMgr::Stop()
{
    uv_timer_stop(&_timerWatcher);
}
void TaskBaseMgr::DoCurTask(int curidx, LsTimeVal& cur)
{
	_doCurBlock = true;
	int total = 0;
	do {
		SetTaskBase*	pCurSet = this->_vecCurTask[curidx];
		if (NULL == pCurSet) {
			break;
		}

		this->_vecCurTask[curidx] = _pExchangeSet;

		SetTaskBase::iterator it;
		for (it = pCurSet->begin(); it != pCurSet->end(); it++) {
			TaskBase* pTask = *it;

			if (pTask) {
				do {
					int64_t cur_offset = pTask->_endTime - this->_curTime;
					if ( cur_offset <= this->_passTimeout)
					{
						if (total < this->_tasksPerFrame) {
							pTask->DoFinish(0, true);
							total++;
						}
						else {
							this->OnDoNextFrame(pTask);
						}
						pTask->_pos = TimerTaskBase_Pos_Now;
						break;
					}
					
					int64_t next_offset = pTask->_endTime - this->_nextTriggerTime;
                    int64_t left = pTask->_endTime - cur;
					if (next_offset >= -_passTimeout) { //not trigger this time
						
						this->AddCurTask(pTask, left);
						//SYS_DEBUG(" left %ld ", left);
						break;
					}
					//if (cur_offset > this->_passTimeout ) {
                    //SYS_DEBUG("cur %ld pt %d ",  cur_offset, _passTimeout);
					this->OnOverTimeout(pTask, left);
					//	break;
				//	}

				} while (false);
			}
		}
		pCurSet->clear();
		_pExchangeSet = pCurSet;
	} while (false);
	_doCurBlock = false;	
}

bool TaskBaseMgr::AddCurTask(TaskBase * pTask, int64_t FinishMs)
{
	int index = this->GetTriggerIndex(FinishMs);
	//SYS_DEBUG("index %d", index);
	SetTaskBase* curSet = _vecCurTask[index];
	if (NULL == curSet) {
		curSet = new  SetTaskBase();
		if (NULL == curSet) {
			SYS_ERR("add task err, out of  memorr");
			return false;
		}
		_vecCurTask[index] = curSet;
	}

	curSet->insert(pTask);
	pTask->_pos = this->_pos;
	pTask->_index = index;

	
	return true;
}

bool TaskBaseMgr::RemoveTask(TaskBase * pTask)
{
	bool ret = false;
	do {
		if (this->_pos != pTask->_pos) {
			SYS_ERR("%s WRONG pos %d %d", pTask->GetTag(), this->_pos, pTask->_pos);
			break;
		}
		if (pTask->_index < 0 || pTask->_index >= this->_vecCurTask.size()) {
			SYS_ERR("%s wrong index %d sz %d", pTask->GetTag(), pTask->_index, this->_vecCurTask.size());
			break;
		}
		SetTaskBase* curSet = _vecCurTask[pTask->_index];
		if (curSet){
			curSet->erase(pTask);
		}
		ret = true;
	} while (false);

	return ret;
}

int TaskBaseMgr::GetTriggerIndex(int64_t FinishMs)
{
    if ( FinishMs <  this->_totalPeriod ){
        return  this->_nextTriggerIndex;
    }
    
	int left  = FinishMs % this->_totalPeriod;
	int index = left / this->_periodTime + this->_nextTriggerIndex -1;
	if (index < 0) {
		index = this->_totalperiodCount + index;
		return index;
	}
	return index  % this->_totalperiodCount;
}

int TaskBaseMgr::AddTimerTask(TaskBase * pTask, int64_t FinishMs)
{
	int ret = -1;
	do {
		if (NULL == pTask) {
			SYS_ERR("task null");
			break;
		}

		if (pTask->_state != TaskBase::TimerTaskBase_State_Stop) {
			SYS_ERR("task state %d err", pTask->_state);
			break;
		}
        /*
		if (FinishMs < this->_periodTime ) {
			SYS_ERR("finish ms %ld < %d ", FinishMs, this->_periodTime);
			break;
		}
         */
		
		if (!this->AddCurTask(pTask, FinishMs)) {
			break;
		}
        
        LsTimeVal now;
		now.GetNow();
		//pTask->_pManager = this;
		pTask->_state = TaskBase::TimerTaskBase_State_Start;

		pTask->_startTime = now;
		pTask->_endTime = pTask->_startTime;
		pTask->_endTime += FinishMs;

		pTask->_initTotalTime = FinishMs;
		
		pTask->OnStart();
		ret = pTask->_pos;
	} while (false);
	return ret;
}
void TaskBaseMgr::CheckAll()
{
    //LsTimeVal now ;
    //now.GetNow();
    SetTaskBase*	pCurSet = this->_vecCurTask[this->_nextTriggerIndex];
    
    if (NULL == pCurSet) {
		pCurSet = new  SetTaskBase();
		if (NULL == pCurSet) {
			SYS_ERR("add task err, out of  memorr");
			return ;
		}
		_vecCurTask[this->_nextTriggerIndex] = pCurSet;
	}
    
    for( auto i = 0; i < _totalperiodCount; i ++ ){
        if ( i != this->_nextTriggerIndex ){
            SetTaskBase* cs = _vecCurTask[i];
            if ( cs ){
                pCurSet->insert( cs->begin(), cs->end());
                cs->clear();
            }
        }   
    }
}

bool TaskBaseMgr::OnTimer(int64_t stamp, LsTimeVal & now)
{
	//SYS_DEBUG("%ld  %ld", stamp, uv_hrtime() / 1000000);
	//SYS_DEBUG("%s", now.GetDateTimeStr().c_str());
	this->_curTime = now;
	int cur = _nextTriggerIndex;
	int64_t offset = now - this->_nextTriggerTime;
	if (offset > 100 || offset < -2) {
		SYS_ERR("TIME ERR %ld ", offset);
	}
	//this->_nextTriggerTime = now;
	this->_nextTriggerTime  += (_periodTime+offset);
	_nextTriggerIndex++;
	_nextTriggerIndex %= _totalperiodCount;
	this->DoCurTask(cur,now);
	return true;
}

void TaskBaseMgr::OnDoNextFrame(TaskBase * pTask)
{
	SYS_DEBUG("%s do next frame", pTask->_taskTag.c_str());
}

void TaskBaseMgr::OnOverTimeout(TaskBase * pTask,int64_t left )
{
	SYS_DEBUG("%s over timeout", pTask->_taskTag.c_str());
}

////////////////////////////////////////////////////////////

TaskBaseMgrEx::TaskBaseMgrEx(int periodTime, int totalperiodTime, int tasksPerFrame, TimerTaskBase_Pos pos, int passTimeout,TimerTaskManager& ttm)
:TaskBaseMgr(periodTime, totalperiodTime,tasksPerFrame, pos, passTimeout)
,_rttMgr(ttm)
{
}

void TaskBaseMgrEx::OnOverTimeout(TaskBase* pTask,int64_t left )
{
    _rttMgr.OnOverTimeout( this->_pos, pTask, left);
}

void TaskBaseMgrEx::OnDoNextFrame(TaskBase* pTask)
{
    _hasNextFrameData = true;
    _rttMgr.OnDoNextFrame(this->_pos, pTask);
}

bool TaskBaseMgrEx::OnTimer(int64_t stamp, LsTimeVal& now)
{
    _hasNextFrameData = false;
    TaskBaseMgr::OnTimer(stamp, now);
    if (_hasNextFrameData){
        _rttMgr.OnTimer(this->_pos);
    }
    return true;
}

///////////////////////////////////////////////////
#define FAST_TIME  100
#define FAST_COUNT 100

#define PER_FRAME_DO 20

#define SLOW_TIME  10000
#define SLOW_COUNT 360

TimerTaskManager::TimerTaskManager()
:_slowClock(SLOW_TIME, SLOW_COUNT, PER_FRAME_DO, TimerTaskBase_Pos_Slow, FAST_TIME,*this)
,_fastClock(FAST_TIME, FAST_COUNT, PER_FRAME_DO, TimerTaskBase_Pos_Fast, FAST_TIME,*this)
{
	_startPerframe = false;
}

TimerTaskManager::~TimerTaskManager()
{
}

void TimerTaskManager::OnOverTimeout(TimerTaskBase_Pos pos, TaskBase* pTask,int64_t left )
{
    if ( pos == TimerTaskBase_Pos_Slow){
        this->_fastClock.AddCurTask( pTask, left );
    }else{
        SYS_ERR("%s err", pTask->GetTag());
        pTask->DoFinish(0, true);
    }
}

void TimerTaskManager::OnDoNextFrame(TimerTaskBase_Pos pos, TaskBase* pTask)
{
	_deqTask.push_back(pTask);
}

void TimerTaskManager::OnTimer(TimerTaskBase_Pos pos)
{
	if ( !_startPerframe && !this->_deqTask.empty())
	{
		uv_idle_start(&_idler, [](uv_idle_t* handle) {
			TimerTaskManager* p = (TimerTaskManager*)handle->data;
			p->DoPerFrame();
		});
		SYS_INFO("start do perframe");
		_startPerframe = true;
	}
}

void TimerTaskManager::DoPerFrame()
{
	int total = 0;
	while (!this->_deqTask.empty() && total < PER_FRAME_DO) {
		TaskBase* pTask = this->_deqTask.front();
		if (pTask) {
			pTask->DoFinish(0, true);
		}
		this->_deqTask.pop_front();
		total++;
	}

	if (this->_deqTask.empty()) {
		uv_idle_stop( &_idler );
		SYS_INFO("stop do perframe");
		_startPerframe = false;
	}
}

bool TimerTaskManager::Start(uv_loop_t* loop)
{
    bool ret = false;
    do{
        if ( NULL == loop){
            SYS_ERR("LOOP NULL");
            break;
        }
        
        if ( ! this->_fastClock.Start(loop)){
            SYS_ERR("start fast err");
            break;
        }
        
        if ( ! this->_slowClock.Start(loop)){
            SYS_ERR("start slow err");
            break;
        }
		_idler.data = this;
		uv_idle_init(loop, &_idler);
        ret = true;
    }while(false);
    return ret;
}

void TimerTaskManager::Stop()
{
    this->_fastClock.Stop();
    this->_slowClock.Stop();
}

int TimerTaskManager::AddTimerTask(TaskBase* pTask, int64_t FinishMs)
{
    int ret = -1;
    
    if ( FinishMs > this->_fastClock.TotalPeriod()){
        ret = this->_slowClock.AddTimerTask(pTask, FinishMs);
    }else{
        ret = this->_fastClock.AddTimerTask(pTask, FinishMs);
    }
	if (ret != -1) {
		pTask->_pManager = this;
	}
    return ret;
}

bool TimerTaskManager::RemoveTask(TaskBase * pTask)
{
	TaskBaseMgrEx* p = pTask->_pos == TimerTaskBase_Pos_Slow ? &_slowClock : &_fastClock;
	return p->RemoveTask(pTask);
}

bool TimerTaskManager::ChangeEndTime(TaskBase * pTask, int64_t changeMs)
{
	bool ret = false;
	do {
		LsTimeVal now;
		now.GetNow();
		
		int64_t leftTime = pTask->GetLeftTime();
		leftTime += changeMs;
		this->RemoveTask(pTask);
		if (leftTime > 0) {
			TaskBaseMgrEx* pLocate = leftTime > _fastClock.TotalPeriod() ? &_slowClock : &_fastClock;
			pLocate->AddCurTask(pTask, leftTime);
			pTask->_endTime = now;
			pTask->_endTime += leftTime;
			pTask->OnChangeTime(changeMs);
		}
		else {
			pTask->_endTime = now;
			pTask->OnChangeTime(changeMs);
			pTask->DoFinish(0, true);
			ret = true;
		}
	} while (false);
	return ret;
}
void TimerTaskManager::CheckAllSlow()
{
    this->_slowClock.CheckAll();
}
