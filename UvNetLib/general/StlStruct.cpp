#include "StlStruct.h"
#include "zby_debug.h"

CInArchive& WrapMapString::Read(CInArchive& in)
{
	LsUInt16 sz;
	std::string key,value;
	in >> sz;
	for( int i = 0; i < sz; i ++ ){
		in>>key>>value;
		_rMapStr.insert( MapString::value_type(key,value));
	}
	return in;
}

LsUInt32 WrapMapString::SerializeSize()
{
	LsUInt32 ret = sizeof(LsUInt16);
	MapString::iterator it;
	for( it = _rMapStr.begin(); it != _rMapStr.end(); it ++ ) {
		ret += ( sizeof(LsUInt16) + (it->first).size() + sizeof(LsUInt16) +  (it->second).size() );
	}
	return ret;
}

COutBuff& WrapMapString::Write(COutBuff& sndBuf)
{
	LsUInt16 sz = _rMapStr.size(); 
	sndBuf << sz;
	MapString::iterator it;
	for( it = _rMapStr.begin(); it != _rMapStr.end(); it ++ ) {
		sndBuf << it->first << it->second;
	}
	return sndBuf;
}
bool WrapMapString::Read(LsUInt8* pBuf, int len)
{
	CInArchive ar( (char*)pBuf, len );
	bool ret = false;
	try{
		this->Read( ar );
		ret = true;
	}catch(ArInExc& e){
		SYS_ERR( "%s",e.what() );
	}
	return ret;
}
////////////////////////////////////////////////////////////
CInArchive& WrapSetString::Read(CInArchive& in)
{
	LsUInt16 sz;
	std::string value;
	in >> sz;
	for( int i = 0; i < sz; i ++ ){
		in>>value;
		_rSetStr.insert(value);
	}
	return in;
}

LsUInt32 WrapSetString::SerializeSize()
{
	LsUInt32 ret = sizeof(LsUInt16);
	SetString::iterator it;
	for( it = _rSetStr.begin(); it != _rSetStr.end(); it ++ ) {
		ret += ( sizeof(LsUInt16) + (*it).size() );
	}
	return ret;
}

COutBuff& WrapSetString::Write(COutBuff& sndBuf)
{
	LsUInt16 sz = _rSetStr.size(); 
	sndBuf << sz;
	SetString::iterator it;
	for( it = _rSetStr.begin(); it != _rSetStr.end(); it ++ ) {
		sndBuf<<*it;
	}
	return sndBuf;
}

bool WrapSetString::Read(LsUInt8* pBuf, int len)
{
	CInArchive ar( (char*)pBuf, len );
	bool ret = false;
	try{
		this->Read( ar );
		ret = true;
	}catch(ArInExc& e){
		SYS_ERR( "%s",e.what() );
	}
	return ret;
}

/////////////////////////////////////////////////////////
CInArchive& WrapSetID::Read(CInArchive& in)
{
	LsUInt16 sz;
	in >> sz;
	for( int i = 0; i < sz; i ++ ){
		LsUInt32 id;
		in>>id;
		this->_rSetID.insert(id );
	}
	return in;
}

bool WrapSetID::Read(LsUInt8* pBuf, int len)
{
	CInArchive ar( (char*)pBuf, len );
	bool ret = false;
	try{
		this->Read( ar );
		ret = true;
	}catch(ArInExc& e){
		SYS_ERR( "%s",e.what() );
	}
	return ret;
}

LsUInt32 WrapSetID::SerializeSize()
{
	LsUInt16 sz = _rSetID.size();
	return  sizeof(LsUInt16) + sizeof(LsUInt32)*sz ;
}

COutBuff& WrapSetID::Write(COutBuff& sndBuf)
{
	LsUInt16 sz = _rSetID.size();
	sndBuf <<sz;
	for( SetUInt32::iterator it = _rSetID.begin(); it != _rSetID.end(); it ++)
		sndBuf<<(*it);
	return sndBuf;
}
