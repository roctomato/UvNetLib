#ifndef CHATCLIENTHANDLER_HPP
#define CHATCLIENTHANDLER_HPP

#include "ProtolTcp.hpp" // Base class: ProtolTcp
#include "net_protocol32_cmd32.h" // Base class: NetProtocol32Cmd32
#include "SingletonT.h"
#include "SimpleHandlerFactory.h"
#include "TimerHandler.h"

class ChatClientHandler : public ProtolTcp, public NetProtocol32Cmd32
{
public:
    ChatClientHandler();
    ~ChatClientHandler();

    void SendChat( const std::string& chat );
public:
    
    int OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_) override;
    bool OnRecieve(NormalBuff& buff) override;
    int OnDisconnect(const char* pszIP_, LsUInt16 port_,Disconnet_Reason reason_) override;
};

class ChatRobot: public ZbyClientRobot<ChatClientHandler>, public SingletonT<ChatRobot>,public TimerHandler
{
public:    
    void SendAllChat( const std::string& chat );
    virtual bool OnTime(uint64_t now);
    
};

#endif // CHATCLIENTHANDLER_HPP
