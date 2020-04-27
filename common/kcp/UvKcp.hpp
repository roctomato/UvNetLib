#ifndef UVKCP_HPP
#define UVKCP_HPP

#include "UdpHandler.hpp" // Base class: SimpleUdp

class KcpUdp : public SimpleUdp
{
public:
    KcpUdp();
    ~KcpUdp();
    void OnUvReceive(ssize_t nread, const uv_buf_t* buf, IpAddress& remote,unsigned int flags ) override;
     
    IpAddress   _remote;
};

typedef std::shared_ptr<KcpUdp> ShareUdp;

class UvKcp
{
public:
    UvKcp();
    ~UvKcp();
    
    virtual void OnConnect();
    virtual void OnDisconnect();
    
    ShareUdp    _udp;
};

#endif // UVKCP_HPP
