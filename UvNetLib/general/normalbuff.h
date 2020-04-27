#ifndef NORMALBUFF_H
#define NORMALBUFF_H

#include <memory>
#include <deque>
#include <string>

#include "z_typedef.h"
#include "Archive.h"


class NormalBuff
{
public:
	NormalBuff();
	NormalBuff( int size );
	NormalBuff(const NormalBuff& ins );
	NormalBuff( NormalBuff& ins );
	NormalBuff( NormalBuff&& ins );
	~NormalBuff();

	void MoveFrom(NormalBuff& ins);
	
	void ResetSize( int size );
	void Reset();
	int  GetBuffSize() { return this->_bufSize;}
	bool IsWriteFull();
	LsUInt8* GetWriteBufSize( int& len );
	bool   MoveWriteOffset( int len );
	int  AppendBuffer( const LsUInt8* pBuf, int len);
	
	LsUInt8* GetRawBuf( int& len );
	LsUInt8* GetReadBuf( int& len );
	bool   MoveReadOffset( int len );
	void   InitOutAr( COutArchiveEx& out );
protected:
	LsUInt8* _pBuf;
	int      _bufSize;
	int      _len;
	
	int      _readOffset;
	int      _writeOffset;
};

class RecvBuffEx
{
public:
	void ResetHeaderSize( int sz );	
	NormalBuff&  SetBodySize( int sz );
	
	NormalBuff  _header;
	NormalBuff  _recvBuf;
};


class ISendBuffEx
{
public:
	virtual LsInt8* GetRawBuf( int* len ) = 0;
	virtual int     GetTotalSize() = 0;
	virtual ~ISendBuffEx() {};
};

typedef std::shared_ptr<ISendBuffEx> SendBuffSptr;
typedef std::deque<SendBuffSptr> SendDequeEx;

class SimpleSendBuff: public ISendBuffEx
{
private:
	SimpleSendBuff( int len );
public:
	static SendBuffSptr Create( int len );
	static SendBuffSptr CreateEx( const char*pBuf, int len );
	virtual ~SimpleSendBuff();
	virtual  LsInt8* GetRawBuf( int* len ) ;
	virtual int     GetTotalSize();
	
private:
	LsInt8* _pBuf;
	int    _len;
};

class StringSendBuff: public ISendBuffEx
{
public:	
	StringSendBuff(StringSendBuff&& ins);
	StringSendBuff( int len =0);
	
	void Append( const char* pData, int len );
	
	virtual ~StringSendBuff();
	virtual  LsInt8* GetRawBuf( int* len ) ;
	virtual int     GetTotalSize();
	
private:
	std::string _buff;
};

class NormalISendBuffEx: public ISendBuffEx
{
public:
	static SendBuffSptr Create(); 
	static SendBuffSptr Create(NormalBuff& buff); 
	static SendBuffSptr Create(const LsUInt8* pData, int len); 
	NormalBuff& GetBuff(){ return _sendBuf; }
	
    NormalISendBuffEx();
	NormalISendBuffEx( NormalBuff& buff);
	NormalISendBuffEx( const LsUInt8* pData, int len);
	virtual ~NormalISendBuffEx();

	//////implement ISendBuff ///////////
	virtual LsInt8* GetRawBuf( int* len ) ;
	virtual int     GetTotalSize() ;
	////////////////////////////////////////////////
	
	static int   s_create;
	static int   s_destory;
private:	
	NormalBuff  _sendBuf;
};

class ArchiveISendBuffEx: public ISendBuffEx
{
public:
	static SendBuffSptr Create(); 
	
    ArchiveISendBuffEx();
	virtual ~ArchiveISendBuffEx();
	
	COutArchive& GetArchOur();
	
	//////implement ISendBuff ///////////
	virtual LsInt8* GetRawBuf( int* len ) ;
	virtual int     GetTotalSize() ;
	////////////////////////////////////////////////
	
	static int   s_create;
	static int   s_destory;
private:	
	COutArchive  _archOut;
};

class GenSendQueue
{
public:
	void Reset();
	StringSendBuff* AddStringBuf(bool addTail = true );
	COutArchive*    AddArchiveBuff(bool addTail = true );

	int  AddSendBuff(SendBuffSptr& ps, bool addTail = true );
	bool AddNormalBuff(NormalBuff& buff, bool addTail  );
    bool AddBuff(const  LsUInt8* pData, int len, bool addTail); 
    
	int GetTotalSize();
	SendBuffSptr Combine();
private:
	SendDequeEx _sendBuff;
};


#endif // NORMALBUFF_H
