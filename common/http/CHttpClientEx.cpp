#include "CHttpClientEx.hpp"
#include "zby_debug.h"
#include <string.h>

//AsyncGetAddrInfoEx CHttpClientEx::s_addrLookup;

CHttpClientEx::CHttpClientEx()
    : CTcpHandler(true)
    , _response(HTTP_RESPONSE)
{
    this->SetRecvHandler(this);
}

CHttpClientEx::~CHttpClientEx()
{
}

int CHttpClientEx::StartHttpClient(const char* url, const char* body, uv_loop_t* loop,AsyncGetAddrInfoEx& lookup)
{
    int ret = -1;
    do {
        if(NULL == loop) {
            SYS_ERR("LOOP null");
            break;
        }
        _loop = loop;

        this->_url = LUrlParser::clParseURL::ParseURL(url);
        if(!this->_url.IsValid()) {
            ret = this->_url.m_ErrorCode;
            SYS_ERR("url %s err code %d", url, ret);
            break;
        }
        if(!body || strlen(body) == 0) {
            this->GenGetData(body);
        } else {
            this->GenPostData(body);
        }

        lookup.Lookup(loop, this->_url.m_Host.c_str(), this);
        ret = 0;
    } while(false);
    return ret;
}

int CHttpClientEx::OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_)
{
    _sendbuf.base = &_sendData[0];
    _sendbuf.len = _sendData.size();
    uv_write(&write_req, (uv_stream_t*)(&_evtHandler), &_sendbuf, 1, NULL);
    SYS_DEBUG("%s (%s ) : %u connect", this->_url.m_Host.c_str(), pszIP_, port_ );
    return 0;
}

int CHttpClientEx::OnDisconnect(const char* pszIP_, LsUInt16 port_, Disconnet_Reason reason_)
{ 
     //bool complete = _response.Parse_ExecuteEx( _recvData.c_str(), _recvData.size()) ;
     SYS_DEBUG("%s (%s ) : %u disconnect reason %d sz %d", this->_url.m_Host.c_str(), pszIP_, port_ , reason_,  _recvData.size());
    
     OnBody( 0, _response.GetBody() );
    return 0;
}

void CHttpClientEx::SetRecvBuff(size_t suggested_size, uv_buf_t* buf)
{
    *buf = uv_buf_init((char*)malloc(suggested_size), suggested_size);
}

void CHttpClientEx::OnUvReceive(ssize_t nread, const uv_buf_t* buf)
{
    SYS_DEBUG("RECV %d", nread);
    if(nread > 0) {
         bool complete = _response.Parse_ExecuteEx(buf->base, nread) ;
         if ( complete ){
             this->Disconnect();
         }
    }
    if(buf->base) {
        free(buf->base);
    }
}

void CHttpClientEx::OnResolved(int status, const char* host, const char* pIp)
{
    if(status == 0) {
        int port;
        this->_url.GetPort(&port);
        this->Connect(pIp, port, this->_loop);
    } else {
        this->HandleConnet(false);
    }
}
void CHttpClientEx::OnBody(int status, const std::string& body)
{
    SYS_DEBUG("%d\n%s", status, body.c_str());
}
void CHttpClientEx::GenPostData(const std::string& data)
{
    std::stringstream str;

    str << "POST /" << this->_url.m_Path << " HTTP/1.1"
        << "\r\n";
    str << "Host: " << this->_url.m_Host << "\r\n";
    str << "User-Agent: curl/7.51.0"
        << "\r\n";
    str << "Accept: */*"
        << "\r\n";
    str << "Content-Length: " << data.size() << "\r\n";
    str << "Content-Type: application/x-www-form-urlencoded"
        << "\r\n";
    str << "\r\n";
    str << data;

    _sendData = str.str();
}
void CHttpClientEx::GenGetData(const std::string& data)
{
    std::stringstream str;

    str << "GET /" << this->_url.m_Path ;
    if ( this->_url.m_Query.size()>0){
        str<<'?'<<this->_url.m_Query;
    }
    str<< " HTTP/1.1"
        << "\r\n";
    str << "Host: " << this->_url.m_Host << "\r\n";
    str << "User-Agent: curl/7.51.0"
        << "\r\n";
    str << "Accept: */*"
        << "\r\n";
    str << "\r\n";

    _sendData = str.str();
}
///////////////////////////////////////////////////////
CTcpHandler* HttpFactory::CreateEvtHandler()
{
    LsUInt32 tid;
    CHttpClientEx* p = this->NewObj(tid);
    p->SetHandleID(tid);
    p->SetPFactory(this);
    return p;
}

bool HttpFactory::DeleteEvtHandler(CTcpHandler* p)
{
    bool ret = false;
    do{
        if ( NULL == p ){
            SYS_ERR("TYPE null");
            break;
        }
        LsUInt32 tid = p->GetHandleID();
        ret = this->DeletObj(tid);
    }while(false);
    return ret;
}

int HttpFactory::StartHttpClient(const char* url, const char* body, uv_loop_t* loop)
{
    int ret = -1;
    do{
        CHttpClientEx* p = (CHttpClientEx*)this->CreateEvtHandler();
        if ( NULL == p ){
            SYS_ERR("no memory");
            break;
        }
        
        ret = p->StartHttpClient(url,body,loop, this->_addLoopup);
        if ( ret ){
            this->DeleteEvtHandler(p);
        }
    }while(false);
    return ret;
}
