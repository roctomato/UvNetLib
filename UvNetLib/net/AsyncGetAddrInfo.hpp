#ifndef ASYNCGETADDRINFO_HPP
#define ASYNCGETADDRINFO_HPP

#include <map>
#include "uv.h"
#include "c_tcp_handler.h"

class IHandleAddrResutl
{
public:
    virtual void OnResolved(int status, const char* host, const char* pIp) = 0;
};

struct AddrIpInfo{
    int status;
    std::string ip;
};

typedef std::map<std::string,AddrIpInfo> AddrMap;


struct AddrReq{
    uv_getaddrinfo_t    addrReq;
    std::string         hostName;
    IHandleAddrResutl*  Handler;
};

class AsyncGetAddrInfoEx
{
public:
    bool Lookup( uv_loop_t* loop, const char* host, IHandleAddrResutl*  pHandler, bool cacheFirst=true);
    void ClearCache();
private:
    AddrMap m_addrMap;
    
};
#endif // ASYNCGETADDRINFO_HPP
