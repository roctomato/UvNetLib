#ifndef SYS_TOOLS_H
#define SYS_TOOLS_H

#include "z_typedef.h"
#include <time.h>
#include <map>
#include <string>

int daemonize( const char* path_name=0);
unsigned  int GenMark( unsigned char* data, int len);

class CheckValid
{
public:
	
	CheckValid();
	~CheckValid();
	bool IsValid();
	void Dump();
private:
	static   LsUInt16 s_nextFlag;
	LsUInt16 _initMark;
	LsUInt16 _lastMark; 
};

#endif // SYS_TOOLS_H
