#include <stdio.h>
#include <string.h>

#include "normalbuff.h"
#include "zby_debug.h"


SendBuffSptr SimpleSendBuff::Create(int len)
{
	return SendBuffSptr( new SimpleSendBuff(len));
}
SendBuffSptr SimpleSendBuff::CreateEx(const char* pBuf, int len)
{
    SendBuffSptr ret = Create(len);
    LsInt8* pDes = ret->GetRawBuf(NULL);
    memcpy(pDes, pBuf, len);
    return ret;
}

LsInt8* SimpleSendBuff::GetRawBuf(int* len)
{
    if (len){
        *len = this->_len;
    }
	return this->_pBuf;
}

int SimpleSendBuff::GetTotalSize()
{
	return this->_len;
}

SimpleSendBuff::SimpleSendBuff(int len)
{
	this->_pBuf = new LsInt8[len];
	this->_len = len;
}

SimpleSendBuff::~SimpleSendBuff()
{
	delete [] this->_pBuf;
}

////////////////////////////////////////
NormalBuff::NormalBuff()
{
	_pBuf = NULL;
	_len = 0;
	_bufSize = 0;
	_readOffset  = 0;
	_writeOffset = 0;
}

NormalBuff::NormalBuff(NormalBuff& ins):NormalBuff(ins._bufSize)
{
	memcpy( this->_pBuf, ins._pBuf, ins._bufSize );
	this->_len = ins._len;
	this->_readOffset = ins._readOffset;
	this->_writeOffset = ins._writeOffset;
}

NormalBuff::NormalBuff(const NormalBuff& ins):NormalBuff(ins._bufSize)
{
	memcpy( this->_pBuf, ins._pBuf, ins._bufSize );
	this->_len = ins._len;
	this->_readOffset = ins._readOffset;
	this->_writeOffset = ins._writeOffset;
}
NormalBuff::NormalBuff( NormalBuff&& ins ):
	_pBuf(ins._pBuf)
	,_bufSize(ins._bufSize )
	,_len (ins._len)
	,_readOffset ( ins._readOffset)
	,_writeOffset (ins._writeOffset)
{
	ins._pBuf = NULL;
	ins._len = 0;
	ins._bufSize = 0;
	ins._readOffset  = 0;
	ins._writeOffset = 0;
}
NormalBuff::~NormalBuff()
{
	if ( _pBuf )
		delete [] _pBuf;
}

NormalBuff::NormalBuff(int size)
{
	_pBuf = NULL;
	_len = 0;
	_bufSize = 0;
	_readOffset  = 0;
	_writeOffset = 0;
	this->ResetSize( size );
}



void NormalBuff::ResetSize(int len)
{
	do {
		if ( len <= this->_bufSize ) {
			break;
		}

		if ( _pBuf ) {
			delete [] _pBuf;
		}
		_pBuf = new LsUInt8[len];
		this->_bufSize = len;
	} while(false);

	_len = len;
	_readOffset  = 0;
	_writeOffset = 0;
}
void NormalBuff::Reset()
{
	_readOffset  = 0;
	_writeOffset = 0;
}

LsUInt8* NormalBuff::GetRawBuf(int& len)
{
	len = this->_len;
	return this->_pBuf;
}

LsUInt8* NormalBuff::GetReadBuf(int& len)
{
	len = this->_writeOffset - this->_readOffset;
	return this->_pBuf + this->_readOffset;
}

bool NormalBuff::MoveReadOffset(int len)
{
	if ( this->_readOffset  + len > this->_len) {
		return false;
	}
	this->_readOffset += len;
	return true;
}

int NormalBuff::AppendBuffer(const LsUInt8* pBuf, int len)
{
	int ret = -1;
	do {
		int left = this->_len - this->_writeOffset;
		if ( left < len ) {
			SYS_ERR( "out buffer left %d write %d", left, len );
			break;
		}
		memcpy( this->_pBuf + this->_writeOffset, pBuf, len );
		this->_writeOffset += len;
		ret = this->_len - this->_writeOffset;
	} while(false);
	return ret;
}

bool NormalBuff::IsWriteFull()
{
	return this->_writeOffset == this->_len;
}


LsUInt8* NormalBuff::GetWriteBufSize(int& len)
{
	len = this->_len - this->_writeOffset;
	return this->_pBuf + this->_writeOffset;
}

bool NormalBuff::MoveWriteOffset(int len)
{
	if ( this->_writeOffset  + len > this->_len) {
		return false;
	}
	this->_writeOffset += len;
	return true;
}
void NormalBuff::InitOutAr(COutArchiveEx& out)
{
	out.Reset( (char*)this->_pBuf, this->_len);
}
void NormalBuff::MoveFrom(NormalBuff& ins)
{
	this->_pBuf = ins._pBuf;
	this->_bufSize = ins._bufSize ;
	this->_len = ins._len;
	this->_readOffset = ins._readOffset;
	this->_writeOffset = ins._writeOffset;

	ins._pBuf = NULL;
	ins._len = 0;
	ins._bufSize = 0;
	ins._readOffset  = 0;
	ins._writeOffset = 0;
}

//////////////////////////////////////////////////////////////
LsInt8* NormalISendBuffEx::GetRawBuf(int* len)
{
	LsInt8*  ret = NULL;
    int readLen =0;
	ret = (LsInt8*)this->_sendBuf.GetReadBuf( readLen );
    if (len)
        *len = readLen;
	return ret;
}

int NormalISendBuffEx::GetTotalSize()
{
	LsInt8*  ret = NULL;
	int len = 0;
	ret = (LsInt8*)this->_sendBuf.GetReadBuf( len );
	return len;
}


