#include <stdio.h>
#include "event_loop.h"
#include "log4cpploggerex.h"
#include "zby_debug.h"


extern void test_http();
extern void test_http2();

extern void test_timer();
extern void test_task();
extern void test_per_frame();

extern void  test_thread();
extern void test_tcp();
extern void test_chat();
extern void test_udp();
extern void test_block_redis();

event_loop loop;
 
bool InitLog()
{
    std::string _logCfgFile = "server.config";
    try {
			InitLog(&Log4cppLoggerEx::Instance(), _logCfgFile.c_str());
    } catch (ConfigureExceptionEx& e) {
			printf("open log config file %s failed. Reason %s\n", _logCfgFile.c_str() , e.what());
			return false;
    }
    return true;
}
int main(int argc, char **argv)
{
    
	printf("%x\n",_WIN32_WINNT);
    //test_http();
    if ( InitLog() ){ 
        //test_thread();
        //test_per_frame();
        //test_http2();
        //test_timer();
        //test_task();
        //test_tcp();
        
        //test_chat();
        //test_udp();
        test_block_redis();
        loop.run();
    }
	return 0;
}
