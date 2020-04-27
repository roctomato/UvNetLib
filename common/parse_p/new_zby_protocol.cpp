#include "new_zby_protocol.h"

NewZbyProtocol::NewZbyProtocol(int maxMsgLen ):_maxMsgLen(maxMsgLen)
{
}

NewZbyProtocol::~NewZbyProtocol()
{
}

int NewZbyProtocol::GetBodySize(LsUInt8* pHeaderBuf, int len)
{
	ZbyPacketHeader* pHeader = (ZbyPacketHeader*)pHeaderBuf;
	return pHeader->nSize - sizeof (ZbyPacketHeader);
}

int NewZbyProtocol::GetHeadSize()
{
	return sizeof (ZbyPacketHeader);
}

int NewZbyProtocol::GetMaxSize()
{
	return this->_maxMsgLen;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ZbyPacketHeader::PushTo(GenSendQueue& send, LsUInt16 cmd, LsUInt16 seq, LsUInt16 mid, LsUInt16 flag)
{
	bool ret = false;
	do {

		StringISendBuffEx*  buff = send.AddStringBuf( false ); // add header
		if ( NULL == buff ) {
			NET_ERR_LOG( "new buff err");
			break;
		}

		COutArchive&  out= buff->GetArchOur();
		this->nCmdID = cmd;
		this->nFlags = flag;
		this->nModuleID = mid;
		this->nSeq = seq;
		int total = send.GetTotalSize();
		this->nSize = sizeof(ZbyPacketHeader) + total;

		out<< *this;
		ret = true;
	} while(false);
	return ret;
}
//////////////////////////////////////////////////////////////////
bool ParseNewZbyMsg::ParseMsg(LsUInt8* pBuf_, LsUInt32 bufLen_)
{
	bool ret = false;
	do {
		if ( NULL == pBuf_){
			break;
		}
		
		header = (ZbyPacketHeader*)pBuf_;
		pBuf   = (LsInt8*)(pBuf_ + sizeof (ZbyPacketHeader)  );
		bufLen = bufLen_ - sizeof (ZbyPacketHeader);
		
		if ( header->nSize != bufLen_ ){
			break;
		}
		ret = true;
	} while(false);
	return ret;
}
