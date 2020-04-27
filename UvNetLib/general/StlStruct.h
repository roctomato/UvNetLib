#ifndef __STL_STRUCT_H__
#define __STL_STRUCT_H__

#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>

#include "z_typedef.h"
#include "Archive.h"
//#include "loop_buf.h"
  
typedef std::map<int,int> IntMap;
typedef std::map<int,long long> Int64Map;
typedef std::list<int>	  IntList;
typedef std::vector<int>  IntVec;
typedef std::set<int>  IntSet;
typedef std::set<unsigned int>  UIntSet;

typedef std::set<LsUInt32>     SetUInt32;
typedef std::set<std::string>  SetString;
typedef std::map<std::string,std::string>  MapString;

class WrapMapString
{
public:
	WrapMapString(MapString& mapStr): _rMapStr(mapStr){}
	
	LsUInt32 SerializeSize();
	bool Read( LsUInt8* pBuf, int len );
	CInArchive& Read(CInArchive& in);
	COutBuff& 	Write(COutBuff& sndBuf );	
	
	MapString&	_rMapStr;
};

class WrapSetString
{
public:
	WrapSetString(SetString& setStr): _rSetStr(setStr){}
	
	LsUInt32 SerializeSize();
	bool Read( LsUInt8* pBuf, int len );
	CInArchive& Read(CInArchive& in);
	COutBuff& 	Write(COutBuff& sndBuf );	
	
	SetString&	_rSetStr;
};

class WrapSetID
{
public:
	WrapSetID(SetUInt32& setStr): _rSetID(setStr){}
	
	LsUInt32 SerializeSize();
	bool Read( LsUInt8* pBuf, int len );
	CInArchive& Read(CInArchive& in);
	COutBuff& 	Write(COutBuff& sndBuf );	
	
	SetUInt32&	_rSetID;
};
#endif
