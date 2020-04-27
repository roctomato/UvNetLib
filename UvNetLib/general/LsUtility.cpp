#include "LsUtility.h"
#include "zby_debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include  <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>

//#include "md5.h"

int  Ceil( float d )
{
	//'向上取整'
	int t = int( d*10 );
	int r = int( t /10 );
	if ( t % 10 )
		return r +1;
	return r;
}

int  Rand( int min, int max )
{
	if ( min > max ) {
		int temp = max;
		max = min;
		min = temp;
	}
	return min + rand() % (max -min + 1);
}
bool HasFlag(unsigned int data, unsigned int flag)
{
	return ( data&flag);
}

void DumpMem( const unsigned char* pBuf,  int len )
{
	SYS_ERR("dump %08x len %d", pBuf, len );
	char  visable[17]= { 0 };
	char  buf[100]={0};
	
	int fullLoop = len / 16;
	int idx = 0;
	int pos = 0;

	for( int i=0; i < fullLoop; i ++ ) {
		printf( "%04x ", idx);
		pos = sprintf( buf , "%04x ", idx );
		for( int j =0; j<16; j ++ ) {
			int d = pBuf[idx++];
			printf( "%02x ", d);
			pos += sprintf( buf + pos, "%02x ", d );
			if (  isprint(d) ) {
				visable[j]=d;
			} else {
				visable[j]='.';
			}
		}
		SYS_ERR( "%s%s",buf, visable );
		printf( "%s\n", visable );
	}


	int lastLoop = len % 16;
	if (  lastLoop ) {
		pos = sprintf( buf , "%04x ", idx );
		for( int j =0; j<16; j ++ ) {
			if ( j < lastLoop ) {
				int d = pBuf[idx++];
				printf( "%02x ", d);
				pos += sprintf( buf + pos, "%02x ", d );
				if (  isprint(d) ) {
					visable[j]=d;
				} else {
					visable[j]='.';
				}
			} else {
				printf( "    ");
				visable[j]=0;
			}
		}
		SYS_ERR( "%s%s",buf, visable );
		printf( "%s\n", visable );
	}
}


int  VarifyDir( const char* pathname )
{
	int ret  = 0;
#ifndef __WIN32__
	DIR* dir = opendir( pathname );
	if ( dir ) {
		ret = 1;
		closedir( dir );
	} else {
		if ( 0 == mkdir( pathname, 0777 ) )
			ret =1;
	}
#endif
	return ret;
}

int Replace(char* pBuf, char old, char newChar)
{
	int total =0;
	int len = strlen( pBuf );
	for( int i =0; i < len; i ++ ) {
		if (   old == pBuf[i] ) {
			pBuf[i]=newChar;
			total ++;
		}
	}
	return total;
}

static std::string _LoadAllContent(const char* file_name)
{
	std::string str;
	do {
		FILE* fp = fopen( file_name, "r");
		if ( NULL == fp ) {
			SYS_ERR("load %s failed", file_name);
			break;
		}
		char temp[100]= {0};
		while( fgets( temp, sizeof(temp), fp) != NULL ) {
			str += temp;
		}
	} while(false);
	return str;	
}
static std::string _LoadContentNoLine(const char* file_name)
{
	std::string str;
	std::ifstream cfgFile ;
	cfgFile.open( file_name);
	if ( cfgFile.is_open())
	{
		std::string temp;
		while (! cfgFile.eof() ) {
			temp.clear();
			cfgFile>> temp;
			str += temp;
		}
	}
	return str;	
}
std::string LoadFile(const char* file_name, bool trim)
{
	return  trim ? _LoadContentNoLine(file_name) : _LoadAllContent( file_name);
}



int RandomSqueue::GetNextMember()
{
	int ret = -1;
	int rand = Rand( _curIdx, _totalMember );
	
	int curStoreVale = _useMap[_curIdx];
	int curRandStore = _useMap[rand];

	if ( curRandStore == 0 )
	{
		ret = rand;
		
	}
	else
	{
		ret = curRandStore;
	}
	
	_useMap[_curIdx] = (  curRandStore == 0 ) ? rand: curRandStore;
	_useMap[rand]         = (  curStoreVale == 0 ) ? _curIdx: curStoreVale;
	
	_curIdx ++;
	if ( _curIdx > _totalMember)
		_curIdx = 1;
	return ret;
}

RandomSqueue::RandomSqueue(int totalMember)
{
	ResetTotal( totalMember );
}

void RandomSqueue::ResetTotal(int totalMember)
{
	_totalMember = totalMember;
	_curIdx = 1;
	_useMap.clear();
}

OpCtrlFlag::OpCtrlFlag()
{
    _statusFlag = 0;
}

OpCtrlFlag::~OpCtrlFlag()
{
}

void OpCtrlFlag::AddFlag(LsUInt32 flag)
{
    _statusFlag |= flag;
}

void OpCtrlFlag::ClearAll()
{
    _statusFlag = 0;
}

bool OpCtrlFlag::HasFlag(LsUInt32 flag)
{
    return ( _statusFlag & flag );
}

void OpCtrlFlag::RemoveFlag(LsUInt32 flag)
{
    _statusFlag &= ( ~flag );
}

void OpCtrlFlag::ResetFlag(LsUInt32 flag)
{
    _statusFlag = flag;
}

void OpCtrlFlag::SetAll()
{
    _statusFlag = -1;
}


LsUInt32 GenUIn32ID::GenID()
{
	LsUInt32 curid = _curID ++;
	if ( _curID >  _maxID ){
		_curID = _minID;
	}
	return  curid;
}

GenUIn32ID::GenUIn32ID(LsUInt32 minid , LsUInt32 maxid ):
_curID (1 )
,_minID(minid)
,_maxID( maxid)
{
	
}

LsUInt32 GenUIn32ID::GetCurID()
{
	return _curID;
}

void GenUIn32ID::SetStartID(LsUInt32 curID)
{
	if ( curID < _curID  ){
		_curID = _minID;
	}else if ( curID > _maxID ){
		_curID = _maxID;
	}else{
		_curID = curID;
	}
}


