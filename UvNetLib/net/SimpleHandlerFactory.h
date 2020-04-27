#pragma once

#include "c_tcp_handler.h"
#include "tidfactory.h"
#include "zby_debug.h"
#include "CTcpAcceptor.hpp"

template <typename TYPE>
class ZbySimpleEvtMgr: public  ZbyEvtHandlerMgr
{
public:
	virtual  CTcpHandler* CreateEvtHandler(   ) {
		CTcpHandler* pIns = new TYPE() ;
		if ( pIns ) {
			pIns->SetPFactory( this );
		}
		return pIns;
	}
	virtual  bool DeleteEvtHandler( CTcpHandler* p ) {
		TYPE* pEv = dynamic_cast<TYPE*>( p);
		if (  NULL == pEv )
			return false;
		delete pEv;
		return true;
	}
   
};

template <typename TYPE>
class ZbySimpleTcpServer: public ZbySimpleEvtMgr<TYPE>,public CTcpAcceptor
{
public:
     bool Listen( const char* pHost, unsigned short port , uv_loop_t* loop , int backlog=DEFAULT_BACKLOG){
        bool ret =  this->Init(pHost, port, this, loop, backlog);
        if ( ret ){
            ret = StartServer() == 0;
        }
        return ret;
    }
};



template<typename TYPE>
class ZbyIdMapEvtMgr: public ZbyEvtHandlerMgr, public TIdFactory < TYPE, LsUInt32>
{
public:
	virtual  CTcpHandler* CreateEvtHandler(   ) {
		LsUInt32 id = -1;
		TYPE* pIns = TIdFactory < TYPE, LsUInt32>::NewObj(id);
		if ( pIns ) {
			pIns->SetHandleID( id );
			pIns->SetPFactory( this );
		}
		return pIns;
	}
	virtual  bool DeleteEvtHandler( CTcpHandler* p ) {
		TYPE* pEv = dynamic_cast<TYPE*>( p);
		if (  NULL == pEv )
			return false;
		LsUInt32 id  =pEv->GetHandleID();
		return TIdFactory < TYPE, LsUInt32>::DeletObj(id);
	}
};

template <typename TYPE>
class ZbyClientRobot: public  ZbyIdMapEvtMgr<TYPE>
{
public:
    ZbyClientRobot():_loop(NULL),_port(0){
    }
    TYPE* Connect(){
        TYPE* robot = NULL;
        do{
            CTcpHandler* ret = this->CreateEvtHandler();
            if (  ret->Connect( this->_ip.c_str(), _port, _loop)){
                robot =  (TYPE*) ret;
            }
        }  while(false);
        return robot;
    }
    void Connect( int n )
    {
        for( int i = 0; i < n; i++ ){
            Connect();
        }
    }
    void InitRobot(   const char* pHost, unsigned short port, uv_loop_t* loop){
        _ip   = pHost;
        _port = port;
        _loop = loop;
    }
private:
    std::string _ip;
    uv_loop_t* _loop;
    LsUInt16     _port;
};

template <typename TYPE>
class ZbyIDTcpServer: public ZbyIdMapEvtMgr<TYPE>,public CTcpAcceptor
{
public:
     bool Listen( const char* pHost, unsigned short port , uv_loop_t* loop , int backlog=DEFAULT_BACKLOG){
        bool ret =  this->Init(pHost, port, this, loop, backlog);
        if ( ret ){
            ret = StartServer() == 0;
        }
        return ret;
    }
};