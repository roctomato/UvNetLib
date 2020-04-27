#include "chttphandler.h"


CHttpHandler::CHttpHandler(HttpHandleFunc&um, int bufLen)
    :_handler(um)
	,_handleState(HANDLE_STATE_CONNECT)
	,_clientID(-1)
    ,_bufLen(bufLen)
{
    this->_pBuf = (char*)malloc(bufLen);
    this->SetRecvHandler(this);
}

CHttpHandler::~CHttpHandler()
{
    if ( this->_pBuf){
        free(this->_pBuf);
    }
}

int CHttpHandler::OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_)
{
	return 0;
}

int CHttpHandler::OnDisconnect(const char* pszIP_, LsUInt16 port_, Disconnet_Reason reason_)
{
	return 0;
}

/*
bool CHttpHandler::OnRecieve(void* pBuf_, LsInt32 bufLen_)
{
	if ( _request.Parse_ExecuteEx(  (char*)pBuf_, bufLen_) ) {
		std::string body = "{hello, world}";
		_response.set_body(body);
		if ( this->HandleRequest() ) {
			this->SendResponse();
		}
	}

	return true;
}
*/

void CHttpHandler::SendResponse()
{
	std::string version = "HTTP/1.1";

	bool is_keepalive = (strcasecmp( _request.GetHeader("Connection").c_str(), "keep-alive") == 0);

	_response.gen_response( version ,is_keepalive );
	_sendData = _response.str();

    _sendbuf.base = &_sendData[0];
    _sendbuf.len = _sendData.size();
    write_req.data = this;
    uv_write(&write_req, (uv_stream_t*)(&_evtHandler), &_sendbuf, 1, [](uv_write_t* req, int status) {
       
        CHttpHandler* p = (CHttpHandler*)req->data;
        if(p) {
            //p->HandleSend(sq);
        }
    });
	_handleState = HANDLE_STATE_DONE;
	//SYS_INFO("response:\n%s", ret.c_str() );
}

bool CHttpHandler::HandleRequest()
{
	_handleState = HANDLE_STATE_HANDLING;
    return this->_handler(this->_request, this->_response, *this);
	//bool ret = true;
    /*
	if (this->_handlerList.empty() ) {
		return ret;
	}

	std::string url = this->_request.GetUrl();

	UrlMapList::iterator it  = this->_handlerList.begin() ;
	IHandleRequest* pHandler = NULL;
	for(  ; it != this->_handlerList.end(); it ++  ) {
		UrlMap& data = *it;
		std::string::size_type found = url.find( data.url );
		pHandler = data.pHandler;
		if ( found != std::string::npos && found < 2 ) {
			break;
		}
	}

	if ( pHandler && pHandler->IsValid() ) {
		ret = pHandler->HandleReq( this->_request, this->_response, *this );
	}*/
	//return ret;
}

int CHttpHandler::GetClientID()
{
	return this->_clientID;
}

Response* CHttpHandler::GetResponse()
{
	return & this->_response;
}

void CHttpHandler::SetRecvBuff(size_t suggested_size, uv_buf_t* buf)
{
    buf->base = this->_pBuf;
    buf->len  = this->_bufLen;
}

void CHttpHandler::OnUvReceive(ssize_t nread, const uv_buf_t* buf)
{
    if(nread > 0) {
         bool complete = _request.Parse_ExecuteEx(buf->base, nread) ;
         if ( complete ){
             std::string body = "{hello, world}";
            _response.set_body(body);
            if ( this->HandleRequest() ) {
                this->SendResponse();
            }
         }
    }
}

///////////////
SimpleHttpServer::SimpleHttpServer(CHttpHandler::HttpHandleFunc h, int bufLen ):_handler(h)
,_bufLen(bufLen)
,_createClient(0)
,_deleteClient(0)
{

}
CTcpHandler* SimpleHttpServer::CreateEvtHandler( )
{
	CHttpHandler* pIns = new CHttpHandler( this->_handler,_bufLen);
	if ( pIns ) {
		pIns->SetPFactory( this );
		_createClient++;
		pIns->_clientID = _createClient;
		this->_clientMap.insert(HttpClientMap::value_type(_createClient, pIns));
	}
	return pIns;
}
bool SimpleHttpServer::DeleteEvtHandler( CTcpHandler* p ) {
	CHttpHandler* pEv = dynamic_cast<CHttpHandler*>( p);
	if (  NULL == pEv )
		return false;
	this->_clientMap.erase( pEv->_clientID );
	_deleteClient++;	
	delete pEv;
	return true;
}

CHttpHandler* SimpleHttpServer::FindHttpClient(int cid)
{
	auto it = this->_clientMap.find( cid );
	if ( it != this->_clientMap.end()){
		return it->second;
	}
	return NULL;
}
int SimpleHttpServer::Start(const char* pHost, unsigned short port, uv_loop_t* loop, int backlog)
{
    int ret = -1;
    do{
        if ( ! this->Init(pHost,port,this,loop,backlog)){
            break;
        }
        ret = this->StartServer();
    }while(false);
    return ret;
}
