#ifndef __LUA_LOG_H__
#define __LUA_LOG_H__

#include "ls_debug.h"

#define  LUA_LOGOBJECT       "LuaMain"
#define  LUA_THRDLOG         "LuaThrd"

#define LUA_INFO(FMT, ...) LogPrintPrint( LUA_LOGOBJECT, LOG_PRIORITY_INFO,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define LUA_WARN(FMT, ...) LogPrintPrint( LUA_LOGOBJECT, LOG_PRIORITY_WARNING,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define LUA_ERR(FMT, ...)  LogPrintPrint( LUA_LOGOBJECT, LOG_PRIORITY_ERROR,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ##  __VA_ARGS__ )
#define LUA_DEBUG(FMT, ...) LogPrintPrint( LUA_LOGOBJECT, LOG_PRIORITY_DEBUG,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )


#define LDB_INFO(FMT, ...) LogPrintPrint( LUA_THRDLOG, LOG_PRIORITY_INFO,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define LDB_WARN(FMT, ...) LogPrintPrint( LUA_THRDLOG, LOG_PRIORITY_WARNING,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define LDB_ERR(FMT, ...)  LogPrintPrint( LUA_THRDLOG, LOG_PRIORITY_ERROR,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ##  __VA_ARGS__ )
#define LDB_DEBUG(FMT, ...) LogPrintPrint( LUA_THRDLOG, LOG_PRIORITY_DEBUG,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )

#endif
