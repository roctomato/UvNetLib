#include "ProtolTcp.hpp"
#include "zby_debug.h"

ProtolTcp::ProtolTcp(NetProtocolHandler* pHBuf, bool asConnector, ZbyEvtHandlerMgr* pFac)
    : CTcpHandler(asConnector, pFac)
{
    this->SetPHandleBuf(pHBuf);
    this->SetRecvHandler(this);
}

ProtolTcp::~ProtolTcp()
{
}

void ProtolTcp::SetRecvBuff(size_t suggested_size, uv_buf_t* buf)
{
    int len = 0;
    if(READ_STATE_HEADER == this->_readState) {
        buf->base = (char*)this->_recvBuff._header.GetWriteBufSize(len);
        buf->len = len;
    } else if(READ_STATE_BODY == this->_readState) {
        buf->base = (char*)this->_recvBuff._recvBuf.GetWriteBufSize(len);
        buf->len = len;
    } else {
        NET_ERR("fd %d readstate err", this->_handleID);
    }
}

void ProtolTcp::OnUvReceive(ssize_t nread, const uv_buf_t* buf)
{
    if(READ_STATE_HEADER == this->_readState) {
        this->_recvBuff._header.AppendBuffer((const LsUInt8*)buf->base, nread);
        this->CheckHeader();
    } else if(READ_STATE_BODY == this->_readState) {
        this->_recvBuff._recvBuf.AppendBuffer((const LsUInt8*)buf->base, nread);
        this->CheckBody();
    } else {
        NET_ERR("fd %d readstate err", this->_handleID);
    }
}

void ProtolTcp::SetPHandleBuf(NetProtocolHandler* pHandleBuf)
{
    this->_protocolHandler = pHandleBuf;
    if(pHandleBuf && pHandleBuf->GetHeadSize() > 0) {
        _readState = READ_STATE_HEADER;
        this->_recvBuff.ResetHeaderSize(pHandleBuf->GetHeadSize());
    } else {
        _readState = READ_STATE_NO_HANDLER;
    }
}

void ProtolTcp::CheckHeader()
{
    do {
        if(!this->_recvBuff._header.IsWriteFull()) {
            break;
        }
        int len;
        LsUInt8* pBuf = this->_recvBuff._header.GetRawBuf(len);
        int bodySize = this->_protocolHandler->GetBodySize(pBuf, len);
        int msgLen = bodySize + len;
        if(bodySize < 0 || msgLen > this->_protocolHandler->GetMaxSize()) {
            NET_ERR("fd %d  buff  len %d allow %d", this->_handleID, msgLen, this->_protocolHandler->GetMaxSize());
            this->Disconnect();
            break;
        }
        this->_recvBuff.SetBodySize(bodySize);
        this->_readState = READ_STATE_BODY;
    } while(false);
}

void ProtolTcp::CheckBody()
{
    NormalBuff& nb = this->_recvBuff._recvBuf;

    if(nb.IsWriteFull()) {
        this->OnRecieve(nb);
        this->_readState = READ_STATE_HEADER;
        this->_recvBuff._header.Reset();
    }
}

void ProtolTcp::HandleAfterSend()
{
    if ( this->_closeAfterSend && 0 == uv_stream_get_write_queue_size( (uv_stream_t*)(&this->_evtHandler))){
        this->Disconnect();
    }
}

int ProtolTcp::Send(SendBuffSptr& buf)
{
    return Sender::Send((uv_stream_t*)(&this->_evtHandler), buf);
}

int ProtolTcp::Send(GenSendQueue& buf)
{
    return Sender::Send((uv_stream_t*)(&this->_evtHandler), buf);
}
