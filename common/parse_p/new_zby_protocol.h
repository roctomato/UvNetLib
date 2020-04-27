#ifndef NEWZBYPROTOCOL_H
#define NEWZBYPROTOCOL_H

#include "CTcpProtocolSock.hpp"

struct ZbyPacketHeader
{
	LsUInt32 nSize; // 包的总大小，包含包头
	LsUInt16 nCmdID; // msg id
	LsUInt16 nSeq; // 网络包发送序列号
	LsUInt16 nModuleID; // 要发送到的模块ID
	LsUInt16 nFlags; // 网络包标记，用来标记是否压缩等信息
	
	ZbyPacketHeader()
	{
		nSize = sizeof(ZbyPacketHeader);
		nCmdID = 0;
		nFlags = 0;
		nModuleID = 0;
		nSeq = 0;
	}
	
	bool PushTo( GenSendQueue& send , LsUInt16 cmd, LsUInt16 seq, LsUInt16 mid =0, LsUInt16 flag=0 );
};

class NewZbyProtocol: public NetProtocolHandler
{
public:
	NewZbyProtocol(int maxMsgLen= (1024*128));
	~NewZbyProtocol();
	/////////implement NetProtocolHandler ////////////// 
	virtual int GetHeadSize() ;
	virtual int GetMaxSize()  ;
 	virtual int GetBodySize( LsUInt8* pHeaderBuf, int len );
	//////////////////////////////
private:
	int		_maxMsgLen;
};

struct ParseNewZbyMsg
{
	ZbyPacketHeader* header= NULL;
	LsInt8* pBuf        = NULL; 
	LsInt32 bufLen      = 0;
 
	bool ParseMsg( LsUInt8* pBuf_, LsUInt32 bufLen_);
};

#endif // NEWZBYPROTOCOL_H
