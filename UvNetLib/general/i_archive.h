#ifndef IARCHIVE_H
#define IARCHIVE_H

#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
 #include <typeinfo>
 
#include "z_typedef.h"
#include <exception>

using namespace std;

class ArInExc: public  exception
{
public:
	ArInExc(  const char* name, int wlen, int len  )
	{
		sprintf( _info,"%s %d %d", name, wlen, len );
	}
	virtual const char* what() const throw()
	{
		return _info;
	}
protected:
	char _info[128];
};

class COutBuff
{
public:	
	
	virtual void Append( const char* pBuf, int len ) = 0;
	virtual int  StartWrite( LsUInt8 sz = 0 ) = 0;
	virtual	bool EndWrite(  int payload = 0) = 0;
	
	template<typename T>
    COutBuff& operator<<(const T& val)
    {
        size_t sz = sizeof(T);
        this->Append((char*)&val, sz );
        return *this;
    }


    template<typename T>
    COutBuff& operator<<(const vector<T>& vec)
    {
		int len = vec.size();
		if ( len > 0xffff){
			throw ArInExc("long string",len,0 );
		}
        LsUInt16 byCnt = (LsUInt16)vec.size();
        *this << byCnt;
        for(LsUInt16 i = 0; i < byCnt; ++i)
            *this << vec[i];
        return *this;
    }

    COutBuff& operator<<(const string& str)
    {
		int len = str.size();
		if ( len > 0xffff){
			throw ArInExc("long string",len,0 );
		}
        LsUInt16 sz = (LsUInt16)len;
        *this << sz;
        this->Append( str.c_str(), str.size());
        return *this;
    }
	
    COutBuff& operator<<(const BigString& str)
    {
		LsInt32 sz = str.size();
        *this << sz;
        this->Append( str.c_str(), str.size());
        return *this;
    }
	
	void AppendStringBuf( char* pData, int len )
	{
		if ( len > 0xffff){
			throw ArInExc("long string",len,0 );
		}
		LsUInt16 sz = (LsUInt16)len;
        *this << sz;
		this->Append( pData, len );
	}
	void AppendBigStringBuf( char* pData, int len )
	{
		LsUInt32 sz = (LsUInt32)len;
        *this << sz;
		this->Append( pData, len );
	}
	
};

#endif // IARCHIVE_H
