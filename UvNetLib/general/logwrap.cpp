#include "logwrap.h"
#include "loggerinterfaceex.h"

LogWrap& LogWrap::Reset()
{
	this->_logStream.clear();
	this->_logStream.str("");
	return *this;
}

LogWrap& LogWrap::Reset(const char* cate, int priority)
{
	this->Reset();
	this->_cateLog = cate;
	this->_priority = priority;
	return *this;
}

LogWrap& LogWrap::Reset(const char* cate, int priority, const char* func, const char* file, int line)
{
	Reset(cate, priority);
	return this->AddFunc( func, file, line);
}

LogWrap& LogWrap::Flush()
{
	LogPrintPrint( this->_cateLog, this->_priority, this->_logStream.str());
	return *this;
}

LogWrap& LogWrap::Flush(const char* cate, int priority)
{
	LogPrintPrint( cate, priority, this->_logStream.str());
	return *this;
}
LogWrap& LogWrap::AddFunc(const char* func, const char* file, int line)
{
	this->_logStream << func << " ("<<file<<':'<<line<<") ";
	return *this;

}
