#ifndef  __CORE_DEBUG_H__
#define  __CORE_DEBUG_H__

#define  DEBUG_NETWORK_FRAME        ( 1 << 0 )
#define  DEBUG_NETWORK_TIMER        ( 1 << 1 )
#define  DEBUG_NETWORK_CONNECT      ( 1 << 3 )
#define  DEBUG_NETWORK_PING         ( 1 << 4 )
#define  DEBUG_NETWORK_NORMAL       ( 1 << 5 )
#define  DEBUG_NETWORK_NET          ( 1 << 6 )

#define  NET_LOGFILE        "networklog"
#define  SYSTEM_LOGFILE     "systemlog"
#define  CHAT_LOGFILE       "chatlog"
#define  LOGIC_LOGFILE      "logiclog"
#define  DB_LOGOBJECT       "dblog"


#include "loggerinterfaceex.h"

#define LOG_PRIORITY_DEBUG   700
#define LOG_PRIORITY_INFO    600
#define LOG_PRIORITY_WARNING 400
#define LOG_PRIORITY_ERROR   300


#define DB_INFO(FMT, ...) LogPrintPrint( DB_LOGOBJECT, LOG_PRIORITY_INFO,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define DB_WARN(FMT, ...) LogPrintPrint( DB_LOGOBJECT, LOG_PRIORITY_WARNING,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define DB_ERR(FMT, ...)  LogPrintPrint( DB_LOGOBJECT, LOG_PRIORITY_ERROR,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ##  __VA_ARGS__ )
#define DB_DEBUG(FMT, ...) LogPrintPrint( DB_LOGOBJECT, LOG_PRIORITY_DEBUG,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )

#define NET_ERR(FMT, ...) LogPrintPrint( NET_LOGFILE, LOG_PRIORITY_ERROR,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define NET_INFO(FMT, ...)LogPrintPrint( NET_LOGFILE, LOG_PRIORITY_INFO,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define NET_WARN(FMT, ...)LogPrintPrint( NET_LOGFILE, LOG_PRIORITY_WARNING,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define NET_DEBUG(FMT, ...) LogPrintPrint( NET_LOGFILE, LOG_PRIORITY_DEBUG,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )

#define SYS_INFO(FMT, ...) LogPrintPrint( SYSTEM_LOGFILE, LOG_PRIORITY_INFO,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define SYS_WARN(FMT, ...) LogPrintPrint( SYSTEM_LOGFILE, LOG_PRIORITY_WARNING,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define SYS_ERR(FMT, ...) LogPrintPrint( SYSTEM_LOGFILE, LOG_PRIORITY_ERROR,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )
#define SYS_DEBUG(FMT, ...) LogPrintPrint( SYSTEM_LOGFILE, LOG_PRIORITY_DEBUG,"%s (%s:%d) " FMT,__FUNCTION__,__FILE__,__LINE__, ## __VA_ARGS__ )

#endif
