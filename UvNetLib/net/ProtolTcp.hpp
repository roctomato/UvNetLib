#ifndef PROTOLTCP_HPP
#define PROTOLTCP_HPP

#include "c_tcp_handler.h" // Base class: CTcpHandler
#include "normalbuff.h"

/*
协议包收取接口，假设网络协议由包头和包体组成
框架调用 GetHeadSize(),得到包头长度，然后先接受包头长度的数据，接着调用GetBodySize(),把包头数据传入，得到包体长度
框架判断包体长度是否落在 GetMaxSize()范围内，是则收数据，否则断开连接
*/
class NetProtocolHandler
{
public:
    virtual int GetHeadSize() = 0;                             //包头长度
    virtual int GetMaxSize() = 0;                              //最大消息长度
    virtual int GetBodySize(uint8_t* pHeaderBuf, int len) = 0; // 包体长度，注意此长度不包含消息头长度
};

enum READ_STATE {
    READ_STATE_NO_HANDLER,
    READ_STATE_HEADER,
    READ_STATE_BODY,
    READ_STATE_RAW,
};

class ProtolTcp : public CTcpHandler, public Sender, public IHandleRecv
{
public:
    ProtolTcp(NetProtocolHandler* pHBuf = NULL, bool asConnector = false, ZbyEvtHandlerMgr* pFac = NULL);
    ~ProtolTcp();

    void SetPHandleBuf(NetProtocolHandler* pHandleBuf);
    int Send( SendBuffSptr& buf);
    int Send( GenSendQueue& buf);
    
    virtual bool OnRecieve( NormalBuff& buff)  = 0;
    
    void SetRecvBuff(size_t suggested_size, uv_buf_t* buf) override;
    void OnUvReceive(ssize_t nread, const uv_buf_t* buf) override;

    void HandleAfterSend() override;
    
private:
    void CheckHeader();
    void CheckBody();

public:
    NetProtocolHandler* _protocolHandler;
    READ_STATE _readState;

private:
    RecvBuffEx _recvBuff;
};

#endif // PROTOLTCP_HPP
