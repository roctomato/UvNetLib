#include "old_zby_protocol.h"
#include "zby_debug.h"

bool PacketHeader::PushTo(GenSendQueue& send, LsUInt16 cmd, LsUInt16 flag, LsUInt16 mid)
{
	bool ret = false;
	do {

		COutArchive*  buff = send.AddArchiveBuff( false ); // add header
		if ( NULL == buff ) {
			NET_ERR( "new buff err");
			break;
		}

		COutArchive&  out= *buff;
		this->nCmdID = cmd;
		this->nFlags = flag;
		this->nModuleID = mid;
		//this->nDateLen = send.GetTotalSize()-1;
		//this->nSize = sizeof(PacketHeader) + nDateLen+1;
		int total = send.GetTotalSize();
		this->nDateLen = total -1 ;
		this->nSize = sizeof(PacketHeader) + total;

		out<< *this;
		ret = true;
	} while(false);
	return ret;
}
//////////////////////////////////////////////////////////////////
int OldZbyProtocol::GetBodySize(LsUInt8* pHeaderBuf, int len)
{
	PacketHeader* pHeader = (PacketHeader*)pHeaderBuf;
	return pHeader->nSize - sizeof (PacketHeader);
}

int OldZbyProtocol::GetHeadSize()
{
	return sizeof (PacketHeader);
}

int OldZbyProtocol::GetMaxSize()
{
	return 0xffff - sizeof (PacketHeader) -2;
}

bool ParseOldZbyMsg::ParseMsg(LsUInt8* pBuf_, LsUInt32 bufLen_)
{
	bool ret = false;
	do {
		if ( NULL == pBuf_){
			break;
		}
		
		header = (PacketHeader*)pBuf_;
		pBuf   = (LsInt8*)(pBuf_ + sizeof (PacketHeader)  );
		bufLen = bufLen_ - sizeof (PacketHeader)-1;
		
		if ( header->nSize != bufLen_ || header->nDateLen != bufLen){
			break;
		}
		ret = true;
	} while(false);
	return ret;
}
