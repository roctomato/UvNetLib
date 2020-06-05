#ifndef OLDZBYPROTOCOL_H
#define OLDZBYPROTOCOL_H

#include "ProtolTcp.hpp" // Base class: NetProtocolHandler

struct PacketHeader
{
    static const LsUInt16 HEAD_SIZE = 10;
	LsUInt16 nSize; // 包的总大小，包含包头
	LsUInt16 nCmdID; // msg id
	LsUInt16 nFlags; // 网络包标记，用来标记是否压缩等信息
	LsUInt16 nModuleID; // 要发送到的模块ID
	LsUInt16 nDateLen;
	PacketHeader()
	{
		nSize = 0;
		nCmdID = 0;
		nFlags = 0;
		nModuleID = 0;
		nDateLen = 0;
	}
	
	bool PushTo( GenSendQueue& send , LsUInt16 cmd=0, LsUInt16 flag=0, LsUInt16 mid =0 );
    bool ReadFrom(CInArchive& arch);
};

class OldZbyProtocol : public NetProtocolHandler
{
public:
	/////////implement NetProtocolHandler ////////////// 
	virtual int GetHeadSize() ;
	virtual int GetMaxSize()  ;
 	virtual int GetBodySize( LsUInt8* pHeaderBuf, int len );
	//////////////////////////////
};

struct ParseOldZbyMsg
{
	PacketHeader head;
	LsInt8* pBuf        = NULL; 
	LsInt32 bufLen      = 0;
 
	bool ParseMsg( LsUInt8* pBuf_, LsUInt32 bufLen_);
};

/*
class OldZbyFilter: public IClientProtocol, public OldZbyProtocol
{
public:
	virtual NetProtocolHandler* GetClientProtocol()    { return this;}
	virtual int CheckZbyRpcType( void * pBuf, int len ){ 
		PacketHeader* pHeader = (PacketHeader*)pBuf;
		return pHeader->nCmdID/1000;
	}
};
*/
#endif // OLDZBYPROTOCOL_H
