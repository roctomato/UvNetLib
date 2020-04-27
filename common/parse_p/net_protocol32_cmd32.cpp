#include "net_protocol32_cmd32.h"
#include "zby_debug.h"

NetProtocol32Cmd32::NetProtocol32Cmd32(int maxMsgLen ):_maxMsgLen(maxMsgLen)
{
}

NetProtocol32Cmd32::~NetProtocol32Cmd32()
{
}

int NetProtocol32Cmd32::GetBodySize(LsUInt8* pHeaderBuf, int len)
{
	P32M32Header* p =(P32M32Header*)pHeaderBuf;
	return p->size - sizeof (P32M32Header);;
}

int NetProtocol32Cmd32::GetHeadSize()
{
	return sizeof (P32M32Header);
}

int NetProtocol32Cmd32::GetMaxSize()
{
	return this->_maxMsgLen;
}
/*
bool ParseChatMsgEx(LsUInt8* pBuf_, LsUInt32 bufLen_, IHandle32MsgEx* handler)
{
	P32M32Header* p =(P32M32Header*)pBuf_;
	LsInt8* pData = (LsInt8*)(pBuf_ + sizeof (P32M32Header));
	handler->HandleChatMsg( *p, pData, bufLen_ - sizeof (P32M32Header));
	return true;
}
 */ 
bool P32M32Header::PushTo(GenSendQueue& send, LsUInt32 cmd)
{
	bool ret = false;
	do {

		COutArchive*  buff = send.AddArchiveBuff( false ); // add header
		if ( NULL == buff ) {
			NET_ERR( "new buff err");
			break;
		}

		COutArchive&  out= *buff;
		this->cmd  = cmd;
		this->size = sizeof(P32M32Header) + send.GetTotalSize();
		out<< *this;
		ret = true;
	} while(false);
	return ret;
}
bool ParseP32M32Msg::ParseMsg(LsUInt8* pBuf_, LsUInt32 bufLen_)
{
	bool ret = false;
	do {
		if ( NULL == pBuf_){
			break;
		}
		
		header = (P32M32Header*)pBuf_;
		pBuf   = (LsInt8*)(pBuf_ + sizeof (P32M32Header));
		bufLen = bufLen_ - sizeof (P32M32Header);
		
		if ( header->size != bufLen_){
			break;
		}
		ret = true;
	} while(false);
	return ret;
}
