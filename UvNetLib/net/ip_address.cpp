#include "ip_address.h"
#include <string.h>


bool CheckIpV4(const char* ip)
{
	const char*p = ip;
	int cnt = 0;
	for(; *p != '\0'; p++)
		if(*p == ':')
			cnt++;
	return cnt==0;
}

IpAddress::IpAddress(const char* ip, unsigned short port)
{
	this->SetAddr(ip, port);
}


void IpAddress::SetAddr(const char* ip, unsigned short port)
{
	_ip = ip;
	_port = port;
	_isIpV4 = CheckIpV4(ip);
	
	if ( !_isIpV4)
	{
		::uv_ip6_addr(ip, port, &_ipv6);
	}
	else
	{
		::uv_ip4_addr(ip, port, &_ipv4);
	}
}
const sockaddr* IpAddress::Addr()
{
     return _isIpV4 ? reinterpret_cast<const sockaddr*>(&_ipv4) : reinterpret_cast<const sockaddr*>(&_ipv6);
}
void IpAddress::InitFrom(uv_tcp_t* handle)
{
    struct sockaddr_storage addr;
    int len = sizeof(struct sockaddr_storage);
    uv_tcp_getpeername(handle, (struct sockaddr *)&addr, &len);
    InitFrom(addr);
}

void IpAddress::InitFrom(const struct sockaddr_storage& addr)
{ 
    _isIpV4 =  ( addr.ss_family == AF_INET);
    if ( _isIpV4 ){
        memcpy(&(this->_ipv4), &addr, sizeof(this->_ipv4));
        this->_ip = inet_ntoa( _ipv4.sin_addr );
        this->_port =  ntohs(_ipv4.sin_port);
    }else{
        memcpy(&(this->_ipv6), &addr, sizeof(this->_ipv6));
        this->_port =  ntohs(_ipv6.sin6_port);
        this->_ip.resize(50);
    #ifndef __WIN32__
        inet_ntop(AF_INET6, &(_ipv6.sin6_addr), &(this->_ip[0]), _ip.size());
    #endif
    }
}

void IpAddress::InitFromUdpPeer(uv_udp_t* handle)
{
    struct sockaddr_storage addr;
    int len = sizeof(struct sockaddr_storage);
    uv_udp_getpeername(handle, (struct sockaddr *)&addr, &len);
    InitFrom(addr);
}

void IpAddress::InitFromUdpLocal(uv_udp_t* handle)
{
    struct sockaddr_storage addr;
    int len = sizeof(struct sockaddr_storage);
    uv_udp_getsockname(handle, (struct sockaddr *)&addr, &len);
    InitFrom(addr);
}
