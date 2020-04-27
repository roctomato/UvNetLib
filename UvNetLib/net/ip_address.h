#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <string>
#include <uv.h>



class IpAddress
{
public:
	IpAddress(const char* ip, unsigned short port);
	IpAddress(){}
	
    void InitFrom(uv_tcp_t* handle);
    void InitFrom(const struct sockaddr_storage& addr);
    void InitFromUdpPeer( uv_udp_t* handle);
    void InitFromUdpLocal( uv_udp_t* handle);
    
	const sockaddr* Addr();
	void SetAddr(const char* ip, unsigned short port);

	const char* GetIP(){ return _ip.c_str();}
	unsigned short GetPort(){ return this->_port; }
    
    bool operator == (const IpAddress& other){
        return _ip == other._ip && _port == other._port;
    }
private:
    bool _isIpV4;

	std::string 	_ip;
    unsigned short _port;

    sockaddr_in _ipv4;
    sockaddr_in6 _ipv6;

};



#endif // IPADDRESS_H
