#include "TestApp.hpp"
#include "zby_debug.h"
#include "log4cpploggerex.h"
#include "ChatServerHandler.hpp"
extern test_chat();
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

bool TestApp::Init(int argv, char* argc[], AppNetStack* ans)
{
    std::string _logCfgFile = "server.config";
    try {
        InitLog(&Log4cppLoggerEx::Instance(), _logCfgFile.c_str());
    } catch(ConfigureExceptionEx& e) {
        printf("open log config file %s failed. Reason %s\n", _logCfgFile.c_str(), e.what());
        return false;
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
