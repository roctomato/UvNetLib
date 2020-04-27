#include "CTcpAcceptor.hpp"
#include "event_loop.h"
#include "ip_address.h"
#include "zby_debug.h"

CTcpAcceptor::CTcpAcceptor()
    : _backlog(DEFAULT_BACKLOG)
    , _pFactory(nullptr)
{
    _evtHandler.data = this;
}

CTcpAcceptor::~CTcpAcceptor()
{
}
bool CTcpAcceptor::Init(const char* pHost,
    unsigned short port,
    ZbyEvtHandlerMgr* pFactory,
   event_loop& loop,
    int backlog)
{
    return Init(pHost, port,pFactory, loop.loop(), backlog );
}
bool CTcpAcceptor::Init(const char* pHost,
    unsigned short port,
    ZbyEvtHandlerMgr* pFactory,
     uv_loop_t* loop,
    int backlog)
{
    bool ret = false;
    do {
        if(nullptr == pFactory) {
            NET_ERR("factory null");
            break;
        }

        this->_pFactory = pFactory;
        uv_tcp_init(loop, &_evtHandler);
        IpAddress addr(pHost, port);
        int err = uv_tcp_bind(&_evtHandler, addr.Addr(), 0);
        if(err) {
            NET_ERR("bind %s %d create sock err %d", pHost, port, err);
            break;
        }
        this->_backlog = backlog;
        ret = true;
    } while(false);
    return ret;
}

int CTcpAcceptor::StartServer()
{
    return uv_listen((uv_stream_t*)&_evtHandler, _backlog, [](uv_stream_t* server, int status) {
        CTcpAcceptor* p = (CTcpAcceptor*)(server->data);
        if(p) {
            if ( 0 == status ){
                p->HandleAccept(server, status);
            }else{
                NET_ERR("listen err %d", status );
            }
        }
    });
}

void CTcpAcceptor::StopServer()
{
    if(::uv_is_closing((uv_handle_t*)&_evtHandler) == 0) {
        ::uv_close((uv_handle_t*)&_evtHandler, [](uv_handle_t* req) {
            CTcpAcceptor* p = (CTcpAcceptor*)req->data;
            if(p) {
                p->HandleShutdown(0);
            }
        });
    }else{
        HandleShutdown(1);
    }
}
void CTcpAcceptor::HandleAccept(uv_stream_t* server, int status)
{
    do {
        uv_loop_t* loop = server->loop;
        if(loop == nullptr) {
            NET_ERR("loop null");
            break;
        }

        if(nullptr == this->_pFactory) {
            NET_ERR("factory null");
            break;
        }

        CTcpHandler* pHandle = this->_pFactory->CreateEvtHandler();
        if(nullptr == pHandle) {
            NET_ERR("factory create client null");
            break;
        }

        pHandle->init_tcp(loop);
        pHandle->HandleAccept(server);
        // if (uv_accept(server, (uv_stream_t*) client) == 0) {
    } while(false);
}
void  CTcpAcceptor::HandleShutdown(int status)
{
}

