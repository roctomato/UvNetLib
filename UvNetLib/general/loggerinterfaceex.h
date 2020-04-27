#ifndef LOGGERINTERFACEEX_H
#define LOGGERINTERFACEEX_H

#include <stdexcept>
#include <stdarg.h>
#include <string>

/**
 * @brief Exception class for configuration.
 */
class ConfigureExceptionEx : public std::runtime_error
{
public:
    /**
     * @brief Constructor.
     * @param reason String containing the description of the exception.
     */
    ConfigureExceptionEx( const std::string& reason ) : std::runtime_error( reason ) {}
};

class LoggerInterfaceEx
{
// Construction.
public:
    /// Destructor.
    virtual ~LoggerInterfaceEx() {}

// Method.
public:
    /// Load configure.
    virtual void Configure( const std::string& configFile )  = 0;
    
    /// Log a message with the specified category and priority.
    virtual void Print( const std::string& categoryName, int priority, const char* format, va_list args )  = 0;

    /// Log a message with the specified category and priority.
    virtual void Print( const std::string& categoryName, int priority, const std::string& message )  = 0;

};

void InitLog( LoggerInterfaceEx* pLo, const std::string& configFile );
void LogPrintPrint( const std::string& categoryName, int priority, const char* format, ... );
void LogPrintPrint( const std::string& categoryName, int priority, const std::string& message);
#endif // LOGGERINTERFACEEX_H
