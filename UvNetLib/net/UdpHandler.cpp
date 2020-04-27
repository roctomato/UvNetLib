#include "UdpHandler.hpp"


UdpHandler::UdpHandler()
:_asConnector(false)
{
    _udp.data = this;
}

UdpHandler::~UdpHandler()
{
}

int UdpHandler::udp_init(uv_loop_t* loop)
{
    return uv_udp_init(loop, &_udp);
}

int UdpHandler::udp_init_ex(uv_loop_t* loop, unsigned int flags)
{
    return uv_udp_init_ex(loop,&_udp, flags);
}

int UdpHandler::udp_bind(const char* pHost, unsigned short port, unsigned int flags)
{
     IpAddress addr(pHost, port);
     return uv_udp_bind(&_udp, addr.Addr(), flags);
}

int UdpHandler::udp_start_recv()
{
    return uv_udp_recv_start(&_udp,
        [](uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
            UdpHandler* p = (UdpHandler*)handle->data;
            p->SetRecvBuff(suggested_size, buf);
        },
        [](uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags) {
            UdpHandler* p = (UdpHandler*)handle->data;
            IpAddress ip_addr;
            if ( addr){
                ip_addr.InitFrom(*(const struct sockaddr_storage*)addr);
            }
            p->OnUvReceive(nread, buf, ip_addr, flags);
        });
}

int UdpHandler::udp_stop_recv()
{
    return uv_udp_recv_stop(&_udp);
}

int UdpHandler::udp_send(SendBuffSptr& buf,const struct sockaddr* addr)
{
    SendUdpReq* req = new SendUdpReq(buf);
    req->data = this;
    return uv_udp_send(req, &_udp, req->GetBuf(), 1, addr, [](uv_udp_send_t* req, int status) {
        SendUdpReq* sq = (SendUdpReq*)req;
        UdpHandler* p = (UdpHandler*)req->data;
        if(p) {
            p->HandleAfterSend();
            delete sq;
        }
    }); 
}

int UdpHandler::udp_send(GenSendQueue& sq,const struct sockaddr* addr)
{
    SendBuffSptr buf = sq.Combine();
    return udp_send( buf, addr);
}
int UdpHandler::udp_connect(const char* ip, unsigned short port)
{
    _asConnector = true;
    IpAddress ip_addr(ip,port);
    return uv_udp_connect(&_udp, ip_addr.Addr());
}

/////////////////////////////////////////
SimpleUdp::SimpleUdp(int buf_size)
:_recvBuf(buf_size)
{
}

SimpleUdp::~SimpleUdp()
{
}

void SimpleUdp::ResizeBuf(int sz)
{
    this->_recvBuf.ResetSize(sz);
}

void SimpleUdp::SetRecvBuff(size_t suggested_size, uv_buf_t* buf)
{
    int len = 0;
    buf->base = (char*)this->_recvBuf.GetWriteBufSize(len);
    buf->len = len;
}

int SimpleUdp::Send(char* pBuf, int sz, const char* ip, unsigned short port )
{
    IpAddress ip_addr(ip,port);
    return Send(pBuf,sz,ip_addr);
}

int SimpleUdp::Send(char* pBuf, int sz, IpAddress& ip_addr)
{ 
    SendBuffSptr sendBuf = SimpleSendBuff::CreateEx(pBuf, sz);
    return this->udp_send( sendBuf,ip_addr.Addr());
}

int SimpleUdp::Send(char* pBuf, int sz)
{
    SendBuffSptr sendBuf = SimpleSendBuff::CreateEx(pBuf, sz);
    return this->udp_send( sendBuf,NULL);
}
