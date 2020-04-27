#ifndef LSUTILITY_H_INCLUDED
#define LSUTILITY_H_INCLUDED
#include "z_typedef.h"
#include <time.h>
#include <map>
#include <string>

int  Ceil( float d );

// [min, max]
int  Rand( int min, int max );

bool HasFlag( unsigned int  data, unsigned int flag );

void DumpMem( const unsigned char* pBuf,  int len );




int  VarifyDir( const char* pathname  );






int Replace( char* pBuf, char old, char newChar );


std::string LoadFile(const char* file_name , bool trim);

class RandomSqueue
{
public:
	RandomSqueue( int  totalMember );
	void ResetTotal(int  totalMember);
	int	GetNextMember( ); // base 1
protected:
	int  	_totalMember;
	int  	_curIdx;
	std::map<int, int>  _useMap;
};


class OpCtrlFlag {

public:
	OpCtrlFlag();
	~OpCtrlFlag();  
    void ResetFlag(LsUInt32 flag);
    void ClearAll();
    void SetAll();
    
    void AddFlag(LsUInt32 flag) ;
	void RemoveFlag(LsUInt32 flag);
    
	bool HasFlag(LsUInt32 flag);
    
    LsUInt32 _statusFlag ;

};

class GenUIn32ID{
public:
	GenUIn32ID( LsUInt32 minid=0, LsUInt32 maxid = 0xffffffff);
	
	LsUInt32 GenID();
	LsUInt32 GetCurID();
	void SetStartID( LsUInt32 maxID);
	
	
protected:
	LsUInt32 _curID;
	LsUInt32 _minID;
	LsUInt32 _maxID;
};



#define LS_PRINT( FMT, ... ) printf ( "(%s:%d) " FMT "\n", __FUNCTION__ , __LINE__, ## __VA_ARGS__ )
#endif // LSUTILITY_H_INCLUDED
