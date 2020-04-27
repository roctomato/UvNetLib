#ifndef ASYNCREDIS_H
#define ASYNCREDIS_H

#include "hiredis.h"
#include "async.h"
#include "libuv_adapt.h"
#include "chiredisbase.h"

class AsyncRedis;

typedef bool (*HandleRedis)(redisAsyncContext *c,AsyncRedis* redis, CHiredisReply& reply, void* param);

struct HackFunc
{
    AsyncRedis* redis       = NULL;
    void*       param       = NULL;
    HandleRedis fn          = NULL;
    bool        auto_delete = true;
};

class AsyncRedis {
public:
	enum REDIS_STATE{
		REDIS_STATE_DISCONNECT,
		REDIS_STATE_CONNECTING,
		REDIS_STATE_CONNECTED,
	};
 	AsyncRedis();
	~AsyncRedis();
    bool Connect(const char *ip, int port, uv_loop_t* loop, int index=0, const char* password=NULL);
    int  Exec( HandleRedis fn, void* param,const char *format, ...);
    int  ExecRepeatCallback( HandleRedis fn, void* param,const char *format, ...);
    
	bool IsConnect(){ return this->_bConnect;}
	bool IsDisconnect(){ return _cnntState == REDIS_STATE_DISCONNECT; }
    redisAsyncContext * _context;
    
  
	void        HandleConnect(int status );
	void        HandleDisconnet(int status );
	void        HandleAuthPassword( int status );
	
    virtual void OnConnect( int status );
    virtual void OnDisconnect( int status);
    
    
    static void ConnectCallback(const redisAsyncContext *c,int status);
    static void DisonnectCallback(const redisAsyncContext *c, int status);
    static void CmdCallback(redisAsyncContext *c, void *r, void *privdata) ;  
   
    
protected:
	int					_redisIdx;
	bool			    _bConnect;
	REDIS_STATE		    _cnntState;
	const char*         _password;
};

#endif // ASYNCREDIS_H
