#ifndef CNGATEMSG_H
#define CNGATEMSG_H
#include <set>
#include <map>
#include "Archive.h"
#include "zserverhandler.h"

#define SERVER_BUFF_LENGTH (5*1024*1024)
//服务器通信模块
enum Gate_Svr_Msg_Module
{
	 SVR_MSG_PROXY_MODULE = 1, //转发消息模块  
	 SVR_MSG_LOGIC_MODULE = 2, //服务器间逻辑模块
};

//转发消息
enum Gate_Svr_Proxy_Msg
{
	 Svr_Proxy_Client_Logic       = 1, //gate转发客户端消息到logic   header.param1 = clientid  +  + param + msg
	 Svr_Proxy_Logic_Client_By_ID = 2, //logic 通过gate发消息到客户端  header.param1 = clientid  +  msg
	 Svr_Proxy_Logic_Client_By_Name = 3, //logic 通过gate发消息到客户端 header + name + msg
	 Svr_Proxy_Group_Msg_By_ID = 4, //群发消息 header + idset + msg
	 Svr_Proxy_Group_Msg_By_Name = 5, //群发消息 header + nameset + msg
	 Svr_Proxy_Group_Msg_By_Tag = 6, //群发消息 header + tagset + msg
	 Svr_Proxy_Send_All_Msg = 7, //群发消息    header + msg
};

//服务器间逻辑消息
enum Gate_Svr_Logic_Msg
{
	 Svr_Logic_Set_Name  = 1, //  header.param1 = clientid + name
	 Svr_Logic_Set_Param = 2, //  header.param1 = clientid + kev_value_list
	 Svr_Logic_Del_Param = 3, //  header.param1 = clientid + keylist
	 Svr_Logic_Set_Tag   = 4, //  header.param1 = clientid + op + taglist
	 Svr_Logic_Kick      = 5, //  header.param1 = clientid + reason
	 Svr_Logic_Client_Logout  = 6, //  header.param1 = clientid +  header.param2 =(0 - logout 1 -login ) +kev_value_list 
};

enum Gate_Client_OP
{
	 Gate_Client_OP_Add = 1, //
	 Gate_Client_OP_DEl = 0, //
};

enum Gate_Client_LOGIN_OP
{
	 Gate_Client_LOGIN  = 1, //
	 Gate_Client_LOGOUT = 0, //
};
typedef std::set<LsUInt32> SetClientID; //cmment
typedef std::set<std::string> SetString; //cmment
typedef std::map<std::string,std::string> MapString; //cmment



class CnGateMsgEx
{
public:
	CnGateMsgEx(GenSendQueue& sndBuf);
	
	//proxy msg
	bool GenClient2LogicMsg(  LsUInt32 clientID, MapString& param);//please add send buff first
	bool GenLogic2ClientMsg(  LsUInt32 clientID );
	bool GenLogic2ClientByName(  const char* name );
	bool GenGroupByTag(  SetString& tag );
	bool GenGroupByID(  SetClientID& idSet);
	bool GenGroupByName(  SetString& name );
	bool GenSendAllMsg();
	
	
	//logic msg
	bool GenSetName ( LsUInt32 clientID, const char* name );
	bool GenSetParam( LsUInt32 clientID, MapString& param );
	bool GenDelParam( LsUInt32 clientID, SetString& keys );
	bool GenAddTag  ( LsUInt32 clientID, LsUInt8 op, SetString& tags );
	bool GenKick    ( LsUInt32 clientID, LsUInt8 reason );
	bool GenLogoutIn( LsUInt32 clientID, MapString& param, Gate_Client_LOGIN_OP op);
	
protected:
	SvrMsgHeader	_header;	
	GenSendQueue&   _sendQueue;
};
#endif // CNGATEMSG_H
