#ifndef CHTTPHANDLER_H
#define CHTTPHANDLER_H

#include <list>
#include <functional>

#include "z_typedef.h"
#include "event_loop.h"
#include "c_tcp_handler.h"
#include "CTcpAcceptor.hpp"
#include "zby_debug.h"
#include "chttpparser.h"



class CHttpHandler;

class IHandleRequest
{
public:
	virtual bool HandleReq( CHttpParser& req, Response& res, CHttpHandler& handler )=0; // return true send response immediatily
	bool    IsValid() {
		return _valid;
	}

	IHandleRequest():_valid(true) {}	
	void SetValid(bool _valid) {
		this->_valid = _valid;
	}
protected:
	bool	_valid;

};

struct UrlMap {
	std::string     url;
	IHandleRequest *pHandler;
};

//typedef std::list < UrlMap > UrlMapList;

class CHttpHandler :  public CTcpHandler, public IHandleRecv
{
public:
	enum{
		HANDLE_STATE_CONNECT,
		HANDLE_STATE_HANDLING,
		HANDLE_STATE_DONE
	};
    
    typedef std::function<bool ( CHttpParser& req, Response& res, CHttpHandler& handler)> HttpHandleFunc;
	
    CHttpHandler(HttpHandleFunc&um,	int bufLen = 10*1024);
	~CHttpHandler();
   
    ////implement CTcpHandler
	virtual int  OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_) override;
	virtual int  OnDisconnect(const char* pszIP_, LsUInt16 port_, Disconnet_Reason  reason_) override;
    
   /////////////////////////////////implement IHandleRecv////////////////////////////////
    void SetRecvBuff(size_t suggested_size, uv_buf_t* buf) override;
    void OnUvReceive(ssize_t nread, const uv_buf_t* buf) override;  
  
    //////////////////////////////////////////////////////////////////
    
    //bool OnRecieve(void *pBuf_, LsInt32 bufLen_) ;
	bool      HandleRequest();
	void      SendResponse();
	Response* GetResponse();
	int		  GetClientID();
	
    uv_write_t   write_req;
    uv_buf_t     _sendbuf;
    std::string _sendData;
    
	Response	_response;
	CHttpParser _request;

	HttpHandleFunc&	_handler;
	int         _handleState;
	int     _clientID;

    int     _bufLen;
    char*   _pBuf;
};

typedef std::map<int, CHttpHandler*> HttpClientMap;

/////////////////////////////////////////////////////////////
class SimpleHttpServer:public CTcpAcceptor,  public ZbyEvtHandlerMgr 
{
public:
	SimpleHttpServer(CHttpHandler::HttpHandleFunc h, int bufLen = 10*1024);
    int Start (const char* pHost, unsigned short port ,  uv_loop_t* loop, int backlog=DEFAULT_BACKLOG );
    
	CHttpHandler* FindHttpClient( int cid );
	
	virtual  CTcpHandler* CreateEvtHandler( ); 
	virtual  bool DeleteEvtHandler( CTcpHandler* p );
protected:
	HttpClientMap _clientMap;
    CHttpHandler::HttpHandleFunc	_handler;
	
    int 		_bufLen;
    int 	_createClient;
	int		_deleteClient;
};

#endif // CHTTPHANDLER_H
