#ifndef LOGWRAP_H
#define LOGWRAP_H

#include <string>
#include <sstream>

#define ADD_FUNC( log ) log.AddFunc(__FUNCTION__,__FILE__,__LINE__)

class LogWrap
{
public:
	LogWrap& Reset();
	LogWrap& Reset( const char* cate, int priority );
	LogWrap& Reset( const char* cate, int priority, const char* func, const char* file, int line );
	
	LogWrap& AddFunc(const char* func, const char* file, int  line);
	
	LogWrap& Flush();
	LogWrap& Flush(const char* cate, int priority);
	
	void SetCurCate(const char* cate ){
		this->_cateLog = cate;
	}
	
	void SetCurPriority( int priority){
		this->_priority = priority;
	}
	
	template<typename T>
	LogWrap& operator<< ( const T& val ){
		_logStream<<val;
		return * this;
	}
private:
	std::stringstream _logStream;
	std::string _cateLog;
	int		    _priority;
};

#endif // LOGWRAP_H
