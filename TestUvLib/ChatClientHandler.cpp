#include "ChatClientHandler.hpp"
#include "zby_debug.h"
#include <sstream>

ChatClientHandler::ChatClientHandler()
{
    this->SetPHandleBuf(this);
    this->SetAsConnect();
}

ChatClientHandler::~ChatClientHandler()
{
}

bool ChatClientHandler::OnRecieve(NormalBuff& buff)
{
    int len = 0;
    LsUInt8* pHeader = buff.GetReadBuf(len);
    CInArchive ain((char*)pHeader, len);
    P32M32Header h;
    ain >> h;
    if(h.cmd == 3) {
        std::string name;
        std::string content;
        ain >> name >> content;
        SYS_INFO("[%s]:%s", name.c_str(), content.c_str());
    }
    return true;
}

int ChatClientHandler::OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_)
{
    SYS_DEBUG("%s:%d connect name %d", pszIP_, port_, handleID_);
    std::stringstream ss;
    ss << "hello from " << port_;
    this->SendChat(ss.str());
    return 0;
}

int ChatClientHandler::OnDisconnect(const char* pszIP_, LsUInt16 port_, Disconnet_Reason reason_)
{
    SYS_DEBUG("%s:%d disconnect reason %d", pszIP_, port_, reason_);
    return 0;
}
void ChatClientHandler::SendChat(const std::string& chat)
{
    P32M32Header h;
    h.cmd = 2;

    GenSendQueue gs;
    COutArchive* pOut = gs.AddArchiveBuff(false); // add header

    if(pOut) {
        COutArchive& out = *pOut;
        out << chat;
    }
    h.PushTo(gs, 2);
    this->Send(gs);
}

void ChatRobot::SendAllChat(const std::string& chat)
{
    P32M32Header h;
    h.cmd = 2;

    GenSendQueue gs;
    COutArchive* pOut = gs.AddArchiveBuff(false); // add header

    if(pOut) {
        COutArchive& out = *pOut;
        out << chat;
    }
    h.PushTo(gs, 2);

    SendBuffSptr sendbuf = gs.Combine();
    EnumAllList(
        [](ChatClientHandler* data_, uint32_t id, void* pContext_) {
            SendBuffSptr* p = (SendBuffSptr*)pContext_;
            data_->Send(*p);
        },
        &sendbuf);
}
int n = 1;
bool ChatRobot::OnTime(uint64_t now)
{
     std::stringstream ss;
    ss << "send no. " <<n;
    n++;
    this->SendAllChat(ss.str());
    return true;
}