int NormalISendBuffEx::s_create  = 0;
int NormalISendBuffEx::s_destory = 0;

NormalISendBuffEx::NormalISendBuffEx( NormalBuff& buff):
_sendBuf(std::move(buff))
{

	s_create++;
}

NormalISendBuffEx::NormalISendBuffEx(const LsUInt8* pData, int len)
{
	this->_sendBuf.ResetSize( len );
	this->_sendBuf.AppendBuffer(pData, len );
	s_create++;
}
NormalISendBuffEx::NormalISendBuffEx(){
	s_create++;
}

NormalISendBuffEx::~NormalISendBuffEx()
{
	s_destory ++;
}
SendBuffSptr NormalISendBuffEx::Create(const LsUInt8* pData, int len)
{
	return SendBuffSptr( new NormalISendBuffEx(pData, len) );
}

SendBuffSptr NormalISendBuffEx::Create(NormalBuff& buff)
{
	return SendBuffSptr( new NormalISendBuffEx(buff) );
}
SendBuffSptr NormalISendBuffEx::Create()
{
	return SendBuffSptr( new NormalISendBuffEx() );
}

////////////////////////////////////////////////////////

COutArchive& ArchiveISendBuffEx::GetArchOur()
{
	return this->_archOut;
}

LsInt8* ArchiveISendBuffEx::GetRawBuf(int* len)
{
	LsUInt32 dwLen;
	LsInt8*  pBuf = this->_archOut.GetBuf( dwLen );
	if (len)
        *len = dwLen;
	return pBuf;
}


int ArchiveISendBuffEx::GetTotalSize()
{
	return this->_archOut.GetCurBufLen();
}

int ArchiveISendBuffEx::s_create  = 0;
int ArchiveISendBuffEx::s_destory = 0;
ArchiveISendBuffEx::ArchiveISendBuffEx()
{
	s_create++;
}
ArchiveISendBuffEx::~ArchiveISendBuffEx()
{
	s_destory++;
}
SendBuffSptr ArchiveISendBuffEx::Create()
{
	return SendBuffSptr( new ArchiveISendBuffEx() );
}

//////////////////////////////////////////////////////////////



LsInt8* StringSendBuff::GetRawBuf(int* len)
{
	LsInt8* ret = const_cast<char*>(_buff.c_str());
	if ( len ){
		*len = _buff.size();
	}
	return ret;
}

int StringSendBuff::GetTotalSize()
{
	return _buff.size();
}

StringSendBuff::StringSendBuff(int len)
{
	if (len>0 ){
		_buff.reserve(len);
	}
	
}

StringSendBuff::~StringSendBuff()
{
}
void StringSendBuff::Append(const char* pData, int len)
{
	_buff.append( pData, len );
}
StringSendBuff::StringSendBuff(StringSendBuff&& ins)
:_buff(std::move(ins._buff))
{
}
////////////////////////////////////////////////////////////
void RecvBuffEx::ResetHeaderSize(int sz)
{
	_header.ResetSize( sz );
}

NormalBuff& RecvBuffEx::SetBodySize(int sz)
{
	int hz ;
	LsUInt8* pBuf = this->_header.GetRawBuf( hz );
	int len = hz;
	len += sz;

	this->_recvBuf.ResetSize(len);
	this->_recvBuf.AppendBuffer( pBuf,  hz);
	return this->_recvBuf ;
}
////////////////////////////////////////////////
void GenSendQueue::Reset()
{
    this->_sendBuff.clear();
}

StringSendBuff* GenSendQueue::AddStringBuf(bool addTail)
{
    StringSendBuff*  buff = new StringSendBuff();
    if ( buff ){
        SendBuffSptr ps (buff);
        this->AddSendBuff(ps,addTail);
    }
    return buff;
}

COutArchive* GenSendQueue::AddArchiveBuff(bool addTail)
{
    COutArchive* ret = NULL;
    ArchiveISendBuffEx* pA = new ArchiveISendBuffEx();
    if (pA){
        SendBuffSptr ps (pA);
        this->AddSendBuff(ps,addTail);
        ret = &(pA->GetArchOur());
    }
    return ret;
}

int GenSendQueue::AddSendBuff(SendBuffSptr& ps, bool addTail)
{
    if ( addTail) {
		this->_sendBuff.push_back( ps );
	} else {
		this->_sendBuff.push_front( ps );
	}
	return this->_sendBuff.size();
}

bool GenSendQueue::AddNormalBuff(NormalBuff& buff, bool addTail)
{
    SendBuffSptr p = NormalISendBuffEx::Create( buff);
	this->AddSendBuff( p, addTail);
	return true;
}

bool GenSendQueue::AddBuff(const LsUInt8* pData, int len, bool addTail)
{
    SendBuffSptr p =SimpleSendBuff::CreateEx((const char*)pData, len);
    this->AddSendBuff( p, addTail);
	return true;
}

int GenSendQueue::GetTotalSize()
{
    int ret = 0;
	auto it = _sendBuff.begin();
	for(; it != _sendBuff.end(); it ++ ) {
		SendBuffSptr& pCur = *it;
		ISendBuffEx* p = pCur.get();
		if ( p ) {
			ret += p->GetTotalSize();
		}
	}
	return ret;
}

SendBuffSptr GenSendQueue::Combine()
{
    StringSendBuff*  buff = new StringSendBuff();
    if ( buff ){
        auto it = _sendBuff.begin();
		for(; it != _sendBuff.end(); it ++ ) {
			SendBuffSptr& pCur = *it;
			int   len ;
			char* pBuf = pCur->GetRawBuf( &len );
			if ( pBuf && len > 0 ){
				buff->Append( pBuf, len );
			}
		}
    }
    return SendBuffSptr(buff);
}
