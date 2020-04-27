#ifndef NETPROTOCOL32CMD32_H
#define NETPROTOCOL32CMD32_H

#include "ProtolTcp.hpp"// Base class: NetProtocolHandler



struct P32M32Header
{
	LsUInt32 size;
	LsUInt32 cmd; // 1 rigister 2 chat 3 chat ntf
	
	bool PushTo( GenSendQueue& send , LsUInt32 cmd);
};

class NetProtocol32Cmd32 : public NetProtocolHandler
{
public:
	NetProtocol32Cmd32(int maxMsgLen= (1024*128) );
	~NetProtocol32Cmd32();


	///////implement NetProtocolHandler /////////////////
	virtual int GetHeadSize() ;
	virtual int GetMaxSize()  ;
 	virtual int GetBodySize( LsUInt8* pHeaderBuf, int len );
	/////////////////////////////////////////////////////
private:
	int		_maxMsgLen;
};

//////////////////parse recv msg /////////////////////////////////

struct ParseP32M32Msg
{
	P32M32Header* header= NULL;
	LsInt8* pBuf        = NULL; 
	LsInt32 bufLen      = 0;
 
	bool ParseMsg( LsUInt8* pBuf_, LsUInt32 bufLen_);
};




#endif // NETPROTOCOL32CMD32_H
