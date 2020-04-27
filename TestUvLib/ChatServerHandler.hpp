#ifndef CHATSERVERHANDLER_HPP
#define CHATSERVERHANDLER_HPP

#include "net_protocol32_cmd32.h" // Base class: NetProtocol32Cmd32
#include "ProtolTcp.hpp"
#include "SingletonT.h"
#include "SimpleHandlerFactory.h"

class ChatServerHandler : public NetProtocol32Cmd32, public ProtolTcp
{
public:
    ChatServerHandler();

    ~ChatServerHandler();

    //////////////////////////////implement ZSocket //////////////////////////////////////////////////////
    int OnConnect(const char* pszIP_, LsUInt16 port_, LsUInt32 handleID_) override;
    bool OnRecieve(NormalBuff& buff) override;
    int OnDisconnect(const char* pszIP_, LsUInt16 port_,Disconnet_Reason reason_) override;
    //////////////////////////////////////////////////////////////////////////////////////

    std::string _name;
};

class ChatServer: public ZbyIDTcpServer<ChatServerHandler> , public SingletonT<ChatServer>
{
public:    
    void SendAllMsg(std::string& name, NormalBuff& buff);
};

#endif // CHATSERVERHANDLER_HPP
