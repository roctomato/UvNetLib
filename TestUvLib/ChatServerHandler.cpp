#include "ChatServerHandler.hpp"

#include "net_protocol32_cmd32.h" // Base class: NetProtocol32Cmd32
#include "zby_debug.h"
#include <sstream>

ChatServerHandler::ChatServerHandler()
{
    this->SetPHandleBuf(this);
}
ChatServerHandler::~ChatServerHandler()
{
}

//////////////////////////////implement ZSocket //////////////////////////////////////////////////////
int ChatServerHandler::OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_)
{
    std::stringstream str;
    str << handleID_;
    this->_name = str.str();
    SYS_DEBUG("%s:%d connect name %s", pszIP_, port_, this->_name.c_str());
    return 0;
}
bool ChatServerHandler::OnRecieve(NormalBuff& buff)
{
    int headersz = this->GetHeadSize();
    int len = 0;
    LsUInt8* pHeader = buff.GetReadBuf(len);
    P32M32Header* p = (P32M32Header*)pHeader;
    if(p->cmd == 1) {
        _name.assign((char*)pHeader + headersz, len - headersz);
        SYS_DEBUG("%s register", _name.c_str());
    } else if(2 == p->cmd) {
        buff.MoveReadOffset(this->GetHeadSize());
        ChatServer::Instance()->SendAllMsg(this->_name, buff);
    }

    return true;
}
int ChatServerHandler::OnDisconnect(const char* pszIP_, LsUInt16 port_, Disconnet_Reason reason_)
{
    SYS_DEBUG("%s:%d disconnect reason %d", pszIP_, port_, reason_);
    return 0;
}
//////////////////////////////////////////////////////////////////
void ChatServer::SendAllMsg(std::string& name, NormalBuff& buff)
{
    P32M32Header p;
    p.cmd = 3;

    GenSendQueue gs;
    COutArchive* pOut = gs.AddArchiveBuff(false); // add header

    if( pOut) {

        COutArchive& out = *pOut;
        int bufLen;
        LsUInt8* pb = buff.GetReadBuf(bufLen);

        out << name;
        out.Append((char*)pb, bufLen);
        p.size = sizeof(p) + gs.GetTotalSize();
        gs.AddBuff((LsUInt8*)(&p), sizeof p, false);

        SendBuffSptr sendbuf = gs.Combine();
        EnumAllList(
            [](ChatServerHandler* data_, uint32_t id, void* pContext_) {
                SendBuffSptr* p = (SendBuffSptr*)pContext_;
                data_->Send(*p);
            }
            , &sendbuf);
    }
}
