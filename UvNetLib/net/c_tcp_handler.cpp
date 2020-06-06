#include <string.h>

#include "c_tcp_handler.h"
#include "event_loop.h"
#include "zby_debug.h"

CTcpHandler::CTcpHandler(bool asConnector, ZbyEvtHandlerMgr* pFac)
    : _pFactory(pFac)
    , _p_connect_req(nullptr)
{
    _disReason = Disconnect_Connect_Failed;

    _closeAfterSend = false;
    _netState = NET_STATE_INIT;
    _tryConnect = 0;
    _handleID = 0;

    if(asConnector) {
        this->SetAsConnect();
    }
    this->_evtHandler.data = this;
    _pHandleRecv = nullptr;
}

CTcpHandler::~CTcpHandler()
{
    if(_p_connect_req) {
        delete _p_connect_req;
    }
}

int CTcpHandler::init_tcp(uv_loop_t* loop)
{
    return uv_tcp_init(loop, &_evtHandler);
}

int CTcpHandler::init_tcp(event_loop& loop)
{
    return this->init_tcp(loop.loop());
}

void CTcpHandler::SetAsConnect()
{

    if(nullptr == _p_connect_req) {
        _p_connect_req = new uv_connect_t();
    }
    if(_p_connect_req) {
        memset(_p_connect_req, 0, sizeof(uv_connect_t));
        _p_connect_req->data = this;
    } else {
        NET_ERR("connector out of memory");
    }
}
bool CTcpHandler::ReConnect(uv_loop_t* loop)
{
    SetAsConnect();

    const char* ip = this->GetIp();
    unsigned short port = this->GetPort();
    return Connect(ip, port, loop);
}

bool CTcpHandler::Connect(const char* pHost, unsigned short port, uv_loop_t* loop)
{
    bool ret = false;
    do {
        if(!_pHandleRecv) {
            NET_ERR("cnnt %s %d no recv handler", pHost, port);
            break;
        }

        if(!_p_connect_req || !_pHandleRecv) {
            NET_ERR("cnnt %s %d not as connector", pHost, port);
            break;
        }
        if(this->_netState == NET_STATE_CONNECTING || this->_netState == NET_STATE_CONNECT) {
            NET_ERR("cnnt %s %d state %d err", pHost, port, this->_netState);
            break;
        }

        this->init_tcp(loop);
        this->_addr.SetAddr(pHost, port);
        uv_tcp_connect(_p_connect_req, &_evtHandler, _addr.Addr(), [](uv_connect_t* req, int status) {
            CTcpHandler* handle = static_cast<CTcpHandler*>(req->data);
            handle->HandleConnet(0 == status);
        });
        SetNetState(NET_STATE_CONNECTING);
        ret = true;
    } while(false);
    return ret;
}
void CTcpHandler::HandleConnet(bool success)
{
    if(success) {
        SetNetState(NET_STATE_CONNECT);
        this->OnConnect(this->_addr.GetIP(), this->_addr.GetPort(), _handleID);
        this->StartRecv();
        _tryConnect = 0;
    } else {
        this->HandleDisconnect(Disconnect_Connect_Failed);
    }
}

static void CloseCallback(uv_handle_t* handle)
{
    auto connection = static_cast<CTcpHandler*>(handle->data);
    connection->CloseComplete();
}
void CTcpHandler::HandleDisconnect(Disconnet_Reason reason)
{
    _disReason = reason;
    this->OnDisconnect(this->_addr.GetIP(), this->_addr.GetPort(), _disReason);
    SetNetState(NET_STATE_HANDLE_DISCONNECT);

    if(::uv_is_closing((uv_handle_t*)&_evtHandler) == 0) {
        ::uv_close((uv_handle_t*)&_evtHandler, CloseCallback);
    } else {
        CloseComplete();
    }
}

void CTcpHandler::CloseComplete()
{
    ZbyEvtHandlerMgr* pEvtMgr = this->GetPFactory();
    if(pEvtMgr) {
        pEvtMgr->DeleteEvtHandler(this);
    }
}

void CTcpHandler::StartRecv()
{
    ::uv_read_start((uv_stream_t*)(&this->_evtHandler),
        [](uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
            CTcpHandler* p = (CTcpHandler*)handle->data;
            p->GetRecvHandler()->SetRecvBuff(suggested_size, buf);
        },
        [](uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
            CTcpHandler* p = (CTcpHandler*)client->data;
            p->HandleRead(nread, buf);
        });
}
void CTcpHandler::HandleRead(ssize_t nread, const uv_buf_t* buf)
{
    if(nread < 0) {
        char buf[128];
        uv_strerror_r(nread, buf, sizeof buf - 1);
        NET_ERR("handle %d err %s", this->_handleID, buf);
        this->HandleDisconnect(Disconnect_By_Peer);
    } else {
        this->_pHandleRecv->OnUvReceive(nread, buf);
    }
}

void CTcpHandler::Disconnect()
{
    if(::uv_is_closing((uv_handle_t*)&_evtHandler) == 0) {

        ::uv_read_stop((uv_stream_t*)&_evtHandler);

        memset(&_shutdown_req, 0, sizeof _shutdown_req);
        _shutdown_req.data = this;
        int ret = ::uv_shutdown(&_shutdown_req, (uv_stream_t*)(&this->_evtHandler), [](uv_shutdown_t* req, int status) {
            CTcpHandler* p = (CTcpHandler*)req->data;
            if(p) {
                p->HandleShutdown(status);
            }
        });
        if(ret < 0) {
            char buf[128];
            uv_strerror_r(ret, buf, sizeof buf - 1);
            NET_ERR("handle %d err %d:%s", this->_handleID, ret, buf);
        }else{
            this->_closeAfterSend = false;
        }
        
    }
}
void CTcpHandler::HandleShutdown(int status)
{
    this->HandleDisconnect(Disconnect_By_Self);
}

