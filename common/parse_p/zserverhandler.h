#ifndef ZSERVERHANDLER_H
#define ZSERVERHANDLER_H

#include "Archive.h"
#include "ProtolTcp.hpp"// Base class: NetProtocolHandler



#define INNER_CITY_MSG_MODULE  26
#define MAIL_MSG_MODULE		   30
#define MAIL_MSG_MODULE1	   31

#define PG_MSG_MODULE	       60

#include "normalbuff.h"

struct SvrMsgHeader {
	LsUInt32 size; // 包的总大小，包含包头
	LsUInt8  module; // 要发送到的模块ID
	LsUInt8  cmd; // 网络包标记，用来标记是否压缩等信息
	LsUInt16 padding;
	LsUInt32 param1;
	LsUInt32 param2;
	LsUInt32 param3;

	SvrMsgHeader() {
		size = 0;
		module = 0;
		cmd = 0;
		padding = 0;
		param1 = 0;
		param2 = 0;
		param3 = 0;
	}
	void AddToSend(GenSendQueue& sendQueue);
};

class ZServerHandler : public NetProtocolHandler /*: public  CnEvHanler,  public IHandleBuf*/
{

public:
	ZServerHandler(int maxLen, bool change =false);
	~ZServerHandler();
	
	void SetMaxMsgLen(int maxMsgLen) ;
	
	/////////implement NetProtocolHandler //////////////
	virtual int GetHeadSize() ;
	virtual int GetMaxSize()  ;
	virtual int GetBodySize( LsUInt8* pHeaderBuf, int len );
	//////////////////////////////

	bool _netChange;// 是否要做网络字节续转换
protected:
	int  _maxMsgLen;
	
};

#endif // ZSERVERHANDLER_H
