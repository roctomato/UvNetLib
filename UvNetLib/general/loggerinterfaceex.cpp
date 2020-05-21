#include <stdio.h>
#include "loggerinterfaceex.h"

LoggerPtr* gLog = NULL;

void InitLog( LoggerPtr& pLog, const std::string& configFile )
{
    gLog = new LoggerPtr();
	*gLog = pLog;
	if ( (*gLog).get() )
		(*gLog)->Configure( configFile );
}
void LogPrintPrint( const std::string& categoryName, int priority, const char* format, ... )
{
	va_list va;
	va_start(va,format);
    
	if ( gLog && (*gLog).get() ){
		(*gLog)->Print( categoryName, priority, format, va );
	}else{
		vprintf(format, va);
		putchar('\n');
	}
	va_end(va);
}
void LogPrintPrint( const std::string& categoryName, int priority, const std::string& message)
{
	if ( gLog && (*gLog).get() ){
		(*gLog)->Print( categoryName, priority, message );
	}else{
		if ( message.empty()){
			printf( "empty message\n");
		}else{
			printf( message.c_str());
			if ( message[ message.size()-1] != '\n')
				putchar('\n');
		}
		
	}
	
}
