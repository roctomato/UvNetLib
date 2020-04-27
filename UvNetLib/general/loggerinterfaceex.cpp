#include <stdio.h>
#include "loggerinterfaceex.h"

LoggerInterfaceEx * gLog = NULL;

void InitLog( LoggerInterfaceEx* pLog, const std::string& configFile )
{
	gLog = pLog;
	if ( gLog )
		gLog->Configure( configFile );
}
void LogPrintPrint( const std::string& categoryName, int priority, const char* format, ... )
{
	va_list va;
	va_start(va,format);
	if ( gLog ){
		gLog->Print( categoryName, priority, format, va );
	}else{
		vprintf(format, va);
		putchar('\n');
	}
	va_end(va);
}
void LogPrintPrint( const std::string& categoryName, int priority, const std::string& message)
{
	if ( gLog ){
		gLog->Print( categoryName, priority, message );
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
