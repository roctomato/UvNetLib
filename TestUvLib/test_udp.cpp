#include "UdpHandler.hpp"
#include "event_loop.h"
#include "zby_debug.h"
#include "TimerHandler.h"

extern event_loop loop;

#define TEST_UDP_PORT 2800

class SvrUdp : public SimpleUdp
{
public:
    void Start(const char* pHost, unsigned short port, event_loop& loop)
    {
        this->udp_init(loop.loop());
        this->udp_bind(pHost, port, 0);
        this->udp_start_recv();
    }
    void OnUvReceive(ssize_t nread, const uv_buf_t* buf, IpAddress& remote, unsigned int flags) override
    {
        std::string str;
        str.assign(buf->base, nread);
        SYS_DEBUG("server recv [%s:%d]:%s", remote.GetIP(), remote.GetPort(), str.c_str());
        this->Send(buf->base, nread, remote);
    }
};

class CltUdp : public SimpleUdp, public TimerHandler
{
public:
    void Start(const char* pHost, unsigned short port, event_loop& loop)
    {
        this->udp_init(loop.loop());
        this->udp_connect(pHost, port);
        this->udp_start_recv();
        TimerHandler::Start(loop.loop(), 1000, 0);
    }
    void OnUvReceive(ssize_t nread, const uv_buf_t* buf, IpAddress& remote, unsigned int flags) override
    {
        std::string str;
        str.assign(buf->base, nread);
        SYS_DEBUG("client recv [%s:%d]:%s", remote.GetIP(), remote.GetPort(), str.c_str());
    }

    virtual bool OnTime(uint64_t now)
    {
        _n++;
        SYS_DEBUG("now %lu %d", now, _n);
        
        char temp[64];
        int sz = sprintf(temp, "send %d", _n);
        this->Send(temp, sz);
        return true;
    }
    int _n = 0;
};

SvrUdp udp_svr;
CltUdp client;

void test_udp()
{
    udp_svr.Start("0.0.0.0", TEST_UDP_PORT, loop);
    client.Start("127.0.0.1", TEST_UDP_PORT, loop);
   
}