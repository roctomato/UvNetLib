#include "TestApp.hpp"
#include "zby_debug.h"
#include "log4cpploggerex.h"
#include "ChatServerHandler.hpp"
#include "getopt.h"
#include "Archive.h"

//extern test_chat();
TestApp::TestApp()
{
}

TestApp::~TestApp()
{
}

bool TestApp::AllowExit(AppNetStack* ans)
{
    return true;
}
void test_arch()
{
    std::string v("hello");
    COutArchive out;
    out << v;
    LsUInt32 len;
    char* p = out.GetBuf(len);
    
    CInArchive in(p,len);
    std::string s;
    in >> s;
}
bool TestApp::Init(int argc, char* argv[], AppNetStack* ans)
{
    test_arch();
	std::string _logCfgFile = "server.config";
    bool bKill = false;

	do {
		int ch;
		
		while((ch = getopt(argc,argv,"Cdkc:l:"))!= -1) {
			switch ( ch ) {
			case 'k':
				bKill =true;
				break;
			case 'l':
				_logCfgFile = optarg;
				break;
			case 'd':
				ans->SetDaemon ( true );
				break;
		
			}
		}
    }while(false);
	
    try {
        InitLog<Log4cppLoggerEx>( _logCfgFile.c_str());
    } catch(ConfigureExceptionEx& e) {
        printf("open log config file %s failed. Reason %s\n", _logCfgFile.c_str(), e.what());
        return false;
    }
    if ( bKill ) {
			ans->Kill();
			exit( 0 );
	}
    SYS_INFO("INIT OK");
    return true;
}

bool TestApp::OnExit(AppNetStack* ans)
{
    SYS_INFO("OnExit");
    return true;
}

bool TestApp::OnstackStart(AppNetStack* ans)
{
    SYS_INFO("on start in loop");
      
    return true;
}
bool TestApp::StartWork(AppNetStack* ans)
{
    SYS_INFO("start ok");
    if ( !ChatServer::Instance()->Listen("0.0.0.0", 50008, ans->loop()) ){
        SYS_ERR("START chat server err");
        return false;
    }
    
    ///test_chat();
    return true;
}
void TestApp::DoStop()
{
}
