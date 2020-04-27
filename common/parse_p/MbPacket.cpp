#include "MbPacket.h"
#include "zby_debug.h"

void MbClientPacketHeader::ReadFrom(CInArchive& ar)
{
    ar>>nSize>>nCmdID>>nModuleID>>nSeq;
    nSize = ntohl(nSize);
    nCmdID = ntohs(nCmdID);
    nModuleID = ntohl(nModuleID);
    nSeq = ntohl(nSeq);
}
///////////////////////////////////////////////////////////
ClientProtocol::ClientProtocol(int maxMsgLen):_maxMsgLen(maxMsgLen)
{
}

ClientProtocol::~ClientProtocol()
{
}

int ClientProtocol::GetHeadSize()
{
    return CLENT_PACK_HEADER_SIZE;
}

int ClientProtocol::GetMaxSize()
{
    return _maxMsgLen;
}

int ClientProtocol::GetBodySize(LsUInt8* pHeaderBuf, int len)
{
    MbClientPacketHeader* pHeader = (MbClientPacketHeader*)pHeaderBuf;
	return ntohl(pHeader->nSize) - CLENT_PACK_HEADER_SIZE;
}

////////////////////////////////////////////////////////////////////////////////
bool ParseClientMsg::ParseMsg(LsUInt8* pBuf_, LsUInt32 bufLen_)
{
    bool ret = false;
	do {
		if ( NULL == pBuf_){
			break;
		}
		CInArchive ar((char*)pBuf_, bufLen_);
		this->header.ReadFrom(ar);
		pBuf   = (LsInt8*)(pBuf_ + CLENT_PACK_HEADER_SIZE );
		bufLen = bufLen_ - CLENT_PACK_HEADER_SIZE;
		
		if ( header.nSize != bufLen_ ){
			break;
		}
		ret = true;
	} while(false);
	return ret;
}
//////////////////////////////////////////////////////////////////////////////
bool MbServerPacketHeader::PushTo(GenSendQueue& send, LsUInt16 cmd, LsUInt16 mid)
{
    bool ret = false;
	do {

		COutArchive*  buff = send.AddArchiveBuff( false ); // add header
		if ( NULL == buff ) {
			NET_ERR( "new buff err");
			break;
		}

		COutArchive&  out= *buff;
		this->nCmdID = htons(cmd);
		this->nModuleID = htonl(cmd);

		int total = send.GetTotalSize();
		this->nSize = htonl(SERVER_PACK_HEADER_SIZE + total);

		out<< nSize<<nCmdID<<nModuleID;
		ret = true;
	} while(false);
	return ret;

}
void MbServerPacketHeader::ReadFrom(CInArchive& ar)
{
    ar>>nSize>>nCmdID>>nModuleID;
    nSize = ntohl(nSize);
    nCmdID = ntohs(nCmdID);
    nModuleID = ntohl(nModuleID);
}

///////////////////////////////////////////////////////////////////////
ServerProtocol::ServerProtocol(int maxMsgLen):_maxMsgLen(maxMsgLen)
{
}

ServerProtocol::~ServerProtocol()
{
}

int ServerProtocol::GetHeadSize()
{
    return SERVER_PACK_HEADER_SIZE;
}

int ServerProtocol::GetMaxSize()
{
    return _maxMsgLen;
}

int ServerProtocol::GetBodySize(LsUInt8* pHeaderBuf, int len)
{
    MbServerPacketHeader* pHeader = (MbServerPacketHeader*)pHeaderBuf;
	return ntohl(pHeader->nSize) - SERVER_PACK_HEADER_SIZE;
}
/////////////////////////////////////////////////////////////////
bool ParseServerMsg::ParseMsg(LsUInt8* pBuf_, LsUInt32 bufLen_)
{
     bool ret = false;
	do {
		if ( NULL == pBuf_){
			break;
		}
		CInArchive ar((char*)pBuf_, bufLen_);
		this->header.ReadFrom(ar);
		pBuf   = (LsInt8*)(pBuf_ + SERVER_PACK_HEADER_SIZE );
		bufLen = bufLen_ - SERVER_PACK_HEADER_SIZE;
		
		if ( header.nSize != bufLen_ ){
			break;
		}
		ret = true;
	} while(false);
	return ret;
}
///////////////////////////////////////////////////////////////
ClientHandler::ClientHandler(int maxMsgLen):ClientProtocol(maxMsgLen)
{
    SetPHandleBuf(this);
}

bool ClientHandler::SendMsg(LsUInt16 msg, google::protobuf::Message* pMsg, LsUInt32 mid)
{
    if (NULL == pMsg){
        return this->SendMsg(msg, NULL, 0, mid );
    }else{
        std::string out;
        pMsg->SerializeToString(&out);
        return  this->SendMsg(msg, out, mid);
    }
}

bool ClientHandler::SendMsg(LsUInt16 msg, const std::string& value, LsUInt32 mid)
{
    const char* buf = &value[0];
	return SendMsg( msg, buf, value.size(),  mid );
}

bool ClientHandler::SendMsg(LsUInt16 msg, const char* pBuf, int bufLen, LsUInt32 mid)
{
    bool ret = false;
	do {
		if (  this->GetNetState() != NET_STATE_CONNECT){
			break;
		}
		this->_sendQueue.Reset();
		this->_sendQueue.AddBuff(  (const LsUInt8*)pBuf, bufLen,  true );
		MbServerPacketHeader head;
		head.PushTo( this->_sendQueue, msg,  mid );
		this->Send( this->_sendQueue );
		ret = true;
	} while(false);
	return ret;
}

bool ClientHandler::OnRecieve(NormalBuff& buff)
{
    bool ret = false;

	do {
		int bufLen_ ;
		LsUInt8* pBuf_   =  buff.GetReadBuf( bufLen_ );
		ParseClientMsg  parse;
		if ( ! parse.ParseMsg( pBuf_, bufLen_ ) ) {
			NET_ERR("parse err len  %d", bufLen_ );
			break;
		}
		this->HandleClientMsg( parse.header, parse.pBuf, parse.bufLen);
		ret = true;
	} while(false);

	if ( ! ret ) {
		this->Disconnect();
	}
	return 0;
}
