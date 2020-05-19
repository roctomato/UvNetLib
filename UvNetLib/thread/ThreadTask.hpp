#ifndef THREADTASK_HPP
#define THREADTASK_HPP

#include <uv.h>

#include <list>

#include "ZbyEvent.h"
#include "zby_debug.h"

#define DEFAULT_QUEUE  1000
#define DEAFULT_WAIT_SECONDS 3

class MWorkThread;

class ThreadContext
{
public:
    virtual bool Init(MWorkThread& thread, uv_loop_t* loop_){ return true;}
    virtual void OnStart() {}
    virtual void OnEnd(){}
    virtual void OnWaitTimeout(int timeoutTimes){}
    virtual int  QueueCount(){ return DEFAULT_QUEUE; }
    virtual int  WaitSeconds(){ return  DEAFULT_WAIT_SECONDS; }
    virtual ~ThreadContext(){}
};

class ThreadTask
{
public:
	virtual void Execute( int idx, ThreadContext* param )=0;  // excute  in work thread return true need execute HandleResult
	virtual void HandleResult(bool excuteOk ) {}                    // execute in logic thread
	virtual      ~ThreadTask()  {}

    ThreadTask():_callHandleResult(true), _excuteOk(false),_autoDelete(false){}
    
	void DoExecute(int idx, ThreadContext* param) {
		_excuteOk = false;
		try{
			 this->Execute(idx, param);
			_excuteOk = true;
		}catch(...){
			DB_ERR( "thread task err");
			_excuteOk = false;
			_callHandleResult = true;
		}
	}

    void DoHandleResult(){
        try{
			 this->HandleResult( _excuteOk );
		}catch(...){
			DB_ERR( "thread handle result  err");
		}
    }
    void SetNeedResult(){
        _callHandleResult = true;
    }
    
	bool NeedHandleResult() {
		return _callHandleResult;
	}
	
	bool ExecuteOk(){ return _excuteOk; }
    
    void SetAutoDelete(){
        _autoDelete = true;
    }
    
    bool AutoDelete(){
        return _autoDelete;
    }
    
private:
    bool _callHandleResult;
    bool _excuteOk;
    bool _autoDelete;
};

typedef std::list<ThreadTask*> ThreadTaskList;

class ThreadTaskListMgr
{
public:
     enum MSG_QUEUE_ERR_CODE {
        enumNoneErr = 0,
        enumNullErr = -1,
        enumFullErr = -2,
       
        enumQueueEmpty = -3,
        enumQueueOverflow = -4,
        
        enumTimeOut = -6,
        
        enumNoData  = -7,
    };
    
    ThreadTaskListMgr()
    :_size(0)
    { 
        _Reset();
    }
    
    ThreadTaskListMgr( int n)
    :_taskList(n, NULL)
    ,_size(n)
    {
        _Reset();
        
    }
    
    void Resize(int n )
    {
        _taskList.resize(n, NULL);
        _size = n;
        _Reset();
    }
    
    virtual  int Push(ThreadTask* pData )
    {
        int ret = -1;
        do{
            if(NULL == pData) {
                ret = enumNullErr;
                break;
            } 
            
            if ( IsFull() ){
                ret = enumFullErr;
                break;
            }
            
            ThreadTask* & cur = *_writeIt;
            cur = pData;
            _writeIt ++;
            if ( _writeIt == _taskList.end() ){
                _writeIt = _taskList.begin();
            }
            _totalPushCmmd ++;
            ret = enumNoneErr;
        }while(false);
        return ret;
    }
    
    virtual  int Pop(ThreadTask* & data) {
        int ret = -1;
        data = NULL;
        do {
            if ( this->IsEmpty() ){
                ret = enumQueueEmpty;
                break;
            }
            data = *this->_readIt;
            _readIt ++;
            if ( _readIt == _taskList.end() ){
                _readIt = _taskList.begin();
            }
            _totalPopCmmd ++;
            ret = enumNoneErr;
        }while(false);
        return ret;
    }
    
    int ReadCount()
    {
        return (int)( _totalPushCmmd - _totalPopCmmd );
    }
    
    bool IsFull()
    {
        return ReadCount() >= _size;
    }
    
    bool IsEmpty()
    {
        return _totalPushCmmd == _totalPopCmmd;
    }
    
protected:
    void _Reset()
    {
        _readIt  = _taskList.begin();
        _writeIt = _taskList.begin();
        _totalPushCmmd = 0;
        _totalPopCmmd  = 0;
    }
    
    ThreadTaskList  _taskList;
    int             _size;
    
    ThreadTaskList::iterator _readIt;
    ThreadTaskList::iterator _writeIt;
    
    int64_t  _totalPushCmmd;
    int64_t  _totalPopCmmd;
};
#endif // THREADTASK_HPP
