#include "old_zby_protocol.h"
#include "zby_debug.h"

bool PacketHeader::PushTo(GenSendQueue& send, LsUInt16 cmd, LsUInt16 flag, LsUInt16 mid)
{
    bool ret = false;
    do {

        COutArchive* buff = send.AddArchiveBuff(false); // add header
        if(NULL == buff) {
            NET_ERR("new buff err");
            break;
        }
        int total = send.GetTotalSize();

        COutArchive& out = *buff;
        this->nCmdID = cmd;
        this->nFlags = flag;
        this->nModuleID = mid;
        this->nDateLen = total - 1;
        this->nSize = HEAD_SIZE + total;
        out << nSize << nCmdID << nFlags << nModuleID << nDateLen;
        ret = true;
    } while(false);
    return ret;
}
bool PacketHeader::ReadFrom(CInArchive& arch)
{
    try {
        arch >> nSize >> nCmdID >> nFlags >> nModuleID >> nDateLen;
    } catch(...) {
        SYS_ERR("PARSE head err");
        return false;
    }
    return true;
}
//////////////////////////////////////////////////////////////////
int OldZbyProtocol::GetBodySize(LsUInt8* pHeaderBuf, int len)
{
    CInArchive arch((char*)pHeaderBuf, len);
    PacketHeader head;
    head.ReadFrom(arch);
    return head.nSize - PacketHeader::HEAD_SIZE;
}

int OldZbyProtocol::GetHeadSize()
{
    return PacketHeader::HEAD_SIZE;
}

int OldZbyProtocol::GetMaxSize()
{
    return 0xffff - sizeof(PacketHeader) - 2;
}

bool ParseOldZbyMsg::ParseMsg(LsUInt8* pBuf_, LsUInt32 bufLen_)
{
    bool ret = false;
    do {
        if(NULL == pBuf_) {
            break;
        }
        CInArchive arch((char*)pBuf_, bufLen_);
        head.ReadFrom(arch);
        pBuf = (LsInt8*)(pBuf_ + PacketHeader::HEAD_SIZE) - 2;
        bufLen = bufLen_ - PacketHeader::HEAD_SIZE;

        if(head.nSize != bufLen_) {
            SYS_ERR("PARSE head err");
            break;
        }
        ret = true;
    } while(false);
    return ret;
}