void CTcpHandler::HandleAccept(uv_stream_t* server)
{
    if(uv_accept(server, (uv_stream_t*)(&this->_evtHandler)) == 0) {
        this->_addr.InitFrom(&(this->_evtHandler));
        HandleConnet(true);
    } else {
        ::uv_close((uv_handle_t*)&_evtHandler, CloseCallback);
    }
}

//////////////////////////////////////////////////////////////

int Sender::Send(uv_stream_t* stream, SendBuffSptr& buf)
{
    SendReq* req = new SendReq(buf);
    req->data = this;
    return uv_write(req, stream, req->GetBuf(), 1, [](uv_write_t* req, int status) {
        SendReq* sq = (SendReq*)req;
        Sender* p = (Sender*)req->data;
        if(p) {
            p->HandleAfterSend();
            delete sq;
        }
    });
}

int Sender::Send(uv_stream_t* stream, GenSendQueue& sq)
{
    SendBuffSptr buf = sq.Combine();
    return Send(stream, buf);
}

////////////////////////////////////////////////////////////////////////////////////////////////
CnRawSock::CnRawSock(int bufLen, bool asConnector, ZbyEvtHandlerMgr* pFac)
    : CTcpHandler(asConnector, pFac)
    , _bufLen(bufLen)
{
    this->_pBuf = (char*)malloc(bufLen);
    this->SetRecvHandler(this);
}

CnRawSock::~CnRawSock()
{
    if(this->_pBuf) {
        free(this->_pBuf);
    }
}

void CnRawSock::SetRecvBuff(size_t suggested_size, uv_buf_t* buf)
{
    buf->base = this->_pBuf;
    buf->len = this->_bufLen;
}

void CnRawSock::OnUvReceive(ssize_t nread, const uv_buf_t* buf)
{
    this->OnRecieve(buf->base, nread);
}
void CnRawSock::HandleAfterSend()
{
    if(this->_closeAfterSend && 0 == uv_stream_get_write_queue_size((uv_stream_t*)(&this->_evtHandler))) {
        this->Disconnect();
    }
}
int CnRawSock::SendMsg(char* pBuf, int len)
{
    SendBuffSptr buf = SimpleSendBuff::CreateEx(pBuf, len);
    return this->Send((uv_stream_t*)(&this->_evtHandler), buf);
}
////////////////////////////////////////////////////////////////////////////////////////////////
int Connector::Connect(uv_tcp_t& handle, const char* host, int port)
{
    int ret = -1;
    do {
        if(NULL == host) {
            SYS_ERR("host  null");
            break;
        }

        memset(&_connectReq, 0, sizeof(_connectReq));
        _connectReq.data = this;

        struct sockaddr_in dest;
        uv_ip4_addr(host, port, &dest);
        ret = uv_tcp_connect(&_connectReq, &handle, (const struct sockaddr*)&dest, [](uv_connect_t* req, int status) {
            do {
                Connector* pCl = (Connector*)(req->data);
                if(NULL == pCl) {
                    SYS_ERR("Connector null");
                    break;
                }
                pCl->OnConnect(status);
            } while(false);
        });

    } while(false);
    return ret;
}
/////////////////////////////////////////////////////
int SimpleReadEvt::StartRecv(uv_loop_t* loop)
{
    int ret = -1;
    do {
        this->_readHandler.data = this;
        ret = uv_tcp_init(loop, &this->_readHandler);
        if(ret) {
            SYS_ERR("INIT TCP ERR");
            break;
        }

        ret = uv_read_start((uv_stream_t*)(&_readHandler),
            [](uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
                *buf = uv_buf_init((char*)malloc(suggested_size), suggested_size);
            },
            [](uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
                bool deleteBuffer = true;
                do {
                    SimpleReadEvt* pCl = (SimpleReadEvt*)(tcp->data);
                    if(NULL == pCl) {
                        SYS_ERR("SimpleReadEvt null");
                        break;
                    }

                    if(nread > 0) {
                        deleteBuffer = pCl->OnRecv(nread, buf);
                    } else if(nread < 0) {
                        pCl->HandleDisconnect(Disconnect_By_Peer);
                    } else {
                        NET_WARN("recv 0 bytes");
                    }
                } while(false);

                if(buf->base && buf->len > 0 && deleteBuffer) {
                    free(buf->base);
                }
            });
        if(ret) {
            this->OnDisconnect(ret);
            this->CloseComplete();
        }
    } while(false);
    return ret;
}

void SimpleReadEvt::HandleDisconnect(int reason)
{
    this->OnDisconnect(reason);
    if(::uv_is_closing((uv_handle_t*)&_readHandler) == 0) {
        ::uv_close((uv_handle_t*)&_readHandler, [](uv_handle_t* handle) {
            SimpleReadEvt* pCl = (SimpleReadEvt*)(handle->data);
            if(NULL == pCl) {
                SYS_ERR("SimpleReadEvt null");
            } else {
                pCl->CloseComplete();
            }
        });
    } else {
        CloseComplete();
    }
}

void SimpleReadEvt::Disconnect()
{
    if(::uv_is_closing((uv_handle_t*)&_readHandler) == 0) {

        ::uv_read_stop((uv_stream_t*)&_readHandler);

        memset(&_shutdown_req, 0, sizeof _shutdown_req);
        _shutdown_req.data = this;
        ::uv_shutdown(&_shutdown_req, (uv_stream_t*)(&this->_readHandler), [](uv_shutdown_t* req, int status) {
            SimpleReadEvt* p = (SimpleReadEvt*)req->data;
            if(p) {
                p->HandleDisconnect(Disconnect_By_Self);
            }
        });
    }
}
