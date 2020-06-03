#include "cngatemsg.h"
#include "zby_debug.h"
#include "StlStruct.h"


///////////////////////////////////////////////////////////////
CnGateMsgEx::CnGateMsgEx(GenSendQueue& sndBuf):_sendQueue(sndBuf)
{
}

bool CnGateMsgEx::GenClient2LogicMsg(LsUInt32 clientID, MapString& param)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}

		WrapMapString wms(param);
		COutArchive&  out = *pSIs;
		wms.Write( out );

		this->_header.module = SVR_MSG_PROXY_MODULE;
		this->_header.cmd    = Svr_Proxy_Client_Logic;
		this->_header.param1 = clientID;
		this->_header.AddToSend(this->_sendQueue);
		ret = true;
	} while(false);

	return ret;
}

bool CnGateMsgEx::GenLogic2ClientByName(const char* name)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}
		std::string strName(name);
		COutArchive&  out = *pSIs;
		out<<name;
		
		this->_header.module = SVR_MSG_PROXY_MODULE;
		this->_header.cmd    = Svr_Proxy_Logic_Client_By_Name;
		this->_header.AddToSend(this->_sendQueue);
		ret =true;
	} while(false);
	
	return ret;
}

bool CnGateMsgEx::GenLogic2ClientMsg(LsUInt32 clientID)
{
	this->_header.module = SVR_MSG_PROXY_MODULE;
	this->_header.cmd    = Svr_Proxy_Logic_Client_By_ID;
	this->_header.param1 = clientID;
	this->_header.AddToSend(this->_sendQueue);
	return true;
}

bool CnGateMsgEx::GenGroupByTag(SetString& tag)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}

		WrapSetString wss(tag);
		COutArchive&  out = *pSIs;
		wss.Write( out );

		this->_header.module = SVR_MSG_PROXY_MODULE;
		this->_header.cmd    = Svr_Proxy_Group_Msg_By_Tag;
		this->_header.AddToSend(this->_sendQueue);
		ret = true;
	} while(false);
	return ret;
}

bool CnGateMsgEx::GenGroupByID(SetClientID& idSet)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}

		WrapSetID wss(idSet);
		COutArchive&  out = *pSIs;
		wss.Write( out );

		this->_header.module = SVR_MSG_PROXY_MODULE;
		this->_header.cmd    = Svr_Proxy_Group_Msg_By_ID;
		this->_header.AddToSend(this->_sendQueue);
		ret = true;
	} while(false);
	return ret;
}
bool CnGateMsgEx::GenSendAllMsg()
{
	this->_header.module = SVR_MSG_PROXY_MODULE;
	this->_header.cmd    = Svr_Proxy_Send_All_Msg;
	this->_header.AddToSend(this->_sendQueue);
	return true;
}
bool CnGateMsgEx::GenGroupByName(SetString& name)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}

		WrapSetString wss(name);
		COutArchive&  out = *pSIs;
		wss.Write( out );

		this->_header.module = SVR_MSG_PROXY_MODULE;
		this->_header.cmd    = Svr_Proxy_Group_Msg_By_Name;
		this->_header.AddToSend(this->_sendQueue);
		ret = true;
	} while(false);
	return ret;
}


bool CnGateMsgEx::GenAddTag(LsUInt32 clientID, LsUInt8 op, SetString& tags)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}

		WrapSetString wss(tags);
		COutArchive&  out = *pSIs;
		wss.Write( out );

		this->_header.module = SVR_MSG_LOGIC_MODULE;
		this->_header.cmd    = Svr_Logic_Set_Tag;
		this->_header.param1 = clientID;
		this->_header.param2 = op;
		this->_header.AddToSend(this->_sendQueue);
		ret = true;
	} while(false);
	return ret;
}

bool CnGateMsgEx::GenDelParam(LsUInt32 clientID, SetString& keys)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}

		WrapSetString wss(keys);
		COutArchive&  out = *pSIs;
		wss.Write( out );

		this->_header.module = SVR_MSG_LOGIC_MODULE;
		this->_header.cmd    = Svr_Logic_Del_Param;
		this->_header.param1 = clientID;
		this->_header.AddToSend(this->_sendQueue);
		ret = true;
	} while(false);
	return ret;
}

bool CnGateMsgEx::GenKick(LsUInt32 clientID, LsUInt8 reason)
{
	this->_header.module = SVR_MSG_LOGIC_MODULE;
	this->_header.cmd    = Svr_Logic_Kick;
	this->_header.param1 = clientID;
	this->_header.param2 = reason;
	this->_header.AddToSend(this->_sendQueue);
	return true;
}

bool CnGateMsgEx::GenSetName(LsUInt32 clientID, const char* name)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}

		std::string sname(name);
		COutArchive&  out = *pSIs;
		out<<sname;

		this->_header.module = SVR_MSG_LOGIC_MODULE;
		this->_header.cmd    = Svr_Logic_Set_Name;
		this->_header.param1 = clientID;
		this->_header.AddToSend(this->_sendQueue);
		ret = true;
	} while(false);
	return ret;	
}

bool CnGateMsgEx::GenSetParam(LsUInt32 clientID, MapString& param)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}

		WrapMapString wss(param);
		COutArchive&  out = *pSIs;
		wss.Write( out );

		this->_header.module = SVR_MSG_LOGIC_MODULE;
		this->_header.cmd    = Svr_Logic_Set_Param;
		this->_header.param1 = clientID;
		this->_header.AddToSend(this->_sendQueue);
		ret = true;
	} while(false);
	return ret;	
}

bool CnGateMsgEx::GenLogoutIn(LsUInt32 clientID, MapString& param, Gate_Client_LOGIN_OP op)
{
	bool ret = false;
	do {
		COutArchive* pSIs = this->_sendQueue.AddArchiveBuff(false);
		if ( NULL == pSIs ) {
			SYS_ERR("add string buff err");
			break;
		}

		WrapMapString wss(param);
		COutArchive&  out = *pSIs;
		wss.Write( out );

		this->_header.module = SVR_MSG_LOGIC_MODULE;
		this->_header.cmd    = Svr_Logic_Client_Logout;
		this->_header.param1 = clientID;
		this->_header.param2 = (LsUInt32)op;
		this->_header.AddToSend(this->_sendQueue);
		ret = true;
	} while(false);
	return ret;	
}

