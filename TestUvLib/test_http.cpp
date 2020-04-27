#include "http.h"
#include "chttphandler.h"
#include "CHttpClientEx.hpp"
#include "event_loop.h"

extern event_loop loop;

void HandleHttp(http::Request & req, http::Response& res)
{
    res.setStatus(200);
    res.setHeader("Connection", "keep-alive");
    res.setHeader("Content-Type", "text/plain");
    res<<"hello world";
    res<<std::endl;
}



void test_http()
{
   
    http::Server svr(HandleHttp);
    //svr.listen("localhost",9090, loop.loop());
    svr.listen("127.0.0.1",9090, loop.loop());
    
    
}

bool HandleReq( CHttpParser& req, Response& res, CHttpHandler& handler ); 

SimpleHttpServer  svr(HandleReq);

bool HandleReq( CHttpParser& req, Response& res, CHttpHandler& handler ) 
{
    static int count = 0;   
    res.set_head("Content-Type", "text/plain");
    char temp [64];
    sprintf(temp, "hello world ,this ok %d", count);
    ++count;
    res.SetBody( temp );
    if ( count >= 10 ){
        svr.StopServer();
    }
    return true;
}

AsyncGetAddrInfoEx a;
HttpFactory  h(a);
    
void test_http_client()
{
    //h.StartHttpClient("http://www.163.com/","", loop.loop());
    h.StartHttpClient("http://127.0.0.1:9090/","", loop.loop());
}

void test_http2()
{
    svr.Start("127.0.0.1",9090, loop.loop());
    test_http_client();
}