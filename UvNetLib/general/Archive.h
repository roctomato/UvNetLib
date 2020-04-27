
#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include "i_archive.h"

class CInArchive
{
public:
    CInArchive(const char* pBuf, LsUInt32 dwLen) : _pBuf(pBuf), _pPos((char*)pBuf), _dwLen(dwLen) ,_leftSize(dwLen) { }

    template<typename T>
    CInArchive& operator>>(T& val) 
    {
        size_t sz = sizeof(T);
        if ( _leftSize < (LsInt32)sz )
            throw  ArInExc( typeid(T).name(), (int)sz,  (int)_leftSize );
        memcpy(&val,  _pPos, sz);
        _pPos += sz;
        _leftSize -= sz;
        return *this;
    }

    
    template<typename T>
    CInArchive& operator>>(vector<T>& vec)
    {
    	LsUInt16 byCnt;
		*this >>byCnt;
    	vec.resize(byCnt);
    	for(LsUInt16 i = 0; i < byCnt; ++i)
    		*this >> vec[i];
    	return *this;
    }
    
    CInArchive& operator>>(string& str)
    {
        LsUInt16 wLen = 0;
        *this >> wLen;
        if ( _leftSize < wLen )
            throw  ArInExc("string", (int)wLen, (int)_leftSize);
        str.assign(_pPos, wLen);
        _pPos += wLen;
        _leftSize -= wLen;
        return *this;
    }

   CInArchive& operator>>(BigString& str)
    {
        LsInt32 wLen = 0;
        *this >> wLen;
        if ( _leftSize < wLen )
            throw  ArInExc("string", (int)wLen, (int)_leftSize);
        str.assign(_pPos, wLen);
        _pPos += wLen;
        _leftSize -= wLen;
        return *this;
    }

	char* GetLeftBuf(LsUInt32& dwLen)
    {
        dwLen =  _leftSize ;
        return _pPos;
    }
	
	CInArchive& ReadBigString( string& str )
    {
        LsInt32 wLen = 0;
        *this >> wLen;
        if ( _leftSize < wLen )
            throw  ArInExc("string", (int)wLen, (int)_leftSize);
        str.assign(_pPos, wLen);
        _pPos += wLen;
        _leftSize -= wLen;
        return *this;
    }
	
protected:
    const char* _pBuf;
    char* _pPos;
    LsUInt32 _dwLen;
    LsInt32 _leftSize;
};

class COutArchive: public COutBuff
{
public:
    COutArchive():_strBuf( _selfStr )
    {
        _strBuf.reserve(20);
    }
    COutArchive( string& other):_strBuf( other )
    {
        //_strBuf.reserve(20);
    }

	char* GetBuf(LsUInt32& dwLen)
	{
		dwLen = this->GetCurBufLen();
		return this->GetCurBuf();
	}

	char* GetCurBuf()
	{
		return const_cast<char*>(_strBuf.c_str());
	}
	
	LsUInt32 GetCurBufLen()  {
		return _strBuf.size();
	}
	
	void Reset()
    {
        _strBuf.clear();
    }

	// implement COutBuff
	virtual void Append( const char* pData, int len )
	{
		_strBuf.append( pData, len );
	}
	virtual int  StartWrite( LsUInt8 sz = 0 ) { return 0; }
	virtual	bool EndWrite(  int payload = 0)  { return true; }
	//////////////////////////////////////////////////////
   
	string& GetString()
	{
		return _strBuf;
	}
protected:
    string& _strBuf;
    string   _selfStr;
};

class COutArchiveEx: public COutBuff
{
public:
    COutArchiveEx( char* pBuf=NULL, LsUInt32 dwLen=0) : _pBuf(pBuf), _pPos((char*)pBuf), _dwLen(dwLen) ,_leftSize(dwLen) { }

	// implement COutBuff
	virtual void Append( const char* pData, int sz)
	{
		if ( sz > _leftSize ){
			throw "overflow";
		}
		memcpy(  _pPos, pData, sz);
        _pPos += sz;
        _leftSize -= sz;
		//_strBuf.append( pData, len );
	}
	virtual int  StartWrite( LsUInt8 sz = 0 ) { return 0; }
	virtual	bool EndWrite(  int payload = 0)  { return true; }
	//////////////////////////////////////////////////////
#ifndef __WIN32__
    COutArchiveEx& Printf( const char *fmt, ...)
    {
        int res = -1;
        va_list ap;

        va_start(ap, fmt);
        res = vsnprintf(_pPos,  _leftSize, fmt, ap);
        va_end(ap);
        if ( res <= 0 )
            throw "overflow";
        _pPos += res;
        _leftSize -= res;
        return  *this;
    }
#endif

    char* GetBuf(LsUInt32& dwLen)
    {
        dwLen = _dwLen - _leftSize ;
        return _pBuf;
    }
    void Reset(  char* pBuf, LsUInt32 dwLen )
    {
        _pBuf  = pBuf;
        _pPos = pBuf;
        _dwLen  = dwLen;
        _leftSize = dwLen;
    }

    void Reset(  )
    {
        _pPos     = _pBuf;
        _leftSize = _dwLen;
    }

protected:
    char* _pBuf;
    char* _pPos;
    LsUInt32 _dwLen;
    LsInt32 _leftSize;
};

#endif
