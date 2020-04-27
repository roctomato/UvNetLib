#ifndef CHTTPCLIENTEX_HPP
#define CHTTPCLIENTEX_HPP

#include <map>
#include <sstream>
#include <string>

#include "uv.h"

#include "LUrlParser.h"
#include "chttpparser.h"

#include "AsyncGetAddrInfo.hpp"
#include "c_tcp_handler.h"
#include "tidfactory.h"

class CHttpClientEx : public CTcpHandler, public IHandleRecv, public IHandleAddrResutl
{
public:
    CHttpClientEx();
    ~CHttpClientEx();

    int StartHttpClient(const char* url, const char* body, uv_loop_t* loop,AsyncGetAddrInfoEx& lookup);
    
    virtual void OnBody( int status, const std::string& body );

    /////////////////////////////// implement CTcpHandler /////////////////////////////////
    int OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_) override;
    int OnDisconnect(const char* pszIP_, LsUInt16 port_, Disconnet_Reason reason_) override;

    /////////////////////////////////implement IHandleRecv////////////////////////////////
    void SetRecvBuff(size_t suggested_size, uv_buf_t* buf) override;
    void OnUvReceive(ssize_t nread, const uv_buf_t* buf) override;

    /////////////////////////////////implement IHandleAddrResutl////////////////////////
    void OnResolved(int status, const char* host, const char* pIp) override;
    ////////////////////////////////////////////////////////////////////////////////////
    
private:
    void GenPostData( const std::string& data);
    void GenGetData( const std::string& data );
    
private:
    //static AsyncGetAddrInfoEx s_addrLookup;

    uv_write_t write_req;
    uv_buf_t     _sendbuf;
    std::string _sendData;
    
    LUrlParser::clParseURL _url;
    std::string _recvData;
    CHttpParser _response;
    
    uv_loop_t*   _loop; 
};

class HttpFactory:public TIdFactory<CHttpClientEx>, public ZbyEvtHandlerMgr
{
public:
    HttpFactory(AsyncGetAddrInfoEx& a):_addLoopup(a){}
    CTcpHandler* CreateEvtHandler( );
    bool DeleteEvtHandler( CTcpHandler* p );
    int StartHttpClient(const char* url, const char* body, uv_loop_t* loop);
    AsyncGetAddrInfoEx& _addLoopup;
};
#endif // CHTTPCLIENTEX_HPP
