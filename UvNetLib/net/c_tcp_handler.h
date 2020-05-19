#ifndef CTCPHANDLER_H
#define CTCPHANDLER_H

#include "z_typedef.h"
#include <uv.h>

#include "ip_address.h"
#include "normalbuff.h"

class ZbyEvtHandlerMgr;
class event_loop;

class IHandleRecv
{
public:
    virtual void SetRecvBuff(size_t suggested_size, uv_buf_t* buf) = 0;
    virtual void OnUvReceive(ssize_t nread, const uv_buf_t* buf) = 0;
};

class SendReq: public uv_write_t
{
public:
    SendReq(SendBuffSptr& buf): _sendBuf(buf)
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

class Sender
{
public:
    int Send(uv_stream_t* stream, SendBuffSptr& buf);
    int Send(uv_stream_t* stream, GenSendQueue& sq);
    virtual void HandleAfterSend() {}
    virtual ~Sender(){}
};

enum Disconnet_Reason {
    Disconnect_By_Self,
    Disconnect_By_Peer,
    Disconnect_Connect_Failed,
};
enum NET_STATE {
    NET_STATE_INIT,
    NET_STATE_HANDLE_CONNECT,
    NET_STATE_CONNECTING,
    NET_STATE_CONNECT,
    NET_STATE_HANDLE_DISCONNECT,
};

class CTcpHandler
{
public:
    CTcpHandler(bool asConnector = false, ZbyEvtHandlerMgr* pFac = NULL);
    virtual ~CTcpHandler();

    int init_tcp(uv_loop_t* loop);
    int init_tcp(event_loop& loop);

    bool Connect(const char* pHost, unsigned short port, uv_loop_t* loop);
    void Disconnect();

    void HandleAccept(uv_stream_t* server);
    void HandleConnet(bool success);
    void HandleDisconnect(Disconnet_Reason reason);
    void HandleRead(ssize_t nread, const uv_buf_t* buf);
    void HandleShutdown(int status);

    ////////////////////////////////////////////////////////////////////////////////////
    virtual int OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_) = 0;
    virtual int OnDisconnect(const char* pszIP_, LsUInt16 port_, Disconnet_Reason reason_) = 0;
    //////////////////////////////////////////////////////////////////////////////////////

    void SetCloseFlag()
    {
        _closeAfterSend = true;
    }

    int GetDisReason()
    {
        return this->_disReason;
    }

    int GetNetState()
    {
        return this->_netState;
    }
    void SetNetState(int state)
    {
        _netState = state;
    }
    bool IsConnector()
    {
        return this->_p_connect_req != nullptr;
    }
    void SetAsConnect();

    void SetTryConnect(int _tryConnect)
    {
        this->_tryConnect = _tryConnect;
    }

    void SetPFactory(ZbyEvtHandlerMgr* _pFactory)
    {
        this->_pFactory = _pFactory;
    }

    ZbyEvtHandlerMgr* GetPFactory()
    {
        return _pFactory;
    }

    void SetRecvHandler(IHandleRecv* handler)
    {
        _pHandleRecv = handler;
    }

    IHandleRecv* GetRecvHandler()
    {
        return _pHandleRecv;
    }

    void SetHandleID(LsUInt32 handleID)
    {
        this->_handleID = handleID;
    }

    LsUInt32 GetHandleID()
    {
        return _handleID;
    }

    const char* GetIp() 
    {
        return _addr.GetIP();
    }
    
    int GetPort()
    {
        return _addr.GetPort();
    }
    
    virtual void CloseComplete();

protected:
    void StartRecv();

protected:
    IpAddress   _addr;

    uv_tcp_t _evtHandler;
    uv_shutdown_t _shutdown_req;
    uv_connect_t* _p_connect_req;

    IHandleRecv* _pHandleRecv;

    int _tryConnect;
    bool _closeAfterSend;
    Disconnet_Reason _disReason;
    int _netState;
    LsUInt32 _handleID;

    ZbyEvtHandlerMgr* _pFactory;
};

class ZbyEvtHandlerMgr
{
public:
    virtual CTcpHandler* CreateEvtHandler() = 0;
    virtual bool DeleteEvtHandler(CTcpHandler* p) = 0;
};


class CnRawSock:  public CTcpHandler, public Sender, public IHandleRecv
{
public:
    CnRawSock(int bufLen = 100*1024,bool asConnector=false,  ZbyEvtHandlerMgr* pFac = NULL);
    ~CnRawSock();
    
    int SendMsg(char* pBuf, int len );
    virtual bool OnRecieve(void *pBuf_, LsInt32 bufLen_) =0;
    
    ///implement IHandleRecv
    virtual void SetRecvBuff(size_t suggested_size, uv_buf_t *buf) override;
	virtual void OnUvReceive(ssize_t nread, const uv_buf_t* buf) override;
    
    //////////Sender /////////////////////////////////////////////
    void HandleAfterSend() override;
    //////////////////////////////////////////////////////////////////
private:
    int     _bufLen;
    char*   _pBuf;
};
 
class Connector
{
public:
    int Connect( uv_tcp_t& handle, const char* ip, int port); 
    virtual void OnConnect(int status ) = 0;
private:
    uv_connect_t    _connectReq;
};

class SimpleReadEvt
{
public:
    enum Disconnet_Reason
    {
        Disconnect_By_Self,
        Disconnect_By_Peer,
        Disconnect_Connect_Failed,
    };
    
    int  StartRecv(uv_loop_t* loop);
    void Disconnect();
    
    void HandleDisconnect(int reason);
    
    virtual void CloseComplete(){}
    
    virtual void OnDisconnect(int reason ) = 0;
    virtual bool OnRecv( ssize_t nread, const uv_buf_t* buf) = 0;
protected:
    
    uv_tcp_t        _readHandler;
    uv_shutdown_t   _shutdown_req;
};

#endif // CTCPHANDLER_H
