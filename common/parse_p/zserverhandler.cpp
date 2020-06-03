
#include "zserverhandler.h"

ZServerHandler::ZServerHandler(int maxLen,bool change )
:_netChange(change), _maxMsgLen(maxLen)
{
}

ZServerHandler::~ZServerHandler()
{
}

int ZServerHandler::GetBodySize(LsUInt8* pHeaderBuf, int len)
{
	SvrMsgHeader* pheader = (SvrMsgHeader* )pHeaderBuf;
	return  pheader->size - sizeof(SvrMsgHeader) ;
}

int ZServerHandler::GetHeadSize()
{
	return sizeof(SvrMsgHeader);
}

int ZServerHandler::GetMaxSize()
{
	return this->_maxMsgLen;
}
void ZServerHandler::SetMaxMsgLen(int maxMsgLen)
{
	this->_maxMsgLen = maxMsgLen;
}

void SvrMsgHeader::AddToSend(GenSendQueue& sendQueue)
{
	this->size += ( sizeof(SvrMsgHeader) + sendQueue.GetTotalSize() );
	LsUInt8* p = (LsUInt8*)( & this->size);
	sendQueue.AddBuff( p, sizeof (SvrMsgHeader), false );
}
