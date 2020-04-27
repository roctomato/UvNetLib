
#include "ChatClientHandler.hpp"
#include "ChatServerHandler.hpp"
#include "event_loop.h"

extern event_loop loop;
 
#define CHAT_PORT 50008

void test_chat(){
    ChatServer::Instance()->Listen("0.0.0.0", CHAT_PORT,loop.loop());
    ChatRobot::Instance()->InitRobot("127.0.0.1",CHAT_PORT, loop.loop());
    
    ChatRobot::Instance()->Connect(5);
    
     ChatRobot::Instance()->Start(loop.loop(), 5000, 5000 );
}
