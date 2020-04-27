#ifndef MBPACKET_H
#define MBPACKET_H

#include "CTcpProtocolSock.hpp"
#include <google/protobuf/message.h>

#define CLENT_PACK_HEADER_SIZE (sizeof(LsUInt32)*3 + sizeof(LsUInt16))

struct MbClientPacketHeader
{
	LsUInt32 nSize; // 包的总大小，包含包头
	LsUInt16 nCmdID; // msg id
    LsUInt32 nModuleID; // netid
	LsUInt32 nSeq; // 网络包发送序列号
	
	
	MbClientPacketHeader()
	{
		nSize = CLENT_PACK_HEADER_SIZE;
		nCmdID = 0;
		nModuleID = 0;
		nSeq = 0;
	}
    void ReadFrom(CInArchive& ar);
    
};

class ClientProtocol: public NetProtocolHandler
{
public:
	ClientProtocol(int maxMsgLen= (1024*128));
	~ClientProtocol();
	/////////implement NetProtocolHandler ////////////// 
	virtual int GetHeadSize() ;
	virtual int GetMaxSize()  ;
 	virtual int GetBodySize( LsUInt8* pHeaderBuf, int len );
	//////////////////////////////
private:
	int		_maxMsgLen;
};

struct ParseClientMsg
{
	MbClientPacketHeader header;
	LsInt8* pBuf        = NULL; 
	LsInt32 bufLen      = 0;
 
	bool ParseMsg( LsUInt8* pBuf_, LsUInt32 bufLen_);
};

//////////////////////////////////////////////////////////////////////////
#define SERVER_PACK_HEADER_SIZE (sizeof(LsUInt32)*2 + sizeof(LsUInt16))

struct MbServerPacketHeader
{
	LsUInt32 nSize; // 包的总大小，包含包头
	LsUInt16 nCmdID; // msg id
    LsUInt32 nModuleID; // netid

	MbServerPacketHeader()
	{
		nSize = SERVER_PACK_HEADER_SIZE;
		nCmdID = 0;
		nModuleID = 0;
	}
    void ReadFrom(CInArchive& ar);
    bool PushTo( GenSendQueue& send , LsUInt16 cmd, LsUInt16 mid =0 );
};

class ServerProtocol: public NetProtocolHandler
{
public:
	ServerProtocol(int maxMsgLen= (1024*128));
	~ServerProtocol();
	/////////implement NetProtocolHandler ////////////// 
	virtual int GetHeadSize() ;
	virtual int GetMaxSize()  ;
 	virtual int GetBodySize( LsUInt8* pHeaderBuf, int len );
	//////////////////////////////
private:
	int		_maxMsgLen;
};

struct ParseServerMsg
{
	MbServerPacketHeader header;
	LsInt8* pBuf        = NULL; 
	LsInt32 bufLen      = 0;
 
	bool ParseMsg( LsUInt8* pBuf_, LsUInt32 bufLen_);
};

/////////////////////////////////////////////////////////////

class ClientHandler: public CTcpProtocolSock, public ClientProtocol
{
public:
    ClientHandler(int maxMsgLen= (1024*128));
    bool SendMsg(LsUInt16 msg ,  google::protobuf::Message* pMsg,  LsUInt32 mid = 0);
    bool SendMsg( LsUInt16 msg ,  const std::string& value,  LsUInt32 mid = 0);
	bool SendMsg( LsUInt16 msg , const char* pBUf, int bufLen,  LsUInt32 mid =0);

	//implement CnProxySock
	virtual bool OnRecieve( NormalBuff& buff) ;
	//////////////////////////////////////////////////////
	
	virtual void HandleClientMsg(MbClientPacketHeader& header, LsInt8* pHeaderBuf, int len)=0;
private:
	GenSendQueue  _sendQueue;
};
#endif // MBPACKET_H
