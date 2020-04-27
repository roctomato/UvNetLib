#pragma once

#include "c_tcp_handler.h"



#define DEFAULT_BACKLOG 128
    
class CTcpAcceptor
{
public:
    CTcpAcceptor();
    ~CTcpAcceptor();
    bool Init(  const char* pHost, unsigned short port , ZbyEvtHandlerMgr* pFactory, uv_loop_t* loop , int backlog=DEFAULT_BACKLOG );
    bool Init(  const char* pHost, unsigned short port , ZbyEvtHandlerMgr* pFactory, event_loop& loop, int backlog=DEFAULT_BACKLOG );
    int StartServer();
    void StopServer();
    
    void HandleAccept(uv_stream_t *server, int status);
    virtual void HandleShutdown(int status ); 
protected:
    uv_tcp_t    _evtHandler;	
    int         _backlog;
    uv_shutdown_t   _shutdown_req;
    
    ZbyEvtHandlerMgr* _pFactory;
};



