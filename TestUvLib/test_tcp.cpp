#include "c_tcp_handler.h"
#include "event_loop.h"
#include "SimpleHandlerFactory.h"
#include "zby_debug.h"

extern event_loop loop;

class TestTcpClient: public CnRawSock
{
public:
	virtual int  OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_) 
	{
		SYS_DEBUG("connect %s %d  is connect %s\n", pszIP_, port_, this->IsConnector()?"true":"false");
		//this->Disconnect();
        char hello[]={"hello, world!"};
        this->SendMsg(hello, sizeof(hello));
		return 0;
	}
	virtual int  OnDisconnect(const char* pszIP_, LsUInt16 port_, Disconnet_Reason reason_)
	{
		SYS_DEBUG("dis %s %d reason %d\n", pszIP_, port_, reason_);		
		return 0;
	}
	virtual bool OnRecieve(void *pBuf_, LsInt32 bufLen_)
	{
		SYS_DEBUG("%s\n",(char*)pBuf_);
        return true;
	}
};

ZbySimpleTcpServer<TestTcpClient> fac;
ZbyClientRobot<TestTcpClient> robot;
   
#define PORT 50007

void test_tcp()
{ 
    robot.InitRobot("127.0.0.1",PORT, loop.loop());
    fac.Listen("0.0.0.0", PORT,loop.loop());
    
    robot.Connect( 1 );
}