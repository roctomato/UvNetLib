#ifndef TASKBASE_H
#define TASKBASE_H

#include <list>
#include <map>
#include <set>
#include <deque>
#include <vector>

#include <uv.h>

#include "LsTimeVal.h"

class TaskBaseMgr;
class TimerTaskManager;

enum TimerTaskBase_Pos {
        TimerTaskBase_Pos_Slow,
        TimerTaskBase_Pos_Fast,
        TimerTaskBase_Pos_Now,
};

class TaskBase
{
public:
    enum TimerTaskBase_State {
        TimerTaskBase_State_Stop,
        TimerTaskBase_State_Start,
    };
	
	friend class TaskBaseMgr;
    friend class TimerTaskManager;
    
    TaskBase();
    ~TaskBase();
	bool	Cancel(int reason);
	bool    FinishNow(int reason);
	bool    ForceFinish(int reason);
	bool	ChangeEndTime(int64_t changeMs);
	bool	ChangeEndTimeSeconds(int64_t secondss) {
		return ChangeEndTime(secondss * 1000);
	}

	int64_t GetLeftTime();
	int64_t GetInitTotalTime() { return _initTotalTime / 1000; }

	TimerTaskManager* GetPManager() {
		return _pManager;
	}
    bool    IsStart() {
		return (TimerTaskBase_State_Start == _state);
	}
	virtual bool    IsFinished() {
		return TimerTaskBase_State_Stop == _state;
	}
	const LsTimeVal& GetEndTime() const {
		return _endTime;
	}
	const LsTimeVal& GetStartTime() const {
		return _startTime;
	}
    const char* GetTag(){ return this->_taskTag.c_str();}
    
	//interdface
	virtual void OnStart() {};
	virtual void OnFinish(int reason, bool byServer) {};
	virtual void OnCancel(int reason) {}
	virtual void OnChangeTime(int64_t change) {}
	//end
private:
	bool DoFinish(int reason, bool byServer);
	void DoStart();

protected:
	LsTimeVal				_startTime;
	LsTimeVal				_endTime;

	//int64_t					_passTime;
	//int64_t					_leftTime;

	int64_t                 _initTotalTime;
private:
    TimerTaskBase_State		_state;
	TimerTaskBase_Pos 		_pos;
	int				  		_index;
	
	TimerTaskManager*		_pManager;
	std::string				_taskTag;
};

//////////////////////////////////////////////////////////////////////////////////////


typedef std::set<TaskBase* > SetTaskBase;
typedef std::vector<SetTaskBase*> VecPTaskBase;
typedef std::deque<TaskBase*> DeqTaskBase;

class TaskBaseMgr
{
public:
	TaskBaseMgr(int periodTime, int totalperiodTime, int tasksPerFrame, TimerTaskBase_Pos pos, int passTimeout);

	bool	Start(uv_loop_t* loop);
	void 	Stop();

	int		AddTimerTask(TaskBase* pTask, int64_t FinishMs);
    bool	AddCurTask(TaskBase* pTask, int64_t FinishMs);
	bool	RemoveTask(TaskBase* pTask);

	virtual bool OnTimer( int64_t stamp, LsTimeVal& now);

	virtual void OnOverTimeout(TaskBase* pTask,int64_t left );
	virtual void OnDoNextFrame(TaskBase* pTask);

    int TotalPeriod() const { return _totalPeriod; }
    void CheckAll();
protected:
	void  DoCurTask(int curidx, LsTimeVal& cur);
	
	int   GetTriggerIndex(int64_t FinishMs);

	int 	_periodTime;
	int		_totalperiodCount;
	int 	_tasksPerFrame;

	int		_totalPeriod;

	LsTimeVal _curTime;
	LsTimeVal _nextTriggerTime;
	int		  _nextTriggerIndex;

	VecPTaskBase    _vecCurTask;
	SetTaskBase*	_pExchangeSet;
	bool			_doCurBlock;

	uv_timer_t			_timerWatcher;
	TimerTaskBase_Pos	_pos;
	int				    _passTimeout;
};

class TimerTaskManager;
class TaskBaseMgrEx : public TaskBaseMgr
{
public:
	TaskBaseMgrEx(int periodTime, int totalperiodTime, int tasksPerFrame, TimerTaskBase_Pos pos, int passTimeout, TimerTaskManager& ttm);
	virtual void OnOverTimeout(TaskBase* pTask,int64_t left );
	virtual void OnDoNextFrame(TaskBase* pTask);
    virtual bool OnTimer( int64_t stamp, LsTimeVal& now);
private:
    TimerTaskManager& _rttMgr;
    bool _hasNextFrameData;
};


class TimerTaskManager 
{
public:
	TimerTaskManager( );
	~TimerTaskManager();
    
    bool	Start(uv_loop_t* loop);
	void 	Stop();

	
	int		AddTimerTask(TaskBase* pTask, int64_t FinishMs);
	int		AddTimerTaskSecond(TaskBase* pTask, int64_t seconds) {
		return AddTimerTask(pTask, seconds * 1000);
	}

	bool	RemoveTask(TaskBase* pTask);
	bool	ChangeEndTime(TaskBase* pTask, int64_t changeMs);

	void OnOverTimeout(TimerTaskBase_Pos pos,TaskBase* pTask,int64_t left );
	void OnDoNextFrame(TimerTaskBase_Pos pos, TaskBase* pTask);
    void OnTimer( TimerTaskBase_Pos pos);
    void CheckAllSlow();
    
	void DoPerFrame();
    TaskBaseMgrEx _slowClock;
    TaskBaseMgrEx _fastClock;

	uv_idle_t	_idler;
	DeqTaskBase _deqTask;
	bool        _startPerframe;
};
#endif // TASKBASE_H
