#ifndef UDPHANDLER_HPP
#define UDPHANDLER_HPP

#include "z_typedef.h"
#include <uv.h>


#include "normalbuff.h"
#include "ip_address.h"

class SendUdpReq: public uv_udp_send_t
{
public:
    SendUdpReq(SendBuffSptr& buf): _sendBuf(buf)
	{
        int len;
        this->_uvbuf.base = _sendBuf->GetRawBuf(&len);
        this->_uvbuf.len  = len;
    }
    
    uv_buf_t* GetBuf(){ 
        return &(this->_uvbuf);
    }
private:
    SendBuffSptr _sendBuf;
    uv_buf_t     _uvbuf;
};

class UdpHandler
{
public:
    UdpHandler();
    ~UdpHandler();
    
    int udp_init(uv_loop_t* loop);
    int udp_init_ex(uv_loop_t* loop,  unsigned int flags);
    int udp_bind(const char* pHost, unsigned short port, unsigned int flags);
    int udp_connect(const char* pHost, unsigned short port);
    
    int udp_start_recv();
    int udp_stop_recv();
    
    int udp_send( SendBuffSptr& buf,const struct sockaddr* addr);
    int udp_send( GenSendQueue& buf,const struct sockaddr* addr);
    
    virtual void SetRecvBuff(size_t suggested_size, uv_buf_t* buf) = 0;
    virtual void OnUvReceive(ssize_t nread, const uv_buf_t* buf, IpAddress& remote,unsigned int flags ) = 0;
    virtual void HandleAfterSend(){};
    
    uv_udp_t _udp;
    bool     _asConnector;
};

#define SIMPLE_UDP_SIZE 1400

class SimpleUdp: public UdpHandler
{
public:
    SimpleUdp(int buf_size = SIMPLE_UDP_SIZE);
    ~SimpleUdp();
    
    int Send(char* pBuf, int sz, const char* pHost, unsigned short port);
    int Send(char* pBuf, int sz, IpAddress& remote);
    int Send(char* pBuf, int sz);
    
    void ResizeBuf( int sz);
    void SetRecvBuff(size_t suggested_size, uv_buf_t* buf) override;
    
    NormalBuff _recvBuf;
};
#endif // UDPHANDLER_HPP
