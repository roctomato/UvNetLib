#include "UvKcp.hpp"



KcpUdp::KcpUdp()
{
}

KcpUdp::~KcpUdp()
{
}

void KcpUdp::OnUvReceive(ssize_t nread, const uv_buf_t* buf, IpAddress& remote, unsigned int flags)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
UvKcp::UvKcp()
{
}

UvKcp::~UvKcp()
{
}

void UvKcp::OnConnect()
{
}

void UvKcp::OnDisconnect()
{
}
